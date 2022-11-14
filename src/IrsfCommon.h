#ifndef IRSFCOMMON_H
#define IRSFCOMMON_H

#include <format>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include "sndfile.h"
namespace irsf {

/*
 *
 */
constexpr int32_t kIrsdkMaxVariableId = 999;

constexpr int32_t kMaxVariableIdDerived = 1999;

constexpr int32_t kMaxVariableAll = 9999;

constexpr int32_t kIdNotSelected = -1;

/*
 * This is the TRACK_ID number which signifies an object belongs to
 * "All tracks"
 */
constexpr int32_t kTrackIdAllTracks = 0;

enum class IrsfError {
  OK = 0,
  InvalidPointer = 1,
  GeneralError = 2,
  TelemetryFileBadFormat = 3,
  TelemetryWriterFileNotOpen = 4,
  TelemetryRecorderNoLapVariable =
      5,  // message: Error: Mandatory variable "Lap" not added to telemetry
          // recording list.
  InvalidVariableId = 6,
  IrsdkVariableNameNotFound = 7,
  IrsdkUnknownVariableType = 8,
  TelemetryDoesNotContainRequiredVariableId = 9,
  MissingInputVariable = 10,
  NoLapsSelectedForTelemetry = 11,
  NoVariablesSelectedForTelemetry = 12,
  InvalidDistanceValuesForTelemetry = 13,
  TelemetryDoesNotContainRequiredLapNumber = 14,
  FormulaEvaluationTooManyOperands = 15,
  FormulaEvaluationTooManyOperators = 16,
  FormulaWithSameNameAlreadyExists = 17,
  FileNotFound = 18,
  ItemNotFound = 19,
  NameAlreadyExists = 20,
  PortaudioFailedInit = 21,
  PortaudioFailedOpen = 22,
  IrsdkFailedToStart = 23,
  PortaudioFailedStop = 24,
  SignalSetEmpty = 25,
  LiveSignalPlayerEventsEmpty = 26,
  SoundChannelCreationFailed = 27,
  IrsdkVariableIsUnsupportedType = 28,
  FormulaNotFound = 29,
  LapDistanceVariableMissing = 30,
  NoSignalSelected = 31,
  SignalSetWithThisNameAlreadyExists = 32,
  WarningMissingSignalForSignalSet = 33,
  ItemAlreadyExists = 34,
  InvalidName = 35,
  IrsdkNotInitialized = 36,
  NoValuesInSelectedTelemetryRange = 37,
  FormulaIsEmpty = 38,
  CannotOpenFile = 39,
  TelemetryDiskWriterWritingFailed = 40,
  FormulaDatabaseCorrupted = 41,
  InputVariableDerivedVelocityHeadingMissingTelemetry = 42,
  InvalidInput = 43,
  CorruptedData = 44,
  NoSignalSetSelected = 45,
  NoTrackAndTrackConfigSelected = 46,
  InvalidInputRange1 = 47,
  InvalidInputRange2 = 48,
  SignalRangesOverlap = 49,
  InvalidSoundFileName = 50,
  SoundFileNotFound = 51,
  NoSymbolWasInput = 52,
  SymbolAlreadyExists = 53,
  NoVariableSelected = 54,
  InvalidInputForAveragePeriod = 55,
  CannotStartTelemetryCannotDeleteFile = 56,
  CannotAddAnyMoreVariableToTelemetryChartView = 57,
  FormulaDbMemoryCorrupted = 58,
  InvalidRange1Relation = 59,
  InvalidRange2Relation = 60,
  InvalidRangeOverlap = 61

  // NOTE: if you add enums here, add them to IrsfException::what() as well
};

static std::string exceptionTxt;

class IrsfException : public std::exception {
 public:
  explicit IrsfException(IrsfError& err) : irsfError(err) {}

  explicit IrsfException(IrsfError&& err) : irsfError(err) {}

  IrsfException(IrsfError& err, std::string& additionalMessage)
      : irsfError(err), AdditionalMessage(additionalMessage) {}

  IrsfException(IrsfError err, const char* msg)
      : irsfError(err), AdditionalMessage(msg) {}

