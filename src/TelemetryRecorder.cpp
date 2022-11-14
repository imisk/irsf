

#include "TelemetryRecorder.h"
#include <conio.h>

using namespace irsf;

TelemetryRecorder::TelemetryRecorder(TelemetryDiskWriter* telemetryDiskWriter,
                                     irsf::irsdk::IrsdkManager* irsdkMngr,
                                     size_t maxTicks)
    : MaxTicksInMemory(maxTicks),
      writer(telemetryDiskWriter),
      irsdkManager(irsdkMngr) {
  writerHandler->SetWriter(writer);
}

void TelemetryRecorder::Init(const std::string& recordingFileName,
                             const std::vector<VariableId> inputVariablesIn) {
  irsdkManager->InitVariables(inputVariablesIn, inputVariables,
                              inputVariablesNonFloat);

  InitLapVariable();

  InitMemory(MaxTicksInMemory);

  InitWriter(recordingFileName, inputVariablesIn);

  currentOffset = 0;
  tickCount = 0;

  /*
   * Begin by assigning mem1 as the one being written to. Later
   * we swap as one is being written to disk.
   */

  recorderValues = &recorderValues_mem1[0];
}

TelemetryRecorder::~TelemetryRecorder() {
  if (valuePointers.size() != 0)
    valuePointers.clear();

  recorderValues_mem1.clear();

  recorderValues_mem2.clear();

  inputVariables.clear();
}

void TelemetryRecorder::Record() {
  ConvertFloats();

  for (size_t i = 0; i < valuePointers.size(); i++) {
    recorderValues[currentOffset] = *valuePointers[i];

    ++currentOffset;
  }
  ++tickCount;

  // We crossed the start/finish line
  if ((previouslyRecordedLapNumber + 0.5f) < *currentLapLiveData) {
    previouslyRecordedLapNumber = *currentLapLiveData;

    SendToWriter();

    writer->WriteCurrentLap_Prepare(
        static_cast<int32_t>(previouslyRecordedLapNumber));

    writerHandler->WriteCurrentLap();
  }

  if (tickCount >= MaxTicksInMemory) {
    SendToWriter();
  }
}

void TelemetryRecorder::SendToWriter() {
  if (tickCount == 0)
    return;

  writer->WriteData_Prepare(recorderValues, inputVariables.size(), tickCount);

  writerHandler->WriteData();

  /*
  Now swap the memory space being used for live data writing while we
  write the other one to disk.
  */

  if (recorderValues == &recorderValues_mem1[0])
    recorderValues = &recorderValues_mem2[0];
  else
    recorderValues = &recorderValues_mem1[0];

  tickCount = 0;
  currentOffset = 0;
}

void TelemetryRecorder::InitMemory(size_t maxTicksInMemory) {
  if (valuePointers.size() != 0)
    valuePointers.clear();

  recorderValues_mem1.clear();

  recorderValues_mem2.clear();

  MaxTicksInMemory = maxTicksInMemory;

  size_t memSize = (MaxTicksInMemory + kMaxTicksSafety) * inputVariables.size();

  for (const auto& var : inputVariables) {
    valuePointers.push_back(var->GetPointer());
  }

  recorderValues_mem1 = std::vector<float>(memSize, 0.0f);

  recorderValues_mem2 = std::vector<float>(memSize, 0.0f);
}

void TelemetryRecorder::InitLapVariable() {
  bool lapVariableFound = false;

  previouslyRecordedLapNumber = 0;

  for (const auto& var : inputVariablesNonFloat) {
    VariableId varId = var->GetVariableId();

    if (varId == VariableId::Lap) {
      var->ConvertToFloat();
      currentLapLiveData = var->GetPointer();
      previouslyRecordedLapNumber = 0;
      lapVariableFound = true;
      qDebug() << "Lap variable found.";
    }
  }

  if (!lapVariableFound) {
    std::cout << "Error: TelemetryRecorder could not find Lap "
                 "variable in live data. \n";
    throw IrsfException(IrsfError::TelemetryRecorderNoLapVariable);
  }
}

void TelemetryRecorder::InitWriter(const std::string& fileName,
                                   const std::vector<VariableId>& inputVars) {
  writer->OpenFile(fileName);
  writer->WriteFileVersion();
  writer->WriteVariableList(inputVars);
  writer->WriteCurrentLap_Prepare(
      static_cast<int32_t>(previouslyRecordedLapNumber));
  writerHandler->WriteCurrentLap();
}

void TelemetryRecorder::ConvertFloats() noexcept {
  for (const auto& iv : inputVariablesNonFloat) {
    iv->ConvertToFloat();
  }
}
