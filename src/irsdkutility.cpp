
#include "irsdkutility.h"

using namespace irsf;

bool irsf::irsdk::IrsdkResizeData(IrsdkVarsData* varData) {
  if (varData->data == nullptr ||
      varData->dataLength !=
          static_cast<unsigned long long>(varData->pHeader->bufLen)) {
    if (varData->data != nullptr)
      delete[] varData->data;

    varData->data = nullptr;

    if (varData->pHeader->bufLen > 0) {
      varData->dataLength =
          static_cast<unsigned long long>(varData->pHeader->bufLen);
      varData->data = new char[varData->dataLength];
    } else {
      return false;
    }

    return true;
  }

  return true;
}

int32_t irsf::irsdk::irsdk_varNameToIndex(IrsdkVarsData* varData,
                                          IrsdkWindowsCtr* winCtr,
                                          const char* name) noexcept(false) {
  if (name) {
    for (int32_t index = 0; index < varData->pHeader->numVars; index++) {
      const irsdk_varHeader* pVar = nullptr;

      pVar = irsdk_getVarHeaderEntry(varData, winCtr, index);

      if (pVar && 0 == strncmp(name, pVar->name, IRSDK_MAX_STRING)) {
        return index;
      }
    }
  }

  return -1;
}

const irsdk_varHeader* irsf::irsdk::irsdk_getVarHeaderEntry(
    IrsdkVarsData* varData,
    IrsdkWindowsCtr* winCtr,
    int32_t index) noexcept {
  if (index >= 0 && index < varData->pHeader->numVars) {
    auto pso = winCtr->pSharedMem + varData->pHeader->varHeaderOffset;

    return &(reinterpret_cast<const irsdk_varHeader*>(pso))[index];

    /*
     * return &(reinterpret_cast<const irsdk_varHeader*>((
     * winCtr->pSharedMem + varData->pHeader->varHeaderOffset)))[index];
     */
  }

  return nullptr;
}