  char const* what() const override {
    std::string msg1;

    std::cout << "exception __ what = " << static_cast<int>(irsfError)
              << std::endl;

    msg1 = "Unknown error";

    switch (irsfError) {
      case IrsfError::OK:
        msg1 = "No error";
        break;
      case IrsfError::InvalidPointer:
        msg1 = "Invalid pointer";
        break;
      case IrsfError::GeneralError:
        msg1 = "General error";
        break;
      case IrsfError::TelemetryFileBadFormat:
        msg1 =
            "Telemetry file is badly formatted. Possibly due to error in "
            "recording, or it was recorded with a different version.";
        break;
      case IrsfError::TelemetryWriterFileNotOpen:
        msg1 = "Telemetry writing could not open file.";
        break;
      case IrsfError::TelemetryRecorderNoLapVariable:
        msg1 =
            "Mandatory variable 'Lap' not added to telemetry recording list.";
        break;
      case IrsfError::InvalidVariableId:
        msg1 = "Invalid VariableId.";
        break;
      case IrsfError::IrsdkVariableNameNotFound:
        msg1 = "iRacing SDK could not find variable with given name.";
        break;
      case IrsfError::IrsdkUnknownVariableType:
        msg1 = "iRacing SDK: unknown variable type.";
        break;
      case IrsfError::TelemetryDoesNotContainRequiredVariableId:
        msg1 = "Telemetry does not contain the required VariableId.";
        break;
      case IrsfError::MissingInputVariable:
        msg1 = "Missing input variable.";
        break;
      case IrsfError::NoLapsSelectedForTelemetry:
        msg1 = "No laps were selected for telemetry.";
        break;
      case IrsfError::NoVariablesSelectedForTelemetry:
        msg1 = "No variables were selected for telemetry.";
        break;
      case IrsfError::InvalidDistanceValuesForTelemetry:
        msg1 = "The given distance values for telemetry are invalid.";
        break;
      case IrsfError::TelemetryDoesNotContainRequiredLapNumber:
        msg1 = "Telemetry does not contain the required lap number.";
        break;
      case IrsfError::FormulaEvaluationTooManyOperands:
        msg1 = "Formula evaluation: formula has too many operands.";
        break;
      case IrsfError::FormulaEvaluationTooManyOperators:
        msg1 = "Formula evaluation: formula has too many operators.";
        break;
      case IrsfError::FormulaWithSameNameAlreadyExists:
        msg1 = "Formula with same name already exists.";
        break;
      case IrsfError::FileNotFound:
        msg1 = "File not found.";
        break;
      case IrsfError::ItemNotFound:
        msg1 = "Item not found.";
        break;
      case IrsfError::NameAlreadyExists:
        msg1 = "Name already exists.";
        break;
      case IrsfError::PortaudioFailedInit:
        msg1 = "Portaudio: failed to initialize.";
        break;
      case IrsfError::PortaudioFailedOpen:
        msg1 = "Portaudio: failed to open.";
        break;
      case IrsfError::IrsdkFailedToStart:
        msg1 = "iRacing SDK failed to start.";
        break;
      case IrsfError::PortaudioFailedStop:
        msg1 = "Portaudio: failed to stop.";
        break;
      case IrsfError::SignalSetEmpty:
        msg1 = "Signal Set is empty.";
        break;
      case IrsfError::LiveSignalPlayerEventsEmpty:
        msg1 = "No events added for the live signal player.";
        break;
      case IrsfError::SoundChannelCreationFailed:
        msg1 = "Sound channel creation failed.";
        break;
      case IrsfError::IrsdkVariableIsUnsupportedType:
        msg1 = "iRacing SDK variable is unsupported type.";
        break;
      case IrsfError::FormulaNotFound:
        msg1 = "Formula not found.";
        break;
      case IrsfError::LapDistanceVariableMissing:
        msg1 = "LapDistance variable missing.";
        break;
      case IrsfError::NoSignalSelected:
        msg1 = "No signal was selected.";
        break;
      case IrsfError::SignalSetWithThisNameAlreadyExists:
        msg1 = "Signal Set with this name already exists.";
        break;
      case IrsfError::WarningMissingSignalForSignalSet:
        msg1 = "Warning: this signal set is missing a signal.";
        break;
      case IrsfError::ItemAlreadyExists:
        msg1 = "Item already exists.";
        break;
      case IrsfError::InvalidName:
        msg1 = "Invalid name.";
        break;
      case IrsfError::IrsdkNotInitialized:
        msg1 = "iRacing SDK not initialized.";
        break;
      case IrsfError::NoValuesInSelectedTelemetryRange:
        msg1 = "No values have been selected in the given telemetry range.";
        break;
      case IrsfError::FormulaIsEmpty:
        msg1 = "Formula is empty.";
        break;
      case IrsfError::CannotOpenFile:
        msg1 = "Cannot open file.";
        break;
      case IrsfError::TelemetryDiskWriterWritingFailed:
        msg1 = "Failed to write telemetry to disk.";
        break;
      case IrsfError::FormulaDatabaseCorrupted:
        msg1 =
            "Formula database is corrupted. Try to use the backup (_bak) "
            "version, or create a new one.";
        break;
      case IrsfError::InputVariableDerivedVelocityHeadingMissingTelemetry:
        msg1 =
            "The telemetry is missing a variable for derived variable "
            "VelocityHeading.";
        break;
      case IrsfError::InvalidInput:
        msg1 = "Invalid input.";
        break;
      case IrsfError::CorruptedData:
        msg1 = "Corrupted data.";
        break;
      case IrsfError::NoSignalSetSelected:
        msg1 = "No signal set selected.";
        break;
      case IrsfError::NoTrackAndTrackConfigSelected:
        msg1 = "No track and/or track configuration were selected.";
        break;
      case IrsfError::InvalidInputRange1:
        msg1 = "Invalid input for range 1.";
        break;
      case IrsfError::InvalidInputRange2:
        msg1 = "Invalid input for range 2.";
        break;
      case IrsfError::SignalRangesOverlap:
        msg1 = "Signal ranges are overlapping.";
        break;
      case IrsfError::InvalidSoundFileName:
        msg1 = "The selected file name for the sound file is invalid.";
        break;
      case IrsfError::SoundFileNotFound:
        msg1 = "Sound file not found.";
        break;
      case IrsfError::NoSymbolWasInput:
        msg1 = "You did not enter a symbol.";
        break;
      case IrsfError::SymbolAlreadyExists:
        msg1 = "Symbol already exists.";
        break;
      case IrsfError::NoVariableSelected:
        msg1 = "No variables were selected.";
        break;
      case IrsfError::InvalidInputForAveragePeriod:
        msg1 = "The inputs for the Average Period are invalid or missing.";
        break;
      case IrsfError::CannotStartTelemetryCannotDeleteFile:
        msg1 =
            "Telemetry recording cannot be started because a file with "
            "selected name already exists and cannot be deleted.";
        break;
      case IrsfError::CannotAddAnyMoreVariableToTelemetryChartView:
        msg1 = "Cannot add any more variables to telemetry chart view.";
        break;
      case IrsfError::FormulaDbMemoryCorrupted:
        msg1 = "Formula database memory corrupted.";
        break;
      case IrsfError::InvalidRange1Relation:
        msg1 = "Range 1 minimum must be smaller than range 1 maximum.";
        break;
      case IrsfError::InvalidRange2Relation:
        msg1 = "Range 2 minimum must be smaller than range 2 maximum.";
        break;
      case IrsfError::InvalidRangeOverlap:
        msg1 =
            "Range overlap is invalid. Maximum of Range 2 must be equal or "
            "smaller than minimum of range 1";
        break;
    }

    exceptionTxt = msg1 + "\n";
    exceptionTxt = exceptionTxt + AdditionalMessage;

    return exceptionTxt.c_str();
  }

