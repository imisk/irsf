
#include "SignalLivePlayer.h"
#include "IrsfCommon.h"

using namespace irsf;

SignalLivePlayer::SignalLivePlayer(TrackDataManager* tdm,
                                   FormulaDbManager* fdm,
                                   SignalDbManager* sdm) noexcept
    : trackDataManager(tdm), formulaDbManager(fdm), signalDbManager(sdm) {}

void SignalLivePlayer::Initialize(const IrsfSignalSet& set,
                                  SoundMixer* soundMixer,
                                  float*& lapDist,
                                  int32_t*& curLap,
                                  bool*& onPitRoad,
                                  std::vector<iVarInterface_sp>& inputVars) {
  if (set.signalNames.size() == 0)
    throw IrsfException(IrsfError::SignalSetEmpty);

  if (lapDist == nullptr)
    throw IrsfException(IrsfError::InvalidPointer);

  lapDistLive = lapDist;

  lapDistancePreviousTick = *lapDistLive;

  if (curLap == nullptr)
    throw IrsfException(IrsfError::InvalidPointer);

  curLapLive = curLap;
  currentLap = *curLapLive;

  onPitRoadLive = onPitRoad;
  currentOnPitRoad = *onPitRoadLive;

  waitingForNextLap = false;

  activeChannels = &soundMixer->activeChannels;
  inputVariables = &inputVars;

  nextEventIndex = 0;

  evaluator = std::make_unique<FormulaEvaluator>();

  soundFileReader = std::make_unique<SoundFileReader>();

  nextEventPairId = 0;

  for (const auto& signalName : set.signalNames) {
    IrsfSignal* newSig = signalDbManager->GetSignal(signalName);

    RegisterSignal(newSig);
  }

  qDebug() << "i4";
  std::sort(events.begin(), events.end(), SignalActivationEventComparer());

  std::cout << "Total events registered: " << events.size() << std::endl;
}

static int32_t debug_msgCountWaiting = 0;

void SignalLivePlayer::OnTickUpdate() {
  if (events.size() == 0 && activeEvents.size() == 0)
    throw IrsfException(IrsfError::LiveSignalPlayerEventsEmpty);

  bool finished = false;

  // activate/deactivate events
  while (finished == false) {
    if (*onPitRoadLive == true) {
      if (currentOnPitRoad == false) {
        std::cout << "Entered pits. ------------------"
                     "---- *-*-*-*-*-* ------------ \n";

        StopAllActiveEvents();

        nextEventIndex = 0;
        waitingForNextLap = false;

        if (BrakeMarkerManagerIsActive) {
          bmm->SetFirstMarkerAsNext();
        }
      }
      currentOnPitRoad = true;

      finished = true;
    } else {
      if (currentOnPitRoad == true) {
        std::cout << "LEAVING pits. ---------"
                     "------------- *-*-*-*-*-* ^^^^^ ------------ ";
        std::cout << " _ nextEvent = " << nextEventIndex << std::endl;
      }
      currentOnPitRoad = false;

      float lapDistanceTickDelta = *lapDistLive - lapDistancePreviousTick;

      if (waitingForNextLap) {
        if (lapDistanceTickDelta < kNextLapSwitchActivationDistance) {
          // next lap detected
          currentLap = *curLapLive;
          qDebug() << "Next lap detected! =============="
                      "============== cur lap distance = "
                   << *lapDistLive << "Now on lap: " << currentLap;
          waitingForNextLap = false;
        }

        finished = true;
      }

      // check if event should be activated
      if (waitingForNextLap == false) {
        if (lapDistanceTickDelta < kNextLapSwitchActivationDistance) {
          qDebug() << "Next lap detected (mode 2)! =================="
                      "========== cur lap distance = "
                   << *lapDistLive << "Now on lap: " << *curLapLive;

          StopAllActiveEvents();

          nextEventIndex = 0;
        }

        if (events.size() > 0) {
          SignalActivationEvent* nextEvent = nullptr;

          nextEvent = events[nextEventIndex].get();

          if (*lapDistLive > nextEvent->lapDistance) {
            // activate event
            qDebug() << "Activating event. lapDistLive = " << *lapDistLive
                     << " _ next lapDist = " << nextEvent->lapDistance;

            if (nextEvent->type == SignalActivationEventType::Start) {
              std::cout << "=========== Activating START event "
                        << nextEventIndex << std::endl;
              AddActiveChannel(nextEvent->channel.get());
              AddActiveEvent(nextEvent);
            } else if (nextEvent->type == SignalActivationEventType::Stop) {
              std::cout << "=========== Activating END event " << nextEventIndex
                        << std::endl;
              RemoveActiveChannel(nextEvent->channel.get());
              RemoveActiveEvent(nextEvent);
            }

            //.... add formula to list of those being evaluated live

            ++nextEventIndex;

            if (nextEventIndex == events.size()) {
              nextEventIndex = 0;

              waitingForNextLap = true;

              std::cout << "Waiting for next lap = true \n";

              StopAllActiveEvents();

              finished = true;
            }
          } else {
            finished = true;
          }

        } else {
          finished = true;
        }
      }
    }
  }

  lapDistancePreviousTick = *lapDistLive;

  /*
   * Now that we have updated active events, update the multipliers that
   * are still active (if any)
   */

  UpdateMultipliers();
}

