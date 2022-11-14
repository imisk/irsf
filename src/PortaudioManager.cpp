
#include "PortaudioManager.h"
#include "IrsfCommon.h"

using namespace irsf;

PortaudioManager::PortaudioManager() noexcept {}

void PortaudioManager::Initialize(int32_t channelCount, int32_t sampleRate) {
  stream = nullptr;

  PaError err;

  Wav_Samplerate = sampleRate;

  std::cout << "---------------------- PortAudio -- Pa_Initialize() \n";
  err = Pa_Initialize();
  if (err != paNoError) {
    std::cout << "----------------PortAudio -- error -- Pa_Initialize() \n";
    OnError(stream, err);
    throw IrsfException(IrsfError::PortaudioFailedInit);
  }

  outputParameters.hostApiSpecificStreamInfo = nullptr;
  outputParameters.channelCount = channelCount;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = 0;

  std::cout << "---------------- PortAudio -- Pa_GetDefaultOutputDevice() \n";
  outputParameters.device = Pa_GetDefaultOutputDevice();  // this also works

  //------------- wasapi

  if (wasapiInfo != nullptr)
    delete wasapiInfo;

  wasapiInfo = new PaWasapiStreamInfo();  // changed_m2

  wasapiInfo->size = sizeof(PaWasapiStreamInfo);
  wasapiInfo->hostApiType = paWASAPI;
  wasapiInfo->version = 1;
  wasapiInfo->flags = (1 << 4);  // paWinWasapiThreadPriority;
  wasapiInfo->channelMask = NULL;
  wasapiInfo->hostProcessorOutput = nullptr;
  wasapiInfo->hostProcessorInput = nullptr;
  wasapiInfo->threadPriority = eThreadPriorityProAudio;

  outputParameters.hostApiSpecificStreamInfo = wasapiInfo;
}

void PortaudioManager::BeginStream(PaStreamCallback* callback_mixer) {
  PaError err;

  std::cout << "---------------------- PortAudio -- Pa_OpenStream() \n";
  err = Pa_OpenStream(&stream, nullptr, &outputParameters, Wav_Samplerate,
                      FRAMES_PER_BUFFER, paClipOff, callback_mixer, nullptr);

  if (err != paNoError) {
    std::cout << "------------------ PortAudio -- Pa_OpenStream() --- err \n";
    OnError(stream, err);
    throw IrsfException(IrsfError::PortaudioFailedOpen);
  }

  std::cout << "---------------------- PortAudio -- Pa_StartStream() \n";
  err = Pa_StartStream(stream);

  if (err != paNoError) {
    std::cout << "------------- PortAudio -- Pa_StartStream() --- error \n";
    OnError(stream, err);
    throw IrsfException(IrsfError::PortaudioFailedOpen);
  }
}

void PortaudioManager::EndStream() {
  PaError err;

  if (!stream)
    return;

  err = Pa_StopStream(stream);
  if (err != paNoError) {
    OnError(stream, err);
    throw IrsfException(IrsfError::PortaudioFailedStop);
  }

  Pa_Terminate();
}

void PortaudioManager::OnError(PaStream* stream, PaError err) {
  if (stream) {
    Pa_AbortStream(stream);
    Pa_CloseStream(stream);
  }

  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  return;
}