  IrsfError GetError() { return irsfError; }

 private:
  IrsfError irsfError;
  std::string AdditionalMessage;
};

enum class VariableId {
  VariableUnknown = 0,
  SessionTime = 1,
  SessionTick = 2,
  SessionNum = 3,
  SessionState = 4,
  SessionUniqueID = 5,
  SessionFlags = 6,
  SessionTimeRemain = 7,
  SessionLapsRemain = 8,
  SessionLapsRemainEx = 9,
  SessionTimeOfDay = 10,
  RadioTransmitCarIdx = 11,
  RadioTransmitRadioIdx = 12,
  RadioTransmitFrequencyIdx = 13,
  DisplayUnits = 14,
  DriverMarker = 15,
  PushToPass = 16,
  ManualBoost = 17,
  ManualNoBoost = 18,
  IsOnTrack = 19,
  IsReplayPlaying = 20,
  ReplayFrameNum = 21,
  ReplayFrameNumEnd = 22,
  IsDiskLoggingEnabled = 23,
  IsDiskLoggingActive = 24,
  FrameRate = 25,
  CpuUsageBG = 26,
  PlayerCarPosition = 27,
  PlayerCarClassPosition = 28,
  PlayerTrackSurface = 29,
  PlayerTrackSurfaceMaterial = 30,
  PlayerCarIdx = 31,
  PlayerCarTeamIncidentCount = 32,
  PlayerCarMyIncidentCount = 33,
  PlayerCarDriverIncidentCount = 34,
  PlayerCarWeightPenalty = 35,
  PlayerCarPowerAdjust = 36,
  PlayerCarTowTime = 37,
  PlayerCarInPitStall = 38,
  PlayerCarPitSvStatus = 39,
  CarIdxLap = 40,
  CarIdxLapCompleted = 41,
  CarIdxLapDistPct = 42,
  CarIdxTrackSurface = 43,
  CarIdxTrackSurfaceMaterial = 44,
  CarIdxOnPitRoad = 45,
  CarIdxPosition = 46,
  CarIdxClassPosition = 47,
  CarIdxF2Time = 48,
  CarIdxEstTime = 49,
  CarIdxLastLapTime = 50,
  CarIdxBestLapTime = 51,
  CarIdxBestLapNum = 52,
  OnPitRoad = 53,
  CarIdxSteer = 54,
  CarIdxRPM = 55,
  CarIdxGear = 56,
  SteeringWheelAngle = 57,
  Throttle = 58,
  Brake = 59,
  Clutch = 60,
  Gear = 61,
  RPM = 62,
  Lap = 63,
  LapCompleted = 64,
  LapDist = 65,
  LapDistPct = 66,
  RaceLaps = 67,
  LapBestLap = 68,
  LapBestLapTime = 69,
  LapLastLapTime = 70,
  LapCurrentLapTime = 71,
  LapLasNLapSeq = 72,
  LapLastNLapTime = 73,
  LapBestNLapLap = 74,
  LapBestNLapTime = 75,
  LapDeltaToBestLap = 76,
  LapDeltaToBestLap_DD = 77,
  LapDeltaToBestLap_OK = 78,
  LapDeltaToOptimalLap = 79,
  LapDeltaToOptimalLap_DD = 80,
  LapDeltaToOptimalLap_OK = 81,
  LapDeltaToSessionBestLap = 82,
  LapDeltaToSessionBestLap_DD = 83,
  LapDeltaToSessionBestLap_OK = 84,
  LapDeltaToSessionOptimalLap = 85,
  LapDeltaToSessionOptimalLap_DD = 86,
  LapDeltaToSessionOptimalLap_OK = 87,
  LapDeltaToSessionLastlLap = 88,
  LapDeltaToSessionLastlLap_DD = 89,
  LapDeltaToSessionLastlLap_OK = 90,
  Speed = 91,
  Yaw = 92,
  YawNorth = 93,
  Pitch = 94,
  Roll = 95,
  EnterExitReset = 96,
  TrackTemp = 97,
  TrackTempCrew = 98,
  AirTemp = 99,
  WeatherType = 100,
  Skies = 101,
  AirDensity = 102,
  AirPressure = 103,
  WindVel = 104,
  WindDir = 105,
  RelativeHumidity = 106,
  FogLevel = 107,
  DCLapStatus = 108,
  DCDriversSoFar = 109,
  OkToReloadTextures = 110,
  LoadNumTextures = 111,
  CarLeftRight = 112,
  PitsOpen = 113,
  PitRepairLeft = 114,
  PitOptRepairLeft = 115,
  PitstopActive = 116,
  FastRepairUsed = 117,
  FastRepairAvailable = 118,
  CamCarIdx = 119,
  CamCameraNumber = 120,
  CamGroupNumber = 121,
  CamCameraState = 122,
  IsOnTrackCar = 123,
  IsInGarage = 124,
  SteeringWheelPctTorque = 125,
  SteeringWheelPctTorqueSign = 126,
  SteeringWheelPctTorqueSignStops = 127,
  SteeringWheelPctDamper = 128,
  SteeringWheelAngleMax = 129,
  ShiftIndicatorPct = 130,
  ShiftPowerPct = 131,
  ShiftGrindRPM = 132,
  ThrottleRaw = 133,
  BrakeRaw = 134,
  HandbrakeRaw = 135,
  SteeringWheelPeakForceNm = 136,
  EngineWarnings = 137,
  FuelLevel = 138,
  FuelLevelPct = 139,
  PitSvFlags = 140,
  PitSvLFP = 141,
  PitSvRFP = 142,
  PitSvLRP = 143,
  PitSvRRP = 144,
  PitSvFuel = 145,
  CarIdxP2P_Status = 146,
  CarIdxP2P_Count = 147,
  ReplayPlaySpeed = 148,
  ReplayPlaySlowMotion = 149,
  ReplaySessionTime = 150,
  ReplaySessionNum = 151,
  TireLF_RumblePitch = 152,
  TireRF_RumblePitch = 153,
  TireLR_RumblePitch = 154,
  TireRR_RumblePitch = 155,
  SteeringWheelTorque_ST = 156,
  SteeringWheelTorque = 157,
  VelocityZ_ST = 158,
  VelocityY_ST = 159,
  VelocityX_ST = 160,
  VelocityZ = 161,
  VelocityY = 162,
  VelocityX = 163,
  YawRate_ST = 164,
  PitchRate_ST = 165,
  RollRate_ST = 166,
  YawRate = 167,
  PitchRate = 168,
  RollRate = 169,
  VertAccel_ST = 170,
  LatAccel_ST = 171,
  LongAccel_ST = 172,
  VertAccel = 173,
  LatAccel = 174,
  LongAccel = 175,
  dcStarter = 176,
  dcPitSpeedLimiterToggle = 177,
  dcDRSToggle = 178,
  dcTearOffVisor = 179,
  dpTireChange = 180,
  dpFuelFill = 181,
  dpFuelAddKg = 182,
  dpFastRepair = 183,
  dcDashPage = 184,
  dcBrakeBias = 185,
  dpLFTireColdPress = 186,
  dpRFTireColdPress = 187,
  dpLRTireColdPress = 188,
  dpRRTireColdPress = 189,
  dcThrottleShape = 190,
  dcTractionControl = 191,
  RFbrakeLinePress = 192,
  RFcoldPressure = 193,
  RFtempCL = 194,
  RFtempCM = 195,
  RFtempCR = 196,
  RFwearL = 197,
  RFwearM = 198,
  RFwearR = 199,
  LFbrakeLinePress = 200,
  LFcoldPressure = 201,
  LFtempCL = 202,
  LFtempCM = 203,
  LFtempCR = 204,
  LFwearL = 205,
  LFwearM = 206,
  LFwearR = 207,
  CFshockDefl = 208,
  CFshockDefl_ST = 209,
  CFshockVel = 210,
  CFshockVel_ST = 211,
  WaterTemp = 212,
  WaterLevel = 213,
  FuelPress = 214,
  FuelUsePerHour = 215,
  OilTemp = 216,
  OilPress = 217,
  OilLevel = 218,
  Voltage = 219,
  ManifoldPress = 220,
  RRbrakeLinePress = 221,
  RRcoldPressure = 222,
  RRtempCL = 223,
  RRtempCM = 224,
  RRtempCR = 225,
  RRwearL = 226,
  RRwearM = 227,
  RRwearR = 228,
  LRbrakeLinePress = 229,
  LRcoldPressure = 230,
  LRtempCL = 231,
  LRtempCM = 232,
  LRtempCR = 233,
  LRwearL = 234,
  LRwearM = 235,
  LRwearR = 236,
  RRshockDefl = 237,
  RRshockDefl_ST = 238,
  RRshockVel = 239,
  RRshockVel_ST = 240,
  LRshockDefl = 241,
  LRshockDefl_ST = 242,
  LRshockVel = 243,
  LRshockVel_ST = 244,
  DRS_Status = 245,
  DRS_Count = 246,

