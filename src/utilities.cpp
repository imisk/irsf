
#include "Utilities.h"

#include <stdlib.h>
#include <QtDebug>

/*
Various utility functions for the program
*/

namespace irsf {

VariableId GetVariableIdFromVariableName(const std::string& name) noexcept {
  if (name == "SessionTime")
    return VariableId::SessionTime;
  if (name == "SessionTick")
    return VariableId::SessionTick;
  if (name == "SessionNum")
    return VariableId::SessionNum;
  if (name == "SessionState")
    return VariableId::SessionState;
  if (name == "SessionUniqueID")
    return VariableId::SessionUniqueID;
  if (name == "SessionFlags")
    return VariableId::SessionFlags;
  if (name == "SessionTimeRemain")
    return VariableId::SessionTimeRemain;
  if (name == "SessionLapsRemain")
    return VariableId::SessionLapsRemain;
  if (name == "SessionLapsRemainEx")
    return VariableId::SessionLapsRemainEx;
  if (name == "SessionTimeOfDay")
    return VariableId::SessionTimeOfDay;
  if (name == "RadioTransmitCarIdx")
    return VariableId::RadioTransmitCarIdx;
  if (name == "RadioTransmitRadioIdx")
    return VariableId::RadioTransmitRadioIdx;
  if (name == "RadioTransmitFrequencyIdx")
    return VariableId::RadioTransmitFrequencyIdx;
  if (name == "DisplayUnits")
    return VariableId::DisplayUnits;
  if (name == "DriverMarker")
    return VariableId::DriverMarker;
  if (name == "PushToPass")
    return VariableId::PushToPass;
  if (name == "ManualBoost")
    return VariableId::ManualBoost;
  if (name == "ManualNoBoost")
    return VariableId::ManualNoBoost;
  if (name == "IsOnTrack")
    return VariableId::IsOnTrack;
  if (name == "IsReplayPlaying")
    return VariableId::IsReplayPlaying;
  if (name == "ReplayFrameNum")
    return VariableId::ReplayFrameNum;
  if (name == "ReplayFrameNumEnd")
    return VariableId::ReplayFrameNumEnd;
  if (name == "IsDiskLoggingEnabled")
    return VariableId::IsDiskLoggingEnabled;
  if (name == "IsDiskLoggingActive")
    return VariableId::IsDiskLoggingActive;
  if (name == "FrameRate")
    return VariableId::FrameRate;
  if (name == "CpuUsageBG")
    return VariableId::CpuUsageBG;
  if (name == "PlayerCarPosition")
    return VariableId::PlayerCarPosition;
  if (name == "PlayerCarClassPosition")
    return VariableId::PlayerCarClassPosition;
  if (name == "PlayerTrackSurface")
    return VariableId::PlayerTrackSurface;
  if (name == "PlayerTrackSurfaceMaterial")
    return VariableId::PlayerTrackSurfaceMaterial;
  if (name == "PlayerCarIdx")
    return VariableId::PlayerCarIdx;
  if (name == "PlayerCarTeamIncidentCount")
    return VariableId::PlayerCarTeamIncidentCount;
  if (name == "PlayerCarMyIncidentCount")
    return VariableId::PlayerCarMyIncidentCount;
  if (name == "PlayerCarDriverIncidentCount")
    return VariableId::PlayerCarDriverIncidentCount;
  if (name == "PlayerCarWeightPenalty")
    return VariableId::PlayerCarWeightPenalty;
  if (name == "PlayerCarPowerAdjust")
    return VariableId::PlayerCarPowerAdjust;
  if (name == "PlayerCarTowTime")
    return VariableId::PlayerCarTowTime;
  if (name == "PlayerCarInPitStall")
    return VariableId::PlayerCarInPitStall;
  if (name == "PlayerCarPitSvStatus")
    return VariableId::PlayerCarPitSvStatus;
  if (name == "CarIdxLap")
    return VariableId::CarIdxLap;
  if (name == "CarIdxLapCompleted")
    return VariableId::CarIdxLapCompleted;
  if (name == "CarIdxLapDistPct")
    return VariableId::CarIdxLapDistPct;
  if (name == "CarIdxTrackSurface")
    return VariableId::CarIdxTrackSurface;
  if (name == "CarIdxTrackSurfaceMaterial")
    return VariableId::CarIdxTrackSurfaceMaterial;
  if (name == "CarIdxOnPitRoad")
    return VariableId::CarIdxOnPitRoad;
  if (name == "CarIdxPosition")
    return VariableId::CarIdxPosition;
  if (name == "CarIdxClassPosition")
    return VariableId::CarIdxClassPosition;
  if (name == "CarIdxF2Time")
    return VariableId::CarIdxF2Time;
  if (name == "CarIdxEstTime")
    return VariableId::CarIdxEstTime;
  if (name == "CarIdxLastLapTime")
    return VariableId::CarIdxLastLapTime;
  if (name == "CarIdxBestLapTime")
    return VariableId::CarIdxBestLapTime;
  if (name == "CarIdxBestLapNum")
    return VariableId::CarIdxBestLapNum;
  if (name == "OnPitRoad")
    return VariableId::OnPitRoad;
  if (name == "CarIdxSteer")
    return VariableId::CarIdxSteer;
  if (name == "CarIdxRPM")
    return VariableId::CarIdxRPM;
  if (name == "CarIdxGear")
    return VariableId::CarIdxGear;
  if (name == "SteeringWheelAngle")
    return VariableId::SteeringWheelAngle;
  if (name == "Throttle")
    return VariableId::Throttle;
  if (name == "Brake")
    return VariableId::Brake;
  if (name == "Clutch")
    return VariableId::Clutch;
  if (name == "Gear")
    return VariableId::Gear;
  if (name == "RPM")
    return VariableId::RPM;
  if (name == "Lap")
    return VariableId::Lap;
  if (name == "LapCompleted")
    return VariableId::LapCompleted;
  if (name == "LapDist")
    return VariableId::LapDist;
  if (name == "LapDistPct")
    return VariableId::LapDistPct;
  if (name == "RaceLaps")
    return VariableId::RaceLaps;
  if (name == "LapBestLap")
    return VariableId::LapBestLap;
  if (name == "LapBestLapTime")
    return VariableId::LapBestLapTime;
  if (name == "LapLastLapTime")
    return VariableId::LapLastLapTime;
  if (name == "LapCurrentLapTime")
    return VariableId::LapCurrentLapTime;
  if (name == "LapLasNLapSeq")
    return VariableId::LapLasNLapSeq;
  if (name == "LapLastNLapTime")
    return VariableId::LapLastNLapTime;
  if (name == "LapBestNLapLap")
    return VariableId::LapBestNLapLap;
  if (name == "LapBestNLapTime")
    return VariableId::LapBestNLapTime;
  if (name == "LapDeltaToBestLap")
    return VariableId::LapDeltaToBestLap;
  if (name == "LapDeltaToBestLap_DD")
    return VariableId::LapDeltaToBestLap_DD;
  if (name == "LapDeltaToBestLap_OK")
    return VariableId::LapDeltaToBestLap_OK;
  if (name == "LapDeltaToOptimalLap")
    return VariableId::LapDeltaToOptimalLap;
  if (name == "LapDeltaToOptimalLap_DD")
    return VariableId::LapDeltaToOptimalLap_DD;
  if (name == "LapDeltaToOptimalLap_OK")
    return VariableId::LapDeltaToOptimalLap_OK;
  if (name == "LapDeltaToSessionBestLap")
    return VariableId::LapDeltaToSessionBestLap;
  if (name == "LapDeltaToSessionBestLap_DD")
    return VariableId::LapDeltaToSessionBestLap_DD;
  if (name == "LapDeltaToSessionBestLap_OK")
    return VariableId::LapDeltaToSessionBestLap_OK;
  if (name == "LapDeltaToSessionOptimalLap")
    return VariableId::LapDeltaToSessionOptimalLap;
  if (name == "LapDeltaToSessionOptimalLap_DD")
    return VariableId::LapDeltaToSessionOptimalLap_DD;
  if (name == "LapDeltaToSessionOptimalLap_OK")
    return VariableId::LapDeltaToSessionOptimalLap_OK;
  if (name == "LapDeltaToSessionLastlLap")
    return VariableId::LapDeltaToSessionLastlLap;
  if (name == "LapDeltaToSessionLastlLap_DD")
    return VariableId::LapDeltaToSessionLastlLap_DD;
  if (name == "LapDeltaToSessionLastlLap_OK")
    return VariableId::LapDeltaToSessionLastlLap_OK;
  if (name == "Speed")
    return VariableId::Speed;
  if (name == "Yaw")
    return VariableId::Yaw;
  if (name == "YawNorth")
    return VariableId::YawNorth;
  if (name == "Pitch")
    return VariableId::Pitch;
  if (name == "Roll")
    return VariableId::Roll;
  if (name == "EnterExitReset")
    return VariableId::EnterExitReset;
  if (name == "TrackTemp")
    return VariableId::TrackTemp;
  if (name == "TrackTempCrew")
    return VariableId::TrackTempCrew;
  if (name == "AirTemp")
    return VariableId::AirTemp;
  if (name == "WeatherType")
    return VariableId::WeatherType;
  if (name == "Skies")
    return VariableId::Skies;
  if (name == "AirDensity")
    return VariableId::AirDensity;
  if (name == "AirPressure")
    return VariableId::AirPressure;
  if (name == "WindVel")
    return VariableId::WindVel;
  if (name == "WindDir")
    return VariableId::WindDir;
  if (name == "RelativeHumidity")
    return VariableId::RelativeHumidity;
  if (name == "FogLevel")
    return VariableId::FogLevel;
  if (name == "DCLapStatus")
    return VariableId::DCLapStatus;
  if (name == "DCDriversSoFar")
    return VariableId::DCDriversSoFar;
  if (name == "OkToReloadTextures")
    return VariableId::OkToReloadTextures;
  if (name == "LoadNumTextures")
    return VariableId::LoadNumTextures;
  if (name == "CarLeftRight")
    return VariableId::CarLeftRight;
  if (name == "PitsOpen")
    return VariableId::PitsOpen;
  if (name == "PitRepairLeft")
    return VariableId::PitRepairLeft;
  if (name == "PitOptRepairLeft")
    return VariableId::PitOptRepairLeft;
  if (name == "PitstopActive")
    return VariableId::PitstopActive;
  if (name == "FastRepairUsed")
    return VariableId::FastRepairUsed;
  if (name == "FastRepairAvailable")
    return VariableId::FastRepairAvailable;
  if (name == "CamCarIdx")
    return VariableId::CamCarIdx;
  if (name == "CamCameraNumber")
    return VariableId::CamCameraNumber;
  if (name == "CamGroupNumber")
    return VariableId::CamGroupNumber;
  if (name == "CamCameraState")
    return VariableId::CamCameraState;
  if (name == "IsOnTrackCar")
    return VariableId::IsOnTrackCar;
  if (name == "IsInGarage")
    return VariableId::IsInGarage;
  if (name == "SteeringWheelPctTorque")
    return VariableId::SteeringWheelPctTorque;
  if (name == "SteeringWheelPctTorqueSign")
    return VariableId::SteeringWheelPctTorqueSign;
  if (name == "SteeringWheelPctTorqueSignStops")
    return VariableId::SteeringWheelPctTorqueSignStops;
  if (name == "SteeringWheelPctDamper")
    return VariableId::SteeringWheelPctDamper;
  if (name == "SteeringWheelAngleMax")
    return VariableId::SteeringWheelAngleMax;
  if (name == "ShiftIndicatorPct")
    return VariableId::ShiftIndicatorPct;
  if (name == "ShiftPowerPct")
    return VariableId::ShiftPowerPct;
  if (name == "ShiftGrindRPM")
    return VariableId::ShiftGrindRPM;
  if (name == "ThrottleRaw")
    return VariableId::ThrottleRaw;
  if (name == "BrakeRaw")
    return VariableId::BrakeRaw;
  if (name == "HandbrakeRaw")
    return VariableId::HandbrakeRaw;
  if (name == "SteeringWheelPeakForceNm")
    return VariableId::SteeringWheelPeakForceNm;
  if (name == "EngineWarnings")
    return VariableId::EngineWarnings;
  if (name == "FuelLevel")
    return VariableId::FuelLevel;
  if (name == "FuelLevelPct")
    return VariableId::FuelLevelPct;
  if (name == "PitSvFlags")
    return VariableId::PitSvFlags;
  if (name == "PitSvLFP")
    return VariableId::PitSvLFP;
  if (name == "PitSvRFP")
    return VariableId::PitSvRFP;
  if (name == "PitSvLRP")
    return VariableId::PitSvLRP;
  if (name == "PitSvRRP")
    return VariableId::PitSvRRP;
  if (name == "PitSvFuel")
    return VariableId::PitSvFuel;
  if (name == "CarIdxP2P_Status")
    return VariableId::CarIdxP2P_Status;
  if (name == "CarIdxP2P_Count")
    return VariableId::CarIdxP2P_Count;
  if (name == "ReplayPlaySpeed")
    return VariableId::ReplayPlaySpeed;
  if (name == "ReplayPlaySlowMotion")
    return VariableId::ReplayPlaySlowMotion;
  if (name == "ReplaySessionTime")
    return VariableId::ReplaySessionTime;
  if (name == "ReplaySessionNum")
    return VariableId::ReplaySessionNum;
  if (name == "TireLF_RumblePitch")
    return VariableId::TireLF_RumblePitch;
  if (name == "TireRF_RumblePitch")
    return VariableId::TireRF_RumblePitch;
  if (name == "TireLR_RumblePitch")
    return VariableId::TireLR_RumblePitch;
  if (name == "TireRR_RumblePitch")
    return VariableId::TireRR_RumblePitch;
  if (name == "SteeringWheelTorque_ST")
    return VariableId::SteeringWheelTorque_ST;
  if (name == "SteeringWheelTorque")
    return VariableId::SteeringWheelTorque;
  if (name == "VelocityZ_ST")
    return VariableId::VelocityZ_ST;
  if (name == "VelocityY_ST")
    return VariableId::VelocityY_ST;
  if (name == "VelocityX_ST")
    return VariableId::VelocityX_ST;
  if (name == "VelocityZ")
    return VariableId::VelocityZ;
  if (name == "VelocityY")
    return VariableId::VelocityY;
  if (name == "VelocityX")
    return VariableId::VelocityX;
  if (name == "YawRate_ST")
    return VariableId::YawRate_ST;
  if (name == "PitchRate_ST")
    return VariableId::PitchRate_ST;
  if (name == "RollRate_ST")
    return VariableId::RollRate_ST;
  if (name == "YawRate")
    return VariableId::YawRate;
  if (name == "PitchRate")
    return VariableId::PitchRate;
  if (name == "RollRate")
    return VariableId::RollRate;
  if (name == "VertAccel_ST")
    return VariableId::VertAccel_ST;
  if (name == "LatAccel_ST")
    return VariableId::LatAccel_ST;
  if (name == "LongAccel_ST")
    return VariableId::LongAccel_ST;
  if (name == "VertAccel")
    return VariableId::VertAccel;
  if (name == "LatAccel")
    return VariableId::LatAccel;
  if (name == "LongAccel")
    return VariableId::LongAccel;
  if (name == "dcStarter")
    return VariableId::dcStarter;
  if (name == "dcPitSpeedLimiterToggle")
    return VariableId::dcPitSpeedLimiterToggle;
  if (name == "dcDRSToggle")
    return VariableId::dcDRSToggle;
  if (name == "dcTearOffVisor")
    return VariableId::dcTearOffVisor;
  if (name == "dpTireChange")
    return VariableId::dpTireChange;
  if (name == "dpFuelFill")
    return VariableId::dpFuelFill;
  if (name == "dpFuelAddKg")
    return VariableId::dpFuelAddKg;
  if (name == "dpFastRepair")
    return VariableId::dpFastRepair;
  if (name == "dcDashPage")
    return VariableId::dcDashPage;
  if (name == "dcBrakeBias")
    return VariableId::dcBrakeBias;
  if (name == "dpLFTireColdPress")
    return VariableId::dpLFTireColdPress;
  if (name == "dpRFTireColdPress")
    return VariableId::dpRFTireColdPress;
  if (name == "dpLRTireColdPress")
    return VariableId::dpLRTireColdPress;
  if (name == "dpRRTireColdPress")
    return VariableId::dpRRTireColdPress;
  if (name == "dcThrottleShape")
    return VariableId::dcThrottleShape;
  if (name == "dcTractionControl")
    return VariableId::dcTractionControl;
  if (name == "RFbrakeLinePress")
    return VariableId::RFbrakeLinePress;
  if (name == "RFcoldPressure")
    return VariableId::RFcoldPressure;
  if (name == "RFtempCL")
    return VariableId::RFtempCL;
  if (name == "RFtempCM")
    return VariableId::RFtempCM;
  if (name == "RFtempCR")
    return VariableId::RFtempCR;
  if (name == "RFwearL")
    return VariableId::RFwearL;
  if (name == "RFwearM")
    return VariableId::RFwearM;
  if (name == "RFwearR")
    return VariableId::RFwearR;
  if (name == "LFbrakeLinePress")
    return VariableId::LFbrakeLinePress;
  if (name == "LFcoldPressure")
    return VariableId::LFcoldPressure;
  if (name == "LFtempCL")
    return VariableId::LFtempCL;
  if (name == "LFtempCM")
    return VariableId::LFtempCM;
  if (name == "LFtempCR")
    return VariableId::LFtempCR;
  if (name == "LFwearL")
    return VariableId::LFwearL;
  if (name == "LFwearM")
    return VariableId::LFwearM;
  if (name == "LFwearR")
    return VariableId::LFwearR;
  if (name == "CFshockDefl")
    return VariableId::CFshockDefl;
  if (name == "CFshockDefl_ST")
    return VariableId::CFshockDefl_ST;
  if (name == "CFshockVel")
    return VariableId::CFshockVel;
  if (name == "CFshockVel_ST")
    return VariableId::CFshockVel_ST;
  if (name == "WaterTemp")
    return VariableId::WaterTemp;
  if (name == "WaterLevel")
    return VariableId::WaterLevel;
  if (name == "FuelPress")
    return VariableId::FuelPress;
  if (name == "FuelUsePerHour")
    return VariableId::FuelUsePerHour;
  if (name == "OilTemp")
    return VariableId::OilTemp;
  if (name == "OilPress")
    return VariableId::OilPress;
  if (name == "OilLevel")
    return VariableId::OilLevel;
  if (name == "Voltage")
    return VariableId::Voltage;
  if (name == "ManifoldPress")
    return VariableId::ManifoldPress;
  if (name == "RRbrakeLinePress")
    return VariableId::RRbrakeLinePress;
  if (name == "RRcoldPressure")
    return VariableId::RRcoldPressure;
  if (name == "RRtempCL")
    return VariableId::RRtempCL;
  if (name == "RRtempCM")
    return VariableId::RRtempCM;
  if (name == "RRtempCR")
    return VariableId::RRtempCR;
  if (name == "RRwearL")
    return VariableId::RRwearL;
  if (name == "RRwearM")
    return VariableId::RRwearM;
  if (name == "RRwearR")
    return VariableId::RRwearR;
  if (name == "LRbrakeLinePress")
    return VariableId::LRbrakeLinePress;
  if (name == "LRcoldPressure")
    return VariableId::LRcoldPressure;
  if (name == "LRtempCL")
    return VariableId::LRtempCL;
  if (name == "LRtempCM")
    return VariableId::LRtempCM;
  if (name == "LRtempCR")
    return VariableId::LRtempCR;
  if (name == "LRwearL")
    return VariableId::LRwearL;
  if (name == "LRwearM")
    return VariableId::LRwearM;
  if (name == "LRwearR")
    return VariableId::LRwearR;
  if (name == "RRshockDefl")
    return VariableId::RRshockDefl;
  if (name == "RRshockDefl_ST")
    return VariableId::RRshockDefl_ST;
  if (name == "RRshockVel")
    return VariableId::RRshockVel;
  if (name == "RRshockVel_ST")
    return VariableId::RRshockVel_ST;
  if (name == "LRshockDefl")
    return VariableId::LRshockDefl;
  if (name == "LRshockDefl_ST")
    return VariableId::LRshockDefl_ST;
  if (name == "LRshockVel")
    return VariableId::LRshockVel;
  if (name == "LRshockVel_ST")
    return VariableId::LRshockVel_ST;
  if (name == "DRS_Status")
    return VariableId::DRS_Status;
  if (name == "DRS_Count")
    return VariableId::DRS_Count;

  return VariableId::VariableUnknown;
}

std::string GetVariableNameFromVariableId(const VariableId& id) noexcept {
  switch (id) {
    case VariableId::SessionTime:
      return "SessionTime";
    case VariableId::SessionTick:
      return "SessionTick";
    case VariableId::SessionNum:
      return "SessionNum";
    case VariableId::SessionState:
      return "SessionState";
    case VariableId::SessionUniqueID:
      return "SessionUniqueID";
    case VariableId::SessionFlags:
      return "SessionFlags";
    case VariableId::SessionTimeRemain:
      return "SessionTimeRemain";
    case VariableId::SessionLapsRemain:
      return "SessionLapsRemain";
    case VariableId::SessionLapsRemainEx:
      return "SessionLapsRemainEx";
    case VariableId::SessionTimeOfDay:
      return "SessionTimeOfDay";
    case VariableId::RadioTransmitCarIdx:
      return "RadioTransmitCarIdx";
    case VariableId::RadioTransmitRadioIdx:
      return "RadioTransmitRadioIdx";
    case VariableId::RadioTransmitFrequencyIdx:
      return "RadioTransmitFrequencyIdx";
    case VariableId::DisplayUnits:
      return "DisplayUnits";
    case VariableId::DriverMarker:
      return "DriverMarker";
    case VariableId::PushToPass:
      return "PushToPass";
    case VariableId::ManualBoost:
      return "ManualBoost";
    case VariableId::ManualNoBoost:
      return "ManualNoBoost";
    case VariableId::IsOnTrack:
      return "IsOnTrack";
    case VariableId::IsReplayPlaying:
      return "IsReplayPlaying";
    case VariableId::ReplayFrameNum:
      return "ReplayFrameNum";
    case VariableId::ReplayFrameNumEnd:
      return "ReplayFrameNumEnd";
    case VariableId::IsDiskLoggingEnabled:
      return "IsDiskLoggingEnabled";
    case VariableId::IsDiskLoggingActive:
      return "IsDiskLoggingActive";
    case VariableId::FrameRate:
      return "FrameRate";
    case VariableId::CpuUsageBG:
      return "CpuUsageBG";
    case VariableId::PlayerCarPosition:
      return "PlayerCarPosition";
    case VariableId::PlayerCarClassPosition:
      return "PlayerCarClassPosition";
    case VariableId::PlayerTrackSurface:
      return "PlayerTrackSurface";
    case VariableId::PlayerTrackSurfaceMaterial:
      return "PlayerTrackSurfaceMaterial";
    case VariableId::PlayerCarIdx:
      return "PlayerCarIdx";
    case VariableId::PlayerCarTeamIncidentCount:
      return "PlayerCarTeamIncidentCount";
    case VariableId::PlayerCarMyIncidentCount:
      return "PlayerCarMyIncidentCount";
    case VariableId::PlayerCarDriverIncidentCount:
      return "PlayerCarDriverIncidentCount";
    case VariableId::PlayerCarWeightPenalty:
      return "PlayerCarWeightPenalty";
    case VariableId::PlayerCarPowerAdjust:
      return "PlayerCarPowerAdjust";
    case VariableId::PlayerCarTowTime:
      return "PlayerCarTowTime";
    case VariableId::PlayerCarInPitStall:
      return "PlayerCarInPitStall";
    case VariableId::PlayerCarPitSvStatus:
      return "PlayerCarPitSvStatus";
    case VariableId::CarIdxLap:
      return "CarIdxLap";
    case VariableId::CarIdxLapCompleted:
      return "CarIdxLapCompleted";
    case VariableId::CarIdxLapDistPct:
      return "CarIdxLapDistPct";
    case VariableId::CarIdxTrackSurface:
      return "CarIdxTrackSurface";
    case VariableId::CarIdxTrackSurfaceMaterial:
      return "CarIdxTrackSurfaceMaterial";
    case VariableId::CarIdxOnPitRoad:
      return "CarIdxOnPitRoad";
    case VariableId::CarIdxPosition:
      return "CarIdxPosition";
    case VariableId::CarIdxClassPosition:
      return "CarIdxClassPosition";
    case VariableId::CarIdxF2Time:
      return "CarIdxF2Time";
    case VariableId::CarIdxEstTime:
      return "CarIdxEstTime";
    case VariableId::CarIdxLastLapTime:
      return "CarIdxLastLapTime";
    case VariableId::CarIdxBestLapTime:
      return "CarIdxBestLapTime";
    case VariableId::CarIdxBestLapNum:
      return "CarIdxBestLapNum";
    case VariableId::OnPitRoad:
      return "OnPitRoad";
    case VariableId::CarIdxSteer:
      return "CarIdxSteer";
    case VariableId::CarIdxRPM:
      return "CarIdxRPM";
    case VariableId::CarIdxGear:
      return "CarIdxGear";
    case VariableId::SteeringWheelAngle:
      return "SteeringWheelAngle";
    case VariableId::Throttle:
      return "Throttle";
    case VariableId::Brake:
      return "Brake";
    case VariableId::Clutch:
      return "Clutch";
    case VariableId::Gear:
      return "Gear";
    case VariableId::RPM:
      return "RPM";
    case VariableId::Lap:
      return "Lap";
    case VariableId::LapCompleted:
      return "LapCompleted";
    case VariableId::LapDist:
      return "LapDist";
    case VariableId::LapDistPct:
      return "LapDistPct";
    case VariableId::RaceLaps:
      return "RaceLaps";
    case VariableId::LapBestLap:
      return "LapBestLap";
    case VariableId::LapBestLapTime:
      return "LapBestLapTime";
    case VariableId::LapLastLapTime:
      return "LapLastLapTime";
    case VariableId::LapCurrentLapTime:
      return "LapCurrentLapTime";
    case VariableId::LapLasNLapSeq:
      return "LapLasNLapSeq";
    case VariableId::LapLastNLapTime:
      return "LapLastNLapTime";
    case VariableId::LapBestNLapLap:
      return "LapBestNLapLap";
    case VariableId::LapBestNLapTime:
      return "LapBestNLapTime";
    case VariableId::LapDeltaToBestLap:
      return "LapDeltaToBestLap";
    case VariableId::LapDeltaToBestLap_DD:
      return "LapDeltaToBestLap_DD";
    case VariableId::LapDeltaToBestLap_OK:
      return "LapDeltaToBestLap_OK";
    case VariableId::LapDeltaToOptimalLap:
      return "LapDeltaToOptimalLap";
    case VariableId::LapDeltaToOptimalLap_DD:
      return "LapDeltaToOptimalLap_DD";
    case VariableId::LapDeltaToOptimalLap_OK:
      return "LapDeltaToOptimalLap_OK";
    case VariableId::LapDeltaToSessionBestLap:
      return "LapDeltaToSessionBestLap";
    case VariableId::LapDeltaToSessionBestLap_DD:
      return "LapDeltaToSessionBestLap_DD";
    case VariableId::LapDeltaToSessionBestLap_OK:
      return "LapDeltaToSessionBestLap_OK";
    case VariableId::LapDeltaToSessionOptimalLap:
      return "LapDeltaToSessionOptimalLap";
    case VariableId::LapDeltaToSessionOptimalLap_DD:
      return "LapDeltaToSessionOptimalLap_DD";
    case VariableId::LapDeltaToSessionOptimalLap_OK:
      return "LapDeltaToSessionOptimalLap_OK";
    case VariableId::LapDeltaToSessionLastlLap:
      return "LapDeltaToSessionLastlLap";
    case VariableId::LapDeltaToSessionLastlLap_DD:
      return "LapDeltaToSessionLastlLap_DD";
    case VariableId::LapDeltaToSessionLastlLap_OK:
      return "LapDeltaToSessionLastlLap_OK";
    case VariableId::Speed:
      return "Speed";
    case VariableId::Yaw:
      return "Yaw";
    case VariableId::YawNorth:
      return "YawNorth";
    case VariableId::Pitch:
      return "Pitch";
    case VariableId::Roll:
      return "Roll";
    case VariableId::EnterExitReset:
      return "EnterExitReset";
    case VariableId::TrackTemp:
      return "TrackTemp";
    case VariableId::TrackTempCrew:
      return "TrackTempCrew";
    case VariableId::AirTemp:
      return "AirTemp";
    case VariableId::WeatherType:
      return "WeatherType";
    case VariableId::Skies:
      return "Skies";
    case VariableId::AirDensity:
      return "AirDensity";
    case VariableId::AirPressure:
      return "AirPressure";
    case VariableId::WindVel:
      return "WindVel";
    case VariableId::WindDir:
      return "WindDir";
    case VariableId::RelativeHumidity:
      return "RelativeHumidity";
    case VariableId::FogLevel:
      return "FogLevel";
    case VariableId::DCLapStatus:
      return "DCLapStatus";
    case VariableId::DCDriversSoFar:
      return "DCDriversSoFar";
    case VariableId::OkToReloadTextures:
      return "OkToReloadTextures";
    case VariableId::LoadNumTextures:
      return "LoadNumTextures";
    case VariableId::CarLeftRight:
      return "CarLeftRight";
    case VariableId::PitsOpen:
      return "PitsOpen";
    case VariableId::PitRepairLeft:
      return "PitRepairLeft";
    case VariableId::PitOptRepairLeft:
      return "PitOptRepairLeft";
    case VariableId::PitstopActive:
      return "PitstopActive";
    case VariableId::FastRepairUsed:
      return "FastRepairUsed";
    case VariableId::FastRepairAvailable:
      return "FastRepairAvailable";
    case VariableId::CamCarIdx:
      return "CamCarIdx";
    case VariableId::CamCameraNumber:
      return "CamCameraNumber";
    case VariableId::CamGroupNumber:
      return "CamGroupNumber";
    case VariableId::CamCameraState:
      return "CamCameraState";
    case VariableId::IsOnTrackCar:
      return "IsOnTrackCar";
    case VariableId::IsInGarage:
      return "IsInGarage";
    case VariableId::SteeringWheelPctTorque:
      return "SteeringWheelPctTorque";
    case VariableId::SteeringWheelPctTorqueSign:
      return "SteeringWheelPctTorqueSign";
    case VariableId::SteeringWheelPctTorqueSignStops:
      return "SteeringWheelPctTorqueSignStops";
    case VariableId::SteeringWheelPctDamper:
      return "SteeringWheelPctDamper";
    case VariableId::SteeringWheelAngleMax:
      return "SteeringWheelAngleMax";
    case VariableId::ShiftIndicatorPct:
      return "ShiftIndicatorPct";
    case VariableId::ShiftPowerPct:
      return "ShiftPowerPct";
    case VariableId::ShiftGrindRPM:
      return "ShiftGrindRPM";
    case VariableId::ThrottleRaw:
      return "ThrottleRaw";
    case VariableId::BrakeRaw:
      return "BrakeRaw";
    case VariableId::HandbrakeRaw:
      return "HandbrakeRaw";
    case VariableId::SteeringWheelPeakForceNm:
      return "SteeringWheelPeakForceNm";
    case VariableId::EngineWarnings:
      return "EngineWarnings";
    case VariableId::FuelLevel:
      return "FuelLevel";
    case VariableId::FuelLevelPct:
      return "FuelLevelPct";
    case VariableId::PitSvFlags:
      return "PitSvFlags";
    case VariableId::PitSvLFP:
      return "PitSvLFP";
    case VariableId::PitSvRFP:
      return "PitSvRFP";
    case VariableId::PitSvLRP:
      return "PitSvLRP";
    case VariableId::PitSvRRP:
      return "PitSvRRP";
    case VariableId::PitSvFuel:
      return "PitSvFuel";
    case VariableId::CarIdxP2P_Status:
      return "CarIdxP2P_Status";
    case VariableId::CarIdxP2P_Count:
      return "CarIdxP2P_Count";
    case VariableId::ReplayPlaySpeed:
      return "ReplayPlaySpeed";
    case VariableId::ReplayPlaySlowMotion:
      return "ReplayPlaySlowMotion";
    case VariableId::ReplaySessionTime:
      return "ReplaySessionTime";
    case VariableId::ReplaySessionNum:
      return "ReplaySessionNum";
    case VariableId::TireLF_RumblePitch:
      return "TireLF_RumblePitch";
    case VariableId::TireRF_RumblePitch:
      return "TireRF_RumblePitch";
    case VariableId::TireLR_RumblePitch:
      return "TireLR_RumblePitch";
    case VariableId::TireRR_RumblePitch:
      return "TireRR_RumblePitch";
    case VariableId::SteeringWheelTorque_ST:
      return "SteeringWheelTorque_ST";
    case VariableId::SteeringWheelTorque:
      return "SteeringWheelTorque";
    case VariableId::VelocityZ_ST:
      return "VelocityZ_ST";
    case VariableId::VelocityY_ST:
      return "VelocityY_ST";
    case VariableId::VelocityX_ST:
      return "VelocityX_ST";
    case VariableId::VelocityZ:
      return "VelocityZ";
    case VariableId::VelocityY:
      return "VelocityY";
    case VariableId::VelocityX:
      return "VelocityX";
    case VariableId::YawRate_ST:
      return "YawRate_ST";
    case VariableId::PitchRate_ST:
      return "PitchRate_ST";
    case VariableId::RollRate_ST:
      return "RollRate_ST";
    case VariableId::YawRate:
      return "YawRate";
    case VariableId::PitchRate:
      return "PitchRate";
    case VariableId::RollRate:
      return "RollRate";
    case VariableId::VertAccel_ST:
      return "VertAccel_ST";
    case VariableId::LatAccel_ST:
      return "LatAccel_ST";
    case VariableId::LongAccel_ST:
      return "LongAccel_ST";
    case VariableId::VertAccel:
      return "VertAccel";
    case VariableId::LatAccel:
      return "LatAccel";
    case VariableId::LongAccel:
      return "LongAccel";
    case VariableId::dcStarter:
      return "dcStarter";
    case VariableId::dcPitSpeedLimiterToggle:
      return "dcPitSpeedLimiterToggle";
    case VariableId::dcDRSToggle:
      return "dcDRSToggle";
    case VariableId::dcTearOffVisor:
      return "dcTearOffVisor";
    case VariableId::dpTireChange:
      return "dpTireChange";
    case VariableId::dpFuelFill:
      return "dpFuelFill";
    case VariableId::dpFuelAddKg:
      return "dpFuelAddKg";
    case VariableId::dpFastRepair:
      return "dpFastRepair";
    case VariableId::dcDashPage:
      return "dcDashPage";
    case VariableId::dcBrakeBias:
      return "dcBrakeBias";
    case VariableId::dpLFTireColdPress:
      return "dpLFTireColdPress";
    case VariableId::dpRFTireColdPress:
      return "dpRFTireColdPress";
    case VariableId::dpLRTireColdPress:
      return "dpLRTireColdPress";
    case VariableId::dpRRTireColdPress:
      return "dpRRTireColdPress";
    case VariableId::dcThrottleShape:
      return "dcThrottleShape";
    case VariableId::dcTractionControl:
      return "dcTractionControl";
    case VariableId::RFbrakeLinePress:
      return "RFbrakeLinePress";
    case VariableId::RFcoldPressure:
      return "RFcoldPressure";
    case VariableId::RFtempCL:
      return "RFtempCL";
    case VariableId::RFtempCM:
      return "RFtempCM";
    case VariableId::RFtempCR:
      return "RFtempCR";
    case VariableId::RFwearL:
      return "RFwearL";
    case VariableId::RFwearM:
      return "RFwearM";
    case VariableId::RFwearR:
      return "RFwearR";
    case VariableId::LFbrakeLinePress:
      return "LFbrakeLinePress";
    case VariableId::LFcoldPressure:
      return "LFcoldPressure";
    case VariableId::LFtempCL:
      return "LFtempCL";
    case VariableId::LFtempCM:
      return "LFtempCM";
    case VariableId::LFtempCR:
      return "LFtempCR";
    case VariableId::LFwearL:
      return "LFwearL";
    case VariableId::LFwearM:
      return "LFwearM";
    case VariableId::LFwearR:
      return "LFwearR";
    case VariableId::CFshockDefl:
      return "CFshockDefl";
    case VariableId::CFshockDefl_ST:
      return "CFshockDefl_ST";
    case VariableId::CFshockVel:
      return "CFshockVel";
    case VariableId::CFshockVel_ST:
      return "CFshockVel_ST";
    case VariableId::WaterTemp:
      return "WaterTemp";
    case VariableId::WaterLevel:
      return "WaterLevel";
    case VariableId::FuelPress:
      return "FuelPress";
    case VariableId::FuelUsePerHour:
      return "FuelUsePerHour";
    case VariableId::OilTemp:
      return "OilTemp";
    case VariableId::OilPress:
      return "OilPress";
    case VariableId::OilLevel:
      return "OilLevel";
    case VariableId::Voltage:
      return "Voltage";
    case VariableId::ManifoldPress:
      return "ManifoldPress";
    case VariableId::RRbrakeLinePress:
      return "RRbrakeLinePress";
    case VariableId::RRcoldPressure:
      return "RRcoldPressure";
    case VariableId::RRtempCL:
      return "RRtempCL";
    case VariableId::RRtempCM:
      return "RRtempCM";
    case VariableId::RRtempCR:
      return "RRtempCR";
    case VariableId::RRwearL:
      return "RRwearL";
    case VariableId::RRwearM:
      return "RRwearM";
    case VariableId::RRwearR:
      return "RRwearR";
    case VariableId::LRbrakeLinePress:
      return "LRbrakeLinePress";
    case VariableId::LRcoldPressure:
      return "LRcoldPressure";
    case VariableId::LRtempCL:
      return "LRtempCL";
    case VariableId::LRtempCM:
      return "LRtempCM";
    case VariableId::LRtempCR:
      return "LRtempCR";
    case VariableId::LRwearL:
      return "LRwearL";
    case VariableId::LRwearM:
      return "LRwearM";
    case VariableId::LRwearR:
      return "LRwearR";
    case VariableId::RRshockDefl:
      return "RRshockDefl";
    case VariableId::RRshockDefl_ST:
      return "RRshockDefl_ST";
    case VariableId::RRshockVel:
      return "RRshockVel";
    case VariableId::RRshockVel_ST:
      return "RRshockVel_ST";
    case VariableId::LRshockDefl:
      return "LRshockDefl";
    case VariableId::LRshockDefl_ST:
      return "LRshockDefl_ST";
    case VariableId::LRshockVel:
      return "LRshockVel";
    case VariableId::LRshockVel_ST:
      return "LRshockVel_ST";
    case VariableId::DRS_Status:
      return "DRS_Status";
    case VariableId::DRS_Count:
      return "DRS_Count";

    case VariableId::VariableUnknown:
      return "VariableUnknown";

    case VariableId::DerivedVelocityHeading:
      return "DerivedVelocityHeading";

    case VariableId::ProcessedAverage:
      return "ProcessedAverage";
    case VariableId::ProcessedDelta:
      return "ProcessedDelta";
  }

  return "InvalidId";
}

std::vector<std::string> GetNamesOfAllInputVariableRawAndDerived() {
  std::vector<std::string> returnValues;

  for (int32_t curId = 1; curId < kVariableProcessedIdStart; curId++) {
    std::string varName =
        irsf::GetVariableNameFromVariableId(static_cast<VariableId>(curId));

    if (varName != "InvalidId") {
      returnValues.push_back(varName);
    }
  }

  return returnValues;
}

void CreateDataSeriesFromTelemetry(
    TelemetryViewerOptionsForChart& options,
    QChart* chart,
    TelemetryData* data,
    const std::vector<QBrush>& variableIdColours) {
  std::vector<TelemetryChartDataPoint> dp;

  QLineSeries* series;

  bool normalised = false;

  if (options.variableList.size() > 1)
    normalised = true;

  chart->legend()->hide();

  if (options.ShowAllLaps == true) {
    options.lapList.clear();
    for (const auto& lapItm : data->LapIndex) {
      options.lapList.push_back(lapItm.first);
    }
  }

  size_t totalValuesFound = 0;

  for (const auto& currentLapNumber : options.lapList) {
    size_t currentVariableColour = 0;

    for (const auto& currentVariableId : options.variableList) {
      dp.clear();

      GetSingleDataSeries(data, dp, currentLapNumber, options.DistanceStart,
                          options.DistanceEnd, currentVariableId, normalised);

      totalValuesFound += dp.size();

      series = new QLineSeries();

      QPen pen = series->pen();
      pen.setWidth(1);
      pen.setBrush(variableIdColours[currentVariableColour]);
      series->setPen(pen);

      currentVariableColour++;

      float prevDistance = 0.0f;

      for (const auto& point : dp) {
        if (point.Distance > prevDistance) {
          series->append(static_cast<qreal>(point.Distance),
                         static_cast<qreal>(point.Value));

          prevDistance = point.Distance;
        }
      }

      chart->addSeries(series);
    }
  }

  if (totalValuesFound == 0) {
    std::cout << "Error : there are no values in the telemetry file for the "
                 "data ranges (laps) you selected! \n";
    throw IrsfException(IrsfError::NoValuesInSelectedTelemetryRange);
  }

  chart->createDefaultAxes();

  QAbstractAxis* x = chart->axisX();

  x->setRange(options.DistanceStart, options.DistanceEnd);
}

void CreateIntListFromCommaDelimitedText(std::vector<int32_t>& retVector,
                                         QString& inString) {
  std::string commaDelimited = inString.toStdString();

  if (commaDelimited.size() == 0)
    throw IrsfException(IrsfError::NoLapsSelectedForTelemetry);

  std::vector<std::string> foundItems;

  std::stringstream sstreamCD(commaDelimited);

  while (sstreamCD.good()) {
    std::string itemStr;
    getline(sstreamCD, itemStr, ',');
    foundItems.push_back(itemStr);
  }

  retVector.clear();

  for (const auto& s : foundItems) {
    int32_t lapNumber;

    lapNumber = -1;
    try {
      lapNumber = std::stoi(s);
    } catch (...) {
      // just ignore bad inputs
    }

    if (lapNumber > -1) {
      retVector.push_back(lapNumber);
    }
  }

  if (retVector.size() == 0)
    throw IrsfException(IrsfError::NoLapsSelectedForTelemetry);
}

void NormaliseFloatVector(std::vector<TelemetryChartDataPoint>& values,
                          float maxValue) noexcept {
  // find max and multiply all values with it

  float multiplier = 1.0f / maxValue;

  for (size_t i = 0; i < values.size(); i++) {
    values[i].Value = values[i].Value * multiplier;
  }
}

void GetSingleDataSeries(TelemetryData* data,
                         std::vector<TelemetryChartDataPoint>& retValues,
                         int32_t lapNumber,
                         float minimumDistance,
                         float maximumDistance,
                         VariableId varId,
                         bool isNormalized) {
  retValues.clear();

  // Find offsets
  size_t offsetLapDistance = kIrsdkMaxVariableId;
  size_t offsetVariable = kIrsdkMaxVariableId;

  for (size_t i = 0; i < data->Variables.size(); i++) {
    if (data->Variables[i] == VariableId::LapDist)
      offsetLapDistance = i;

    if (data->Variables[i] == varId)
      offsetVariable = i;
  }

  if (offsetLapDistance == kIrsdkMaxVariableId ||
      offsetVariable == kIrsdkMaxVariableId)
    throw IrsfException(IrsfError::TelemetryDoesNotContainRequiredVariableId);

  // Find lap vector
  size_t indexOfLap = 0;

  if (data->LapIndex.find(lapNumber) != data->LapIndex.end())
    indexOfLap = data->LapIndex.at(lapNumber);  // data.LapIndex[lapNumber];
  else
    throw IrsfException(IrsfError::TelemetryDoesNotContainRequiredLapNumber);

  std::vector<float> lapData = data->Data[indexOfLap];

  // Populate data
  float maxValueFound = std::numeric_limits<float>::min();

  for (size_t currentTickOffset0 = 0; currentTickOffset0 < lapData.size();
       currentTickOffset0 += data->Variables.size()) {
    float currentDistanceValue =
        lapData[currentTickOffset0 + offsetLapDistance];

    float curVarValue = lapData[currentTickOffset0 + offsetVariable];

    maxValueFound = std::max(curVarValue, maxValueFound);

    if (currentDistanceValue > minimumDistance &&
        currentDistanceValue < maximumDistance) {
      retValues.push_back({curVarValue, currentDistanceValue});
    }
  }

  if (isNormalized)
    irsf::NormaliseFloatVector(retValues, maxValueFound);
}

void FindMaxValueOfVariable(TelemetryData* data,
                            VariableId varId,
                            float& retValue) {
  size_t varOffset;

  bool found = false;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (data->Variables[i] == varId) {
      varOffset = i;
      found = true;
      finished = true;
    }

    ++i;
    if (i == data->Variables.size())
      finished = true;
  }

