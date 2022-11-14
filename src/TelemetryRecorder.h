#ifndef TELEMETRYRECORDER_H
#define TELEMETRYRECORDER_H

#include <memory>
#include <vector>
#include "IrsfCommon.h"
#include "TelemetryDiskWriter.h"
#include "TelemetryDiskWriterHandler.h"
#include "irsdkmanager.h"
namespace irsf {
/*
 * Manager class that handles telemetry recording. After the parameters are set,
 * it launches threads to write the data to disk on set periods.
 */
class TelemetryRecorder {
 public:
  explicit TelemetryRecorder(TelemetryDiskWriter* telemetryDiskWriter,
                             irsf::irsdk::IrsdkManager* irsdkMngr,
                             size_t maxTicks);

  /*
   * Must be called after irsdkManager is initialized and connected to iRacing
   */
  void Init(const std::string& recordingFileName,
            const std::vector<VariableId> inputVariablesIn);

  ~TelemetryRecorder();

  TelemetryRecorder(TelemetryRecorder& other) = delete;

  TelemetryRecorder(TelemetryRecorder&& other) = delete;

  TelemetryRecorder& operator=(TelemetryRecorder& other) = delete;

  TelemetryRecorder& operator=(TelemetryRecorder&& other) = delete;

  /*
   * Write data from the sim into local memory
   */
  void Record();

  /*
   * Write the data kept in memory to disk
   */
  void SendToWriter();

 private:
  void InitMemory(size_t maxTicksInMemory);

  void InitLapVariable();

  void InitWriter(const std::string& fileName,
                  const std::vector<VariableId>& inputVars);

  std::vector<iVarInterface_sp> inputVariables;

  std::vector<iVarRawInterface_sp> inputVariablesNonFloat;

  std::vector<float*> valuePointers;

  std::vector<float> recorderValues_mem1;

  std::vector<float> recorderValues_mem2;

  float* recorderValues{nullptr};

  int32_t currentOffset{-1};

  /*
   * When recording telemetry, how many maximum ticks (frames) to hold in memory
   * before writing to disk. Lower number means more frequent disk writes.
   */
  size_t MaxTicksInMemory;

  size_t tickCount{0};

  TelemetryDiskWriter* writer;

  std::unique_ptr<TelemetryDiskWriterHandler> writerHandler{
      std::make_unique<TelemetryDiskWriterHandler>()};

  irsf::irsdk::IrsdkManager* irsdkManager;

  float* currentLapLiveData{nullptr};

  float previouslyRecordedLapNumber{-2.0f};

  void ConvertFloats() noexcept;

  // Additional number of floats to overassign memory for safety
  static constexpr int32_t kMaxTicksSafety = 10;
};
}  // namespace irsf
#endif  // TELEMETRYRECORDER_H