  DerivedVelocityHeading = 1000,

  // values below this must be >= kVariableProcessedIdStart
  ProcessedAverage = 2000,
  ProcessedDelta = 2001,
};

enum class TelemetryWriterEntryHeader {
  VersionInfo = 1,
  DataEntry = 2,
  VariableDefinitions = 3,
  CurrentLap = 4,
  EndOfFile = 5
};

enum class OperatorId {
  Unknown = 0,
  Add = 1,
  Subtract = 2,
  Multiply = 3,
  Divide = 4,
  OpenBracket = 5,
  CloseBracket = 6,
  Absolute = 7
};

enum class SoundVolumeCurve {
  Unknown = 0,
  Fastest = 1,
  Fast = 2,
  Linear = 3,
  Slow = 4,
  Slowest = 5
};

enum class SignalActivationEventType { Unknown = 0, Start = 1, Stop = 2 };

struct TelemetryData {
  std::vector<VariableId> Variables;

  std::vector<std::vector<float>>
      Data;  // Telemetry Data (vector) for each of the laps (vector)

  // Key = Lap number, Value = index in Data vector
  std::map<int32_t, size_t> LapIndex;
};

struct SoundData {
  // Float* data;
  std::vector<float> data;
  size_t dataLength;  // size of data + extra length for another full buffer,
                      // looped from beginning (dataLength > sampleLength)
  size_t
      sampleLength;  // size at which data begins to loop (actual sample length)
};

struct SoundChannel {
  std::unique_ptr<SoundData> snd;
  float multiplier;  // maybe: volume multiplier - SHOULD BE POINTER (so the
                     // signals can set it without going through the struct
                     // tree) but its ok to access it with
                     // soundChannel->multiplier = value;