  if (!found)
    throw IrsfException(IrsfError::TelemetryDoesNotContainRequiredVariableId);

  float maxValueFound = std::numeric_limits<float>::min();

  for (const auto& curLapData : data->Data) {
    for (size_t offset = 0; offset < curLapData.size();
         offset += data->Variables.size()) {
      float value = curLapData[offset + varOffset];

      maxValueFound = std::max(value, maxValueFound);
    }
  }

  retValue = maxValueFound;
}

bool IsVariableIdForProcessedVariable(VariableId varId) noexcept {
  if (static_cast<int32_t>(varId) >= kVariableProcessedIdStart)

    return true;

  return false;
}

void FindMeanAndStdDevTelemetryData(
    std::vector<std::vector<TelemetryChartDataPoint>> data,
    float& retMean,
    float& retStdDev,
    float& retMinValue,
    float& retMaxValue,
    float& retMinDist,
    float& retMaxDist) noexcept {
  float Sum = 0.0f;
  float count = 0.0;

  retMinValue = FLT_MAX;
  retMinDist = FLT_MAX;

  retMaxValue = FLT_MIN;
  retMaxDist = FLT_MIN;

  for (const auto& curLap : data) {
    for (const auto& p : curLap) {
      if (p.Value < retMinValue)
        retMinValue = p.Value;
      if (p.Distance < retMinDist)
        retMinDist = p.Distance;
      if (p.Value > retMaxValue)
        retMaxValue = p.Value;
      if (p.Distance > retMaxDist)
        retMaxDist = p.Distance;

      Sum += p.Value;
      count += 1;
    }
  }

  retMean = Sum / count;

  float StdDevSum = 0.0f;

  for (const auto& curLap : data) {
    for (const auto& p : curLap) {
      float delta = p.Value - retMean;
      StdDevSum += (delta * delta);
    }
  }

  retStdDev = sqrt(StdDevSum / count);

  std::cout << "Chart value range is from " << retMinValue << " to "
            << retMaxValue << std::endl;
  std::cout << "Chart distance range is from " << retMinDist << " to "
            << retMaxDist << std::endl;
};

std::string BrakeMarkerToString(BrakeMarker& bm) {
  int32_t dist = static_cast<int32_t>(bm.distancePosition);
  int32_t speed = static_cast<int32_t>(bm.speedAtMarker);

  char dist_c[20];
  _itoa(dist, dist_c, 10);

  char speed_c[20];
  _itoa(speed, speed_c, 10);

  std::string dist_s(dist_c);
  std::string speed_s(speed_c);

  std::string ret = "distance: " + dist_s + ", speed: " + speed_s;

  return ret;
}

}  // namespace irsf
