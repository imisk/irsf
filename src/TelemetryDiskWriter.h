#ifndef TELEMETRYDISKWRITER_H
#define TELEMETRYDISKWRITER_H

#include <QThread>
#include <fstream>
#include "QDebug"
#include "QMutex"
#include "QObject"
#include "QString"
#include "TelemetryDiskWriterInterface.h"
namespace irsf {
constexpr int32_t kCurrentTelemetryFileVersion = 1;

class TelemetryDiskWriter : public QObject,
                            public TelemetryDiskWriterInterface {
  Q_OBJECT

 public:
  explicit TelemetryDiskWriter() noexcept;

  ~TelemetryDiskWriter() override;

  TelemetryDiskWriter(TelemetryDiskWriter& other) = delete;

  TelemetryDiskWriter& operator=(TelemetryDiskWriter& other) = delete;

  TelemetryDiskWriter(TelemetryDiskWriter&& other) = delete;

  TelemetryDiskWriter& operator=(TelemetryDiskWriter&& other) = delete;

  void OpenFile(const std::string& fileName) override;

  void WriteData_Prepare(float* valuesToWrite,
                         const size_t& valuesPerTick,
                         const size_t& totalTicks) override;

  void WriteData() override;

  void WriteFileVersion() override;

  void WriteCurrentLap_Prepare(int32_t currentLap) override;

  void WriteCurrentLap() override;

  void WriteVariableList(const std::vector<VariableId>& varList) override;

  void WriteEndOfFile() override;

  void CloseFile() override;

 public slots:

  void processWriteCurrentLap();

  void handleResultsWriteCurrentLap(int32_t retError);

 signals:

  void finishedWriteData();

  void finishedWriteCurrentLap();

  void sendResultWriteData(IrsfError retError);

 private:
  std::fstream myfile;
  std::mutex wMutex;
  float* valuesToWriteThread;
  size_t valuesPerTickThread;
  size_t totalTicksThread;
  int32_t currentLapThread;
  QThread* parentThreadLast;
  bool fileIsOpen;
};
}  // namespace irsf
#endif  // TELEMETRYDISKWRITER_H