  size_t offset;  // offset at which the channel is playing
};

typedef struct  // Portaudio library standard
{
  SNDFILE* file;
  SF_INFO info;
} callback_data_s;

struct BrakeMarker {
  float distancePosition;
  float speedAtMarker;  // kph

  bool operator<(const BrakeMarker& other) {
    return distancePosition < other.distancePosition;
  }
};

struct BrakeMarkerSet {
  std::string name;
  int32_t TrackId;
  int32_t TrackConfigId;
  std::vector<BrakeMarker> bmList;

  bool operator==(const BrakeMarkerSet& other) {
    if (name == other.name) {
      return true;
    }
    return false;
  }

  bool operator==(const std::string& otherName) {
    if (name == otherName) {
      return true;
    }

    return false;
  }
};

struct BrakeMarkerActive {
  BrakeMarkerActive(SoundChannel* inSc, BrakeMarker inBm)
      : bm(inBm), sc(inSc), loopsRemaining(0) {}

  BrakeMarker bm;
  SoundChannel* sc;
  int32_t loopsRemaining;

  bool operator<(const BrakeMarkerActive& other) { return bm < other.bm; }
};

struct TelemetryViewerOptionsForChart {
  std::vector<VariableId> variableList;

  float DistanceStart;
  float DistanceEnd;