void SignalLivePlayer::RegisterSignal(IrsfSignal* signal) {
  TrackSector ts;

  if (signal->useFullTrack == false) {
    try {
      auto tsret = trackDataManager->GetTrackSector(signal->trackSectorId);

      if (tsret.has_value()) {
        ts = tsret.value();
      }

    } catch (IrsfException& err) {
      std::cout << "Error : invalid Track Sector ID for signal. Check "
                   "your data files. Signal name: "
                << signal->name.c_str() << std::endl;

      Q_UNUSED(err)
      throw;
    }
  }

  auto formula = formulaDbManager->GetFormulaWithName(signal->formulaName);

  if (formula == nullptr) {
    std::cout << "Error : invalid formula name for signal. Check your "
                 "data files. Signal name: "
              << signal->name.c_str() << std::endl;
    throw IrsfException(IrsfError::ItemNotFound);
  }

  ++nextEventPairId;

  // create the start event ----------------------------
  auto start = std::make_unique<SignalActivationEvent>();
  start->type = SignalActivationEventType::Start;
  start->signal = signal;

  start->channel = CreateChannelForSignalActivationEvent(*start);

  auto chCopy = start->channel;
  if (start->channel == nullptr) {
    throw IrsfException(IrsfError::SoundChannelCreationFailed);
  }

  start->formulaPostfixBase.clear();

  evaluator->InfixToPostfix(formula->GetCurrentFormulaInfix(),
                            start->formulaPostfixBase);

  evaluator->CreateFormulaEvaluatedValues(
      *inputVariables, start->formulaPostfixBase,
      start->formulaPostfixEvaluated, start->formulaPostfixEvaluated_p);

  if (signal->useFullTrack == false) {
    start->lapDistance = ts.startDistance;
    start->pairId = nextEventPairId;
  } else {
    AddActiveEvent(start.get());
    AddActiveChannel(start->channel.get());
  }

  events.emplace_back(std::move(start));

  if (signal->useFullTrack == true)
    return;

  // create the end event  ----------------------------
  auto end = std::make_unique<SignalActivationEvent>();
  end->type = SignalActivationEventType::Stop;
  end->signal = signal;
  end->lapDistance = ts.endDistance;
  end->channel = chCopy;  // we are starting and stopping the same channel
  end->pairId = nextEventPairId;

  end->formulaPostfixBase.clear();

  evaluator->InfixToPostfix(formula->GetCurrentFormulaInfix(),
                            end->formulaPostfixBase);

  /*
   * consider: i don't think we need to create formula for the end event!
   * */
  evaluator->CreateFormulaEvaluatedValues(
      *inputVariables, end->formulaPostfixBase, end->formulaPostfixEvaluated,
      end->formulaPostfixEvaluated_p);

  events.emplace_back(std::move(end));
}

std::shared_ptr<SoundChannel>
SignalLivePlayer::CreateChannelForSignalActivationEvent(
    const SignalActivationEvent& event) {
  auto sdata = std::make_unique<SoundData>();
  soundFileReader->LoadSoundChannelFromFile(
      event.signal->sound.soundFileName, sdata.get(),
      kSoundChannelLoadBufferOverrun, event.signal->sound.soundVolume);

  std::cout << "Sound file loaded: " << event.signal->sound.soundFileName
            << std::endl;

  std::shared_ptr<SoundChannel> retChannel = std::make_shared<SoundChannel>();

  retChannel->snd = std::move(sdata);
  retChannel->multiplier = 1.0;
  retChannel->offset = 0;

  return retChannel;
}