void irsf::irsdk::GetVarType(VariableId varId,
                             irsdk_VarType& retType) noexcept {
  /*
   * This must be updated if iRacing SDK updates, or new Derived/Processed
   * variables are added.
   */

  retType = irsdk_int;

  switch (varId) {
    // case VariableId::Lap : retType = irsdk_float;
    case VariableId::SessionTime:
      retType = irsdk_double;
    case VariableId::SessionTick:
      retType = irsdk_int;
    case VariableId::SessionNum:
      retType = irsdk_int;
    case VariableId::SessionState:
      retType = irsdk_int;
    case VariableId::SessionUniqueID:
      retType = irsdk_int;
    case VariableId::SessionFlags:
      retType = irsdk_bitField;
    case VariableId::SessionTimeRemain:
      retType = irsdk_double;
    case VariableId::SessionLapsRemain:
      retType = irsdk_int;
    case VariableId::SessionLapsRemainEx:
      retType = irsdk_int;
    case VariableId::SessionTimeOfDay:
      retType = irsdk_float;
    case VariableId::RadioTransmitCarIdx:
      retType = irsdk_int;
    case VariableId::RadioTransmitRadioIdx:
      retType = irsdk_int;
    case VariableId::RadioTransmitFrequencyIdx:
      retType = irsdk_int;
    case VariableId::DisplayUnits:
      retType = irsdk_int;
    case VariableId::DriverMarker:
      retType = irsdk_bool;
    case VariableId::PushToPass:
      retType = irsdk_bool;
    case VariableId::ManualBoost:
      retType = irsdk_bool;
    case VariableId::ManualNoBoost:
      retType = irsdk_bool;
    case VariableId::IsOnTrack:
      retType = irsdk_bool;
    case VariableId::IsReplayPlaying:
      retType = irsdk_bool;
    case VariableId::ReplayFrameNum:
      retType = irsdk_int;
    case VariableId::ReplayFrameNumEnd:
      retType = irsdk_int;
    case VariableId::IsDiskLoggingEnabled:
      retType = irsdk_bool;
    case VariableId::IsDiskLoggingActive:
      retType = irsdk_bool;
    case VariableId::FrameRate:
      retType = irsdk_float;
    case VariableId::CpuUsageBG:
      retType = irsdk_float;
    case VariableId::PlayerCarPosition:
      retType = irsdk_int;
    case VariableId::PlayerCarClassPosition:
      retType = irsdk_int;
    case VariableId::PlayerTrackSurface:
      retType = irsdk_int;
    case VariableId::PlayerTrackSurfaceMaterial:
      retType = irsdk_int;
    case VariableId::PlayerCarIdx:
      retType = irsdk_int;
    case VariableId::PlayerCarTeamIncidentCount:
      retType = irsdk_int;
    case VariableId::PlayerCarMyIncidentCount:
      retType = irsdk_int;
    case VariableId::PlayerCarDriverIncidentCount:
      retType = irsdk_int;
    case VariableId::PlayerCarWeightPenalty:
      retType = irsdk_float;
    case VariableId::PlayerCarPowerAdjust:
      retType = irsdk_float;
    case VariableId::PlayerCarTowTime:
      retType = irsdk_float;
    case VariableId::PlayerCarInPitStall:
      retType = irsdk_bool;
    case VariableId::PlayerCarPitSvStatus:
      retType = irsdk_int;
    case VariableId::CarIdxLap:
      retType = irsdk_int;
    case VariableId::CarIdxLapCompleted:
      retType = irsdk_int;
    case VariableId::CarIdxLapDistPct:
      retType = irsdk_float;
    case VariableId::CarIdxTrackSurface:
      retType = irsdk_int;
    case VariableId::CarIdxTrackSurfaceMaterial:
      retType = irsdk_int;
    case VariableId::CarIdxOnPitRoad:
      retType = irsdk_bool;
    case VariableId::CarIdxPosition:
      retType = irsdk_int;
    case VariableId::CarIdxClassPosition:
      retType = irsdk_int;
    case VariableId::CarIdxF2Time:
      retType = irsdk_float;
    case VariableId::CarIdxEstTime:
      retType = irsdk_float;
    case VariableId::CarIdxLastLapTime:
      retType = irsdk_float;
    case VariableId::CarIdxBestLapTime:
      retType = irsdk_float;
    case VariableId::CarIdxBestLapNum:
      retType = irsdk_int;
    case VariableId::OnPitRoad:
      retType = irsdk_bool;
    case VariableId::CarIdxSteer:
      retType = irsdk_float;
    case VariableId::CarIdxRPM:
      retType = irsdk_float;
    case VariableId::CarIdxGear:
      retType = irsdk_int;
    case VariableId::SteeringWheelAngle:
      retType = irsdk_float;
    case VariableId::Throttle:
      retType = irsdk_float;
    case VariableId::Brake:
      retType = irsdk_float;
    case VariableId::Clutch:
      retType = irsdk_float;
    case VariableId::Gear:
      retType = irsdk_int;
    case VariableId::RPM:
      retType = irsdk_float;
    case VariableId::Lap:
      retType = irsdk_int;
    case VariableId::LapCompleted:
      retType = irsdk_int;
    case VariableId::LapDist:
      retType = irsdk_float;
    case VariableId::LapDistPct:
      retType = irsdk_float;
    case VariableId::RaceLaps:
      retType = irsdk_int;
    case VariableId::LapBestLap:
      retType = irsdk_int;
    case VariableId::LapBestLapTime:
      retType = irsdk_float;
    case VariableId::LapLastLapTime:
      retType = irsdk_float;
    case VariableId::LapCurrentLapTime:
      retType = irsdk_float;
    case VariableId::LapLasNLapSeq:
      retType = irsdk_int;
    case VariableId::LapLastNLapTime:
      retType = irsdk_float;
    case VariableId::LapBestNLapLap:
      retType = irsdk_int;
    case VariableId::LapBestNLapTime:
      retType = irsdk_float;
    case VariableId::LapDeltaToBestLap:
      retType = irsdk_float;
    case VariableId::LapDeltaToBestLap_DD:
      retType = irsdk_float;
    case VariableId::LapDeltaToBestLap_OK:
      retType = irsdk_bool;
    case VariableId::LapDeltaToOptimalLap:
      retType = irsdk_float;
    case VariableId::LapDeltaToOptimalLap_DD:
      retType = irsdk_float;
    case VariableId::LapDeltaToOptimalLap_OK:
      retType = irsdk_bool;
    case VariableId::LapDeltaToSessionBestLap:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionBestLap_DD:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionBestLap_OK:
      retType = irsdk_bool;
    case VariableId::LapDeltaToSessionOptimalLap:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionOptimalLap_DD:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionOptimalLap_OK:
      retType = irsdk_bool;
    case VariableId::LapDeltaToSessionLastlLap:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionLastlLap_DD:
      retType = irsdk_float;
    case VariableId::LapDeltaToSessionLastlLap_OK:
      retType = irsdk_bool;
    case VariableId::Speed:
      retType = irsdk_float;
    case VariableId::Yaw:
      retType = irsdk_float;
    case VariableId::YawNorth:
      retType = irsdk_float;
    case VariableId::Pitch:
      retType = irsdk_float;
    case VariableId::Roll:
      retType = irsdk_float;
    case VariableId::EnterExitReset:
      retType = irsdk_int;
    case VariableId::TrackTemp:
      retType = irsdk_float;
    case VariableId::TrackTempCrew:
      retType = irsdk_float;
    case VariableId::AirTemp:
      retType = irsdk_float;
    case VariableId::WeatherType:
      retType = irsdk_int;
    case VariableId::Skies:
      retType = irsdk_int;
    case VariableId::AirDensity:
      retType = irsdk_float;
    case VariableId::AirPressure:
      retType = irsdk_float;
    case VariableId::WindVel:
      retType = irsdk_float;
    case VariableId::WindDir:
      retType = irsdk_float;
    case VariableId::RelativeHumidity:
      retType = irsdk_float;
    case VariableId::FogLevel:
      retType = irsdk_float;
    case VariableId::DCLapStatus:
      retType = irsdk_int;
    case VariableId::DCDriversSoFar:
      retType = irsdk_int;
    case VariableId::OkToReloadTextures:
      retType = irsdk_bool;
    case VariableId::LoadNumTextures:
      retType = irsdk_bool;
    case VariableId::CarLeftRight:
      retType = irsdk_bitField;
    case VariableId::PitsOpen:
      retType = irsdk_bool;
    case VariableId::PitRepairLeft:
      retType = irsdk_float;
    case VariableId::PitOptRepairLeft:
      retType = irsdk_float;
    case VariableId::PitstopActive:
      retType = irsdk_bool;
    case VariableId::FastRepairUsed:
      retType = irsdk_int;
    case VariableId::FastRepairAvailable:
      retType = irsdk_int;
    case VariableId::CamCarIdx:
      retType = irsdk_int;
    case VariableId::CamCameraNumber:
      retType = irsdk_int;
    case VariableId::CamGroupNumber:
      retType = irsdk_int;
    case VariableId::CamCameraState:
      retType = irsdk_bitField;
    case VariableId::IsOnTrackCar:
      retType = irsdk_bool;
    case VariableId::IsInGarage:
      retType = irsdk_bool;
    case VariableId::SteeringWheelPctTorque:
      retType = irsdk_float;
    case VariableId::SteeringWheelPctTorqueSign:
      retType = irsdk_float;
    case VariableId::SteeringWheelPctTorqueSignStops:
      retType = irsdk_float;
    case VariableId::SteeringWheelPctDamper:
      retType = irsdk_float;
    case VariableId::SteeringWheelAngleMax:
      retType = irsdk_float;
    case VariableId::ShiftIndicatorPct:
      retType = irsdk_float;
    case VariableId::ShiftPowerPct:
      retType = irsdk_float;
    case VariableId::ShiftGrindRPM:
      retType = irsdk_float;
    case VariableId::ThrottleRaw:
      retType = irsdk_float;
    case VariableId::BrakeRaw:
      retType = irsdk_float;
    case VariableId::HandbrakeRaw:
      retType = irsdk_float;
    case VariableId::SteeringWheelPeakForceNm:
      retType = irsdk_float;
    case VariableId::EngineWarnings:
      retType = irsdk_bitField;
    case VariableId::FuelLevel:
      retType = irsdk_float;
    case VariableId::FuelLevelPct:
      retType = irsdk_float;
    case VariableId::PitSvFlags:
      retType = irsdk_bitField;
    case VariableId::PitSvLFP:
      retType = irsdk_float;
    case VariableId::PitSvRFP:
      retType = irsdk_float;
    case VariableId::PitSvLRP:
      retType = irsdk_float;
    case VariableId::PitSvRRP:
      retType = irsdk_float;
    case VariableId::PitSvFuel:
      retType = irsdk_float;
    case VariableId::CarIdxP2P_Status:
      retType = irsdk_bool;
    case VariableId::CarIdxP2P_Count:
      retType = irsdk_int;
    case VariableId::ReplayPlaySpeed:
      retType = irsdk_int;
    case VariableId::ReplayPlaySlowMotion:
      retType = irsdk_bool;
    case VariableId::ReplaySessionTime:
      retType = irsdk_double;
    case VariableId::ReplaySessionNum:
      retType = irsdk_int;
    case VariableId::TireLF_RumblePitch:
      retType = irsdk_float;
    case VariableId::TireRF_RumblePitch:
      retType = irsdk_float;
    case VariableId::TireLR_RumblePitch:
      retType = irsdk_float;
    case VariableId::TireRR_RumblePitch:
      retType = irsdk_float;
    case VariableId::SteeringWheelTorque_ST:
      retType = irsdk_float;
    case VariableId::SteeringWheelTorque:
      retType = irsdk_float;
    case VariableId::VelocityZ_ST:
      retType = irsdk_float;
    case VariableId::VelocityY_ST:
      retType = irsdk_float;
    case VariableId::VelocityX_ST:
      retType = irsdk_float;
    case VariableId::VelocityZ:
      retType = irsdk_float;
    case VariableId::VelocityY:
      retType = irsdk_float;
    case VariableId::VelocityX:
      retType = irsdk_float;
    case VariableId::YawRate_ST:
      retType = irsdk_float;
    case VariableId::PitchRate_ST:
      retType = irsdk_float;
    case VariableId::RollRate_ST:
      retType = irsdk_float;
    case VariableId::YawRate:
      retType = irsdk_float;
    case VariableId::PitchRate:
      retType = irsdk_float;
    case VariableId::RollRate:
      retType = irsdk_float;
    case VariableId::VertAccel_ST:
      retType = irsdk_float;
    case VariableId::LatAccel_ST:
      retType = irsdk_float;
    case VariableId::LongAccel_ST:
      retType = irsdk_float;
    case VariableId::VertAccel:
      retType = irsdk_float;
    case VariableId::LatAccel:
      retType = irsdk_float;
    case VariableId::LongAccel:
      retType = irsdk_float;
    case VariableId::dcStarter:
      retType = irsdk_bool;
    case VariableId::dcPitSpeedLimiterToggle:
      retType = irsdk_bool;
    case VariableId::dcDRSToggle:
      retType = irsdk_bool;
    case VariableId::dcTearOffVisor:
      retType = irsdk_bool;
    case VariableId::dpTireChange:
      retType = irsdk_float;
    case VariableId::dpFuelFill:
      retType = irsdk_float;
    case VariableId::dpFuelAddKg:
      retType = irsdk_float;
    case VariableId::dpFastRepair:
      retType = irsdk_float;
    case VariableId::dcDashPage:
      retType = irsdk_float;
    case VariableId::dcBrakeBias:
      retType = irsdk_float;
    case VariableId::dpLFTireColdPress:
      retType = irsdk_float;
    case VariableId::dpRFTireColdPress:
      retType = irsdk_float;
    case VariableId::dpLRTireColdPress:
      retType = irsdk_float;
    case VariableId::dpRRTireColdPress:
      retType = irsdk_float;
    case VariableId::dcThrottleShape:
      retType = irsdk_float;
    case VariableId::dcTractionControl:
      retType = irsdk_float;
    case VariableId::RFbrakeLinePress:
      retType = irsdk_float;
    case VariableId::RFcoldPressure:
      retType = irsdk_float;
    case VariableId::RFtempCL:
      retType = irsdk_float;
    case VariableId::RFtempCM:
      retType = irsdk_float;
    case VariableId::RFtempCR:
      retType = irsdk_float;
    case VariableId::RFwearL:
      retType = irsdk_float;
    case VariableId::RFwearM:
      retType = irsdk_float;
    case VariableId::RFwearR:
      retType = irsdk_float;
    case VariableId::LFbrakeLinePress:
      retType = irsdk_float;
    case VariableId::LFcoldPressure:
      retType = irsdk_float;
    case VariableId::LFtempCL:
      retType = irsdk_float;
    case VariableId::LFtempCM:
      retType = irsdk_float;
    case VariableId::LFtempCR:
      retType = irsdk_float;
    case VariableId::LFwearL:
      retType = irsdk_float;
    case VariableId::LFwearM:
      retType = irsdk_float;
    case VariableId::LFwearR:
      retType = irsdk_float;
    case VariableId::CFshockDefl:
      retType = irsdk_float;
    case VariableId::CFshockDefl_ST:
      retType = irsdk_float;
    case VariableId::CFshockVel:
      retType = irsdk_float;
    case VariableId::CFshockVel_ST:
      retType = irsdk_float;
    case VariableId::WaterTemp:
      retType = irsdk_float;
    case VariableId::WaterLevel:
      retType = irsdk_float;
    case VariableId::FuelPress:
      retType = irsdk_float;
    case VariableId::FuelUsePerHour:
      retType = irsdk_float;
    case VariableId::OilTemp:
      retType = irsdk_float;
    case VariableId::OilPress:
      retType = irsdk_float;
    case VariableId::OilLevel:
      retType = irsdk_float;
    case VariableId::Voltage:
      retType = irsdk_float;
    case VariableId::ManifoldPress:
      retType = irsdk_float;
    case VariableId::RRbrakeLinePress:
      retType = irsdk_float;
    case VariableId::RRcoldPressure:
      retType = irsdk_float;
    case VariableId::RRtempCL:
      retType = irsdk_float;
    case VariableId::RRtempCM:
      retType = irsdk_float;
    case VariableId::RRtempCR:
      retType = irsdk_float;
    case VariableId::RRwearL:
      retType = irsdk_float;
    case VariableId::RRwearM:
      retType = irsdk_float;
    case VariableId::RRwearR:
      retType = irsdk_float;
    case VariableId::LRbrakeLinePress:
      retType = irsdk_float;
    case VariableId::LRcoldPressure:
      retType = irsdk_float;
    case VariableId::LRtempCL:
      retType = irsdk_float;
    case VariableId::LRtempCM:
      retType = irsdk_float;
    case VariableId::LRtempCR:
      retType = irsdk_float;
    case VariableId::LRwearL:
      retType = irsdk_float;
    case VariableId::LRwearM:
      retType = irsdk_float;
    case VariableId::LRwearR:
      retType = irsdk_float;
    case VariableId::RRshockDefl:
      retType = irsdk_float;
    case VariableId::RRshockDefl_ST:
      retType = irsdk_float;
    case VariableId::RRshockVel:
      retType = irsdk_float;
    case VariableId::RRshockVel_ST:
      retType = irsdk_float;
    case VariableId::LRshockDefl:
      retType = irsdk_float;
    case VariableId::LRshockDefl_ST:
      retType = irsdk_float;
    case VariableId::LRshockVel:
      retType = irsdk_float;
    case VariableId::LRshockVel_ST:
      retType = irsdk_float;
    case VariableId::DRS_Status:
      retType = irsdk_int;
    case VariableId::DRS_Count:
      retType = irsdk_float;

    case VariableId::VariableUnknown:
      retType = irsdk_float;
    case VariableId::DerivedVelocityHeading:
      retType = irsdk_float;
    case VariableId::ProcessedDelta:
      retType = irsdk_float;
    case VariableId::ProcessedAverage:
      retType = irsdk_float;
  }
}