  std::vector<int32_t> lapList;

  bool ShowAllLaps;
};

struct TelemetryChartDataPoint {
  float Value;
  float Distance;
};

struct InputVariableDescriptor {
  VariableId variableId;
  VariableId variableIdForProcessing;
  int32_t parameterForProcessing;

  InputVariableDescriptor()
      : variableId(VariableId::VariableUnknown),
        variableIdForProcessing(VariableId::VariableUnknown),
        parameterForProcessing(-1) {}
};

class FormulaSymbolBase {
  friend class FormulaOperand;
  friend class FormulaOperator;

 public:
  virtual ~FormulaSymbolBase() = default;

  FormulaSymbolBase() = delete;

  // feature: the user must choose operand or operator on creation
  explicit FormulaSymbolBase(bool isSymbolOperand)
      : isOperand(isSymbolOperand) {}

  FormulaSymbolBase(FormulaSymbolBase& other) : isOperand(other.isOperand) {}

  FormulaSymbolBase(FormulaSymbolBase&& other) { isOperand = other.isOperand; }

  FormulaSymbolBase& operator=(const FormulaSymbolBase& other) {
    isOperand = other.isOperand;
    return *this;
  }

  FormulaSymbolBase& operator=(FormulaSymbolBase&& other) noexcept {
    isOperand = other.isOperand;
    return *this;
  }

  bool IsOperand() const noexcept { return isOperand; }

 private:
  bool isOperand;
};

struct FormulaSymbolEvaluated {
  std::variant<OperatorId, float*> val;
};

using SymbEvaluated = std::unique_ptr<FormulaSymbolEvaluated>;

struct TrackLayoutConfiguration {
  std::string name;
  int32_t id;
  float totalLengthMeters;
};

struct Track {
  std::string name;
  int32_t id;
  std::vector<TrackLayoutConfiguration> configurations;
};

struct TrackSector {
  TrackSector()
      : name(""),
        id(kIdNotSelected),
        startDistance(-1.0f),
        endDistance(-1.0f),
        trackId(kIdNotSelected),
        trackConfigurationId(kIdNotSelected) {}

  std::string name;     // descriptive name
  int32_t id;           // unique identifier
  float startDistance;  // meters
  float endDistance;    // meters

  // Which track are these track sections for
  int32_t trackId;