void SignalLivePlayer::AddActiveChannel(SoundChannel* channel) {
  std::scoped_lock<std::mutex> lock(rMutex);

  qDebug() << "Added active channel. ------------------------------------ ac";
  activeChannels->push_back(channel);
}

void SignalLivePlayer::RemoveActiveChannel(
    const SoundChannel* channel) noexcept {
  std::scoped_lock<std::mutex> lock(rMutex);

  bool found = false;

  unsigned long deleteIndex = 0;
  size_t i = 0;
  bool finished = false;

  while (!finished) {
    if ((*activeChannels)[i] == channel) {
      found = true;
      deleteIndex = static_cast<unsigned long>(i);
      finished = true;
    }

    ++i;
    if (i == activeChannels->size())
      finished = true;
  }

  if (found) {
    qDebug() << "Remove active channel ... count before = ."
             << activeChannels->size();

    activeChannels->erase(activeChannels->begin() + deleteIndex);

    qDebug() << "Remove active channel ... count after = ."
             << activeChannels->size();
  }
}

void SignalLivePlayer::RemoveAllChannels() {
  activeChannels->clear();
}

void SignalLivePlayer::AddActiveEvent(SignalActivationEvent* event) {
  std::scoped_lock<std::mutex> lock(rMutex);

  qDebug() << "AddActiveEvent. ----------------------------------------- ac";
  activeEvents.push_back(event);
}

void SignalLivePlayer::RemoveActiveEvent(SignalActivationEvent* event) {
  std::scoped_lock<std::mutex> lock(rMutex);

  bool found = false;

  qDebug() << "RemoveActiveEvent..";

  std::streamsize deleteIndex = 0;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (activeEvents[i]->pairId == event->pairId) {
      // qDebug() << "Found one event...";
      found = true;
      deleteIndex = static_cast<std::streamsize>(i);
      finished = true;
    }

    ++i;
    if (i == activeEvents.size())
      finished = true;
  }

  if (found) {
    qDebug() << "Removing active event.";
    activeEvents.erase(activeEvents.begin() + deleteIndex);
  } else {
    qDebug() << "Removing active event ------- NOT FOUND --------- ****.";
  }
}

void SignalLivePlayer::UpdateMultipliers() {
  if (*onPitRoadLive == true) {
    for (auto& active : activeEvents) {
      active->channel->multiplier = 0.0f;
    }
  } else {
    for (auto& active : activeEvents) {
      float val = 0.0f;

      evaluator->EvaluateFormula(active->formulaPostfixEvaluated_p, &val);

      /*
      Now apply the ranges to find a multiplier

      range 1 is positive
          (everything below Min is 0, everything above Max is 1)
      range 2 is negative
          (everything above Max is 0, everything below Min is 1)
      */

      SignalRange r1 = active->signal->range1;
      SignalRange r2 = active->signal->range2;

      // check range 1
      if (val > r1.min && val < r1.max) {
        // we are inside of range 1

        float rangeTotal = r1.max - r1.min;

        float delta = val - r1.min;

        active->channel->multiplier = (delta / rangeTotal);

      } else {
        // we are outside of range 1
        if (val <= r1.min) {
          // below minimum
          active->channel->multiplier = 0.0f;
        } else if (val >= r1.max) {
          // above maximum
          active->channel->multiplier = 1.0f;
        }
      }

      if (active->signal->secondRangeActive) {
        if (val < r2.max && val > r2.min) {
          // we are inside of range 2

          float rangeTotal = r2.max - r2.min;

          float delta = r2.max - val;

          active->channel->multiplier = (delta / rangeTotal);

        } else {
          // we are outside of range 2
          if (val >= r2.max && val <= r1.min) {
            // we are above maximum, but still below range1 minimum
            active->channel->multiplier = 0.0f;
          } else if (val <= r2.min) {
            // we are below minimum
            active->channel->multiplier = 1.0f;
          }
        }
      }
    }
  }
}

void SignalLivePlayer::StopAllActiveEvents() {
  if (events.size() > 0) {
    size_t curEventIdx;

    for (curEventIdx = nextEventIndex; curEventIdx < events.size();
         curEventIdx++) {
      SignalActivationEvent* nextEvent;

      {
        std::scoped_lock<std::mutex> lock(rMutex);
        nextEvent = events[curEventIdx].get();
      }

      if (nextEvent->type == SignalActivationEventType::Stop) {
        std::cout << "=========== Activating END event " << curEventIdx
                  << std::endl;

        RemoveActiveChannel(nextEvent->channel.get());
        RemoveActiveEvent(nextEvent);
      }
    }
  }
}
