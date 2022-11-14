
#include "TelemetryDiskWriter.h"
#include <fstream>
#include "BinaryReadWriteUtils.h"
#include "ErrorMessageBoxUtility.h"

using namespace irsf;

TelemetryDiskWriter::TelemetryDiskWriter() noexcept
    : valuesToWriteThread(nullptr),
      valuesPerTickThread(0),
      totalTicksThread(0),
      currentLapThread(-1),
      parentThreadLast(nullptr),
      fileIsOpen(false) {}

TelemetryDiskWriter::~TelemetryDiskWriter() {
  if (fileIsOpen) {
    this->WriteEndOfFile();
    this->CloseFile();
  }

  qDebug() << "TelemetryDiskWriter ---- DESTRUCTOR called.";
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void TelemetryDiskWriter::OpenFile(const std::string& fileName) {
  try {
    myfile = std::fstream(fileName,
                          std::ios::out | std::ios::binary | std::ios::ate);

    fileIsOpen = true;
  } catch (...) {
    throw IrsfException(IrsfError::CannotOpenFile);
  }
}

void TelemetryDiskWriter::WriteData_Prepare(float* valuesToWrite,
                                            const size_t& valuesPerTick,
                                            const size_t& totalTicks) {
  /*
   * It's ok to use this pointer in another thread because the slower (parent)
   *  thread has switched to using secondary,
   * and the new thread will finish before the switch is done again.
   * The mutex lock will also prevent overwriting active pointer, or
   * causing conflict.
   */

  std::scoped_lock<std::mutex> lock(wMutex);

  valuesToWriteThread = valuesToWrite;
  valuesPerTickThread = valuesPerTick;
  totalTicksThread = totalTicks;
}

void TelemetryDiskWriter::WriteData() {
  qDebug() << "writer: write data";

  if (!fileIsOpen)
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);

  {
    std::scoped_lock<std::mutex> lock(wMutex);

    size_t valueCount = valuesPerTickThread * totalTicksThread;

    if (valueCount > 0) {
      //--- Header
      TelemetryWriterEntryHeader header = TelemetryWriterEntryHeader::DataEntry;
      WriteBinary(myfile, &header);

      //--- Value count
      WriteBinary(myfile, &valueCount);

      std::cout << "writeData _ val0 = " << valuesToWriteThread[0] << '\n';

      //--- Values
      myfile.write(reinterpret_cast<char*>(valuesToWriteThread),
                   static_cast<std::streamsize>(valueCount * sizeof(float)));
    }
  }
}

void TelemetryDiskWriter::WriteFileVersion() {
  std::scoped_lock<std::mutex> lock(wMutex);

  if (!fileIsOpen) {
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);
  }

  //--- Header
  TelemetryWriterEntryHeader header = TelemetryWriterEntryHeader::VersionInfo;
  WriteBinary(myfile, &header);

  //--- Version
  auto ver = kCurrentTelemetryFileVersion;
  WriteBinary(myfile, &ver);
}

void TelemetryDiskWriter::WriteCurrentLap_Prepare(int32_t currentLap) {
  std::scoped_lock<std::mutex> lock(wMutex);

  currentLapThread = currentLap;
}

void TelemetryDiskWriter::WriteCurrentLap() {
  qDebug() << "WriteCurrentLap...------------------------------------------"
              "-------------########################## "
           << currentLapThread;

  if (!fileIsOpen)
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);

  std::scoped_lock<std::mutex> lock(wMutex);

  //--- Header
  TelemetryWriterEntryHeader header = TelemetryWriterEntryHeader::CurrentLap;
  WriteBinary(myfile, &header);

  //--- Current lap
  WriteBinary(myfile, &currentLapThread);
}

void TelemetryDiskWriter::WriteVariableList(
    const std::vector<VariableId>& varList) {
  if (!fileIsOpen) {
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);
  }

  std::scoped_lock<std::mutex> lock(wMutex);

  //--- Header
  TelemetryWriterEntryHeader header =
      TelemetryWriterEntryHeader::VariableDefinitions;
  WriteBinary(myfile, &header);

  //--- Variable count
  size_t varCount = varList.size();
  WriteBinary(myfile, &varCount);

  //--- Variables
  for (size_t i = 0; i < varList.size(); i++) {
    VariableId id = varList[i];
    WriteBinary(myfile, &id);
  }
}

void TelemetryDiskWriter::WriteEndOfFile() {
  if (!fileIsOpen) {
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);
  }

  std::scoped_lock<std::mutex> lock(wMutex);

  qDebug() << "WriteEndOfFile...";
  //--- Header
  TelemetryWriterEntryHeader header = TelemetryWriterEntryHeader::EndOfFile;
  WriteBinary(myfile, &header);
}

void TelemetryDiskWriter::CloseFile() {
  if (!fileIsOpen) {
    throw IrsfException(IrsfError::TelemetryWriterFileNotOpen);
  }
  std::scoped_lock<std::mutex> lock(wMutex);

  qDebug() << "CloseFile...";
  myfile.close();

  fileIsOpen = false;
}

void TelemetryDiskWriter::processWriteCurrentLap() {
  if (!fileIsOpen)
    return;

  qDebug() << "processWriteData......";

  try {
    //--- Header
    TelemetryWriterEntryHeader header = TelemetryWriterEntryHeader::CurrentLap;
    WriteBinary(myfile, &header);

    //--- Current lap
    WriteBinary(myfile, &currentLapThread);

    finishedWriteCurrentLap();
  } catch (IrsfException& e) {
    HandleErrorMessage(e);
  } catch (std::exception& e) {
    std::cout << "Error: Exception during telemetry write: " << e.what()
              << '\n';
  } catch (...) {
    HandleGeneralError();
  }
}

void TelemetryDiskWriter::handleResultsWriteCurrentLap(int32_t retError) {
  if (!fileIsOpen)
    return;

  Q_UNUSED(retError)

  this->moveToThread(parentThreadLast);

  qDebug() << "handleResultsCurrentLap.................................";
}