  // Which track configuration are these track sections for
  int32_t trackConfigurationId;
};

struct TrackDataAll {
  std::vector<Track> tracks;
  std::vector<TrackSector> trackSectors;
};

struct SignalRange {
  float min;
  float max;
};

struct SignalSound {
  std::string soundFileName;
  float soundVolume;
  SoundVolumeCurve curve;
};

struct IrsfSignal {
  std::string name;  // unique ID
  int32_t trackId = 0;
  int32_t trackConfigId = 0;
  std::string formulaName;
  bool secondRangeActive;
  SignalRange range1;  // range1 is primary range (if using two ranges, this
                       // range is should be the one for positive values)
  SignalRange range2;  // for range2 Maximum is still the higher value (ie
                       // closer to 0 if negative)
  bool useFullTrack;
  int32_t trackSectorId;
  SignalSound sound;

  IrsfSignal() {
    name = "";
    trackId = 0;
    trackConfigId = 0;
    formulaName = "None";
    range1.max = 1.0;
    range1.min = 0.0;
    secondRangeActive = false;
    range2.max = 0.0;
    range2.min = -1.0;
    useFullTrack = true;
    trackSectorId = kIdNotSelected;
    sound.soundFileName = "none";
    sound.soundVolume = 1.0;
    sound.curve = SoundVolumeCurve::Linear;
  }

  IrsfSignal(const IrsfSignal& other) = default;
  IrsfSignal(IrsfSignal&& other) = default;
  IrsfSignal& operator=(const IrsfSignal& other) = default;
  IrsfSignal& operator=(IrsfSignal&& other) = default;
  ~IrsfSignal() = default;
};

struct IrsfSignalSet {
  std::string name;
  int32_t trackId;
  int32_t trackConfigId;
  std::vector<std::string> signalNames;

  explicit IrsfSignalSet()
      : name(""), trackId(kIdNotSelected), trackConfigId(kIdNotSelected) {}
};

struct SignalActivationEvent {
  IrsfSignal* signal;
  float lapDistance;  // where the event happens
  SignalActivationEventType type;
  std::vector<FormulaSymbolBase*> formulaPostfixBase;
  std::vector<SymbEvaluated> formulaPostfixEvaluated;
  std::vector<FormulaSymbolEvaluated*> formulaPostfixEvaluated_p;
  std::shared_ptr<SoundChannel> channel;
  int32_t pairId;  // unique id shared between start and end events
};

struct SignalActivationEventComparer {
  inline bool operator()(const std::unique_ptr<SignalActivationEvent>& s1,
                         const std::unique_ptr<SignalActivationEvent>& s2) {
    return (s1->lapDistance < s2->lapDistance);
  }
};

enum class WindowTelemetryViewerOptionsMoveAction {

  // Note: maybe should be part of some other namespace

  Unknown = 0,
  ZoomIn = 1,
  ZoomOut = 2,
  MoveLeft = 3,
  MoveRight = 4
};

struct AppConfig {
  /*
   * Which variables will be recorded when recording telemetry
   */
  std::vector<VariableId> TelemetryRecordingVariables;

  /*
   * When recording telemetry, how many maximum ticks (frames) to hold in memory
   * before writing to disk. Lower number means more frequent disk writes.
   */
  size_t telemetry_MaxTicksInMemory;

  // Brake marker options ----------------

  /*
   * how many loops to have the sound active before muting it (ie 2,3, etc)
   */
  int32_t bm_LoopLength;

  /*
   *latency between actually hitting the mark and hearing the sound
   *(milliseconds)
   */
  int32_t bm_ExpectedLatencyMs;

  /*
   *milliseconds delay between the two warning and final beep
   */
  int32_t bm_DelayBetweenBeeps;

  /*
   * if distance < this value && distance > 0, mark as start of next lap
   */
  int32_t bm_NextLapMinDistance;

  float bm_SoundVolume;

  std::string Marker_fileName;
  std::string PreMarker_fileName;

  // Sound options-------------

  /*
   * How many samples per buffer per channel to load into memory before
   * releasing it to the sound card
   */
  int32_t FrameCount;

  /*
   *  This should be 2 for stereo
   */
  int32_t ChannelCount;

  /*
   * Default is 44100 but you can use other bitrates if you want for your audio
   * files
   */
  int32_t Wav_SampleRate;
};
}  // namespace irsf
#endif  // IRSFCOMMON_H
