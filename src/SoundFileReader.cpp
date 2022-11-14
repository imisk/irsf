
#include "SoundFileReader.h"

using namespace irsf;

SoundFileReader::SoundFileReader() noexcept {}

void SoundFileReader::LoadSoundChannelFromFile(const std::string& fileName,
                                               SoundData* retData,
                                               size_t bufferOverrun,
                                               float multiplier) const {
  qDebug() << "------------- LoadSoundChannelFromFile() ";
  const char* cmyPath = fileName.c_str();

  callback_data_s data;

  /* Open the soundfile */
  data.file = sf_open(cmyPath, SFM_READ, &data.info);
  if (sf_error(data.file) != SF_ERR_NO_ERROR) {
    fprintf(stderr, "%s\n", sf_strerror(data.file));
    fprintf(stderr, "File: %s\n", cmyPath);
    throw IrsfException(IrsfError::SoundFileNotFound);
  }

  float* outBuffer = nullptr;

  try {
    sf_count_t samplesPerRead = 1000;
    sf_count_t bytesPerRead = samplesPerRead * data.info.channels;

    outBuffer = new float[static_cast<size_t>(bytesPerRead)];

    sf_count_t num_read;

    bool finishedReading = false;

    std::vector<float> audioData;

    while (!finishedReading) {
      num_read = sf_read_float(data.file, outBuffer, bytesPerRead);

      for (sf_count_t i = 0; i < num_read; i++) {
        audioData.push_back(outBuffer[i] * multiplier);
      }

      if (num_read < bytesPerRead) {
        finishedReading = true;
      }
    }

    qDebug() << "^^^^^^^^^^^^^^^ Finished reading audio file. Size = "
             << audioData.size();

    if (!retData) {
      std::cout << "oops";
    }

    CreateSoundData(audioData, retData, bufferOverrun);

    delete[] outBuffer;

  } catch (...) {
    sf_close(data.file);

    delete[] outBuffer;

    throw;
  }

  sf_close(data.file);
}

void SoundFileReader::CreateSoundData(std::vector<float>& inData,
                                      SoundData* retData,
                                      size_t bufferOverrun) const {
  if (!retData) {
    std::cout << "CreateSoundData - retData nullptr";
    throw IrsfException(IrsfError::SoundFileNotFound);
  } else {
    retData->sampleLength = inData.size();

    retData->dataLength = retData->sampleLength + bufferOverrun;

    retData->data.clear();

    // copy the sample
    for (size_t i = 0; i < inData.size(); i++) {
      retData->data.push_back(inData[i]);
    }

    // add the overrun
    for (size_t i = 0; i < bufferOverrun; i++) {
      retData->data.push_back(inData[i]);
    }
  }
}
