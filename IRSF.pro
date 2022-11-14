QT       += core gui charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += QT_DEPRECATED_WARNINGS \
_WIN64 \ _USRDLL \ PA_ENABLE_DEBUG_OUTPUT \ _CRT_SECURE_NO_DEPRECATE \
PAWIN_USE_WDMKS_DEVICE_INFO \ PA_USE_ASIO=0 \ PA_USE_DS=0 \ PA_USE_WMME=0 \ PA_USE_WASAPI=1 \ PA_USE_WDMKS=0 \ _UNICODE=0 \ UNICODE=0 \ PA_LOG_API_CALLS=1 \
#_DEBUG

#DEFINES += QT_DEPRECATED_WARNINGS \
#WIN64 \ DEBUG \ USRDLL \ PA_ENABLE_DEBUG_OUTPUT \ CRT_SECURE_NO_DEPRECATE \ PAWIN_USE_WDMKS_DEVICE_INFO \ PA_USE_ASIO=0 \ PA_USE_DS=0 \ PA_USE_WMME=1 \ PA_USE_WASAPI=1 \ PA_USE_WDMKS=1 \

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
  src/AppDbManager.cpp \
    src/BinaryReadWriteUtils.cpp \
    src/BreakMarkerManager.cpp \
    src/CoreContext.cpp \
    src/DerivedTelemetryDataOfflineCalculator.cpp \
    src/ErrorMessageBoxUtility.cpp \
    src/FormulaDbManager.cpp \
    src/FormulaEditorManager.cpp \
    src/FormulaEvaluator.cpp \
    src/FormulaInputVariableFactory.cpp \
    src/FormulaOfflineCalculator.cpp \
    src/FormulaOperand.cpp \
    src/FormulaOperator.cpp \
    src/InputVariableDerivedVelocityHeading.cpp \
    src/InputVariableProcessedAverage.cpp \
    src/LiveManager.cpp \
    src/PortaudioManager.cpp \
    src/SignalDbManager.cpp \
    src/SignalEditorManager.cpp \
    src/SignalLivePlayer.cpp \
    src/SoundFileReader.cpp \
    src/SoundMixer.cpp \
    src/TelemetryDiskReader.cpp \
    src/TelemetryDiskWriter.cpp \
    src/TelemetryDiskWriterHandler.cpp \
    src/TelemetryDiskWriterWorker.cpp \
    src/TelemetryRecorder.cpp \
    src/TelemetryViewerManager.cpp \
    src/TrackDataIO.cpp \
    src/TrackDataManager.cpp \
    src/TrackSectorManager.cpp \
    src/WindowAddOperand.cpp \
  src/WindowBrakeMarkerEditor.cpp \
  src/WindowConfig.cpp \
    src/WindowFormulaEditor.cpp \
    src/WindowLive.cpp \
    src/WindowLiveHandler.cpp \
    src/WindowLoadFormula.cpp \
    src/WindowLoadSignal.cpp \
    src/WindowSignalEditor.cpp \
    src/WindowSignalSetEditor.cpp \
    src/WindowTelemetryViewerOptions.cpp \
    src/Utilities.cpp \
    src/InputVariableRaw.cpp \
    src/IrsdkManager.cpp \
    src/IrsdkManagerDefines.cpp \
    src/IrsdkUtility.cpp \
    src/WindowTelemetryView.cpp \
    src/WindowTrackListEditor.cpp \
    src/WindowTrackSectorEditor.cpp \
    src/Worker.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    portaudio/src/common/pa_allocation.c \
    portaudio/src/common/pa_converters.c \
    portaudio/src/common/pa_cpuload.c \
    portaudio/src/common/pa_debugprint.c \
    portaudio/src/common/pa_dither.c \
    portaudio/src/common/pa_front.c \
    portaudio/src/common/pa_process.c \
    portaudio/src/common/pa_ringbuffer.c \
    portaudio/src/common/pa_stream.c \
    portaudio/src/common/pa_trace.c \
    portaudio/src/hostapi/asio/ASIOSDK/common/asio.cpp \
    portaudio/src/hostapi/asio/ASIOSDK/host/asiodrivers.cpp \
    portaudio/src/hostapi/asio/ASIOSDK/host/pc/asiolist.cpp \
    portaudio/src/hostapi/asio/pa_asio.cpp \
    portaudio/src/hostapi/dsound/pa_win_ds.c \
    portaudio/src/hostapi/dsound/pa_win_ds_dynlink.c \
    portaudio/src/hostapi/wasapi/pa_win_wasapi.c \
    portaudio/src/hostapi/wdmks/pa_win_wdmks.c \
    portaudio/src/hostapi/wmme/pa_win_wmme.c \
    portaudio/src/os/win/pa_win_coinitialize.c \
    portaudio/src/os/win/pa_win_hostapis.c \
    portaudio/src/os/win/pa_win_util.c \
    portaudio/src/os/win/pa_win_waveformat.c \
    portaudio/src/os/win/pa_win_wdmks_utils.c \
    portaudio/src/os/win/pa_x86_plain_converters.c \

HEADERS += \
  src/AppDbManager.h \
    src/BinaryReadWriteUtils.h \
    src/BinaryReadWriteUtils.tpp \
    src/BreakMarkerManager.h \
    src/CoreContext.h \
    src/DerivedTelemetryDataOfflineCalculator.h \
    src/ErrorMessageBoxUtility.h \
    src/Formula.h \
    src/FormulaDbManager.h \
    src/FormulaEditorManager.h \
    src/FormulaEvaluator.h \
    src/FormulaInputVariableFactory.h \
    src/FormulaOfflineCalculator.h \
    src/FormulaOperand.h \
    src/FormulaOperator.h \
    src/InputVariableCalculableInterface.h \
  src/InputVariableDerivedBase.h \
    src/InputVariableDerivedVelocityHeading.h \
    src/InputVariableInterface.h \
    src/InputVariableProcessedBase.h \
    src/InputVariableProcessedAverage.h \
    src/InputVariableRawInterface.h \
    src/IrsfCommon.h \
    src/LiveManager.h \
    src/OUContainer.h \
    src/PortaudioManager.h \
    src/SignalDbManager.h \
    src/SignalEditorManager.h \
    src/SignalLivePlayer.h \
    src/SoundFileReader.h \
    src/SoundMixer.h \
    src/TelemetryDiskReader.h \
    src/TelemetryDiskReaderInterface.h \
    src/TelemetryDiskWriter.h \
    src/TelemetryDiskWriterHandler.h \
    src/TelemetryDiskWriterInterface.h \
    src/TelemetryDiskWriterWorker.h \
    src/TelemetryRecorder.h \
    src/TelemetryViewerManager.h \
    src/TrackDataIO.h \
    src/TrackDataManager.h \
    src/TrackSectorManager.h \
    src/WindowAddOperand.h \
  src/WindowBrakeMarkerEditor.h \
  src/WindowConfig.h \
    src/WindowFormulaEditor.h \
    src/WindowLive.h \
    src/WindowLiveHandler.h \
    src/WindowLoadFormula.h \
    src/WindowLoadSignal.h \
    src/WindowSignalEditor.h \
    src/WindowSignalSetEditor.h \
    src/WindowTelemetryViewerOptions.h \
    src/Utilities.h \
    src/InputVariableRaw.h \
    src/IrsdkManager.h \
    src/IrsdkManagerDefines.h \
    src/IrsdkUtility.h \
    src/WindowTelemetryView.h \
    src/WindowTrackListEditor.h \
    src/WindowTrackSectorEditor.h \
    src/Worker.h \
    irsdk/irsdk_defines.h \
    src/mainwindow.h \
    portaudio/include/pa_asio.h \
    portaudio/include/pa_jack.h \
    portaudio/include/pa_linux_alsa.h \
    portaudio/include/pa_mac_core.h \
    portaudio/include/pa_win_ds.h \
    portaudio/include/pa_win_wasapi.h \
    portaudio/include/pa_win_waveformat.h \
    portaudio/include/pa_win_wdmks.h \
    portaudio/include/pa_win_wmme.h \
    portaudio/include/portaudio.h \
    portaudio/src/common/pa_allocation.h \
    portaudio/src/common/pa_converters.h \
    portaudio/src/common/pa_cpuload.h \
    portaudio/src/common/pa_debugprint.h \
    portaudio/src/common/pa_dither.h \
    portaudio/src/common/pa_endianness.h \
    portaudio/src/common/pa_gitrevision.h \
    portaudio/src/common/pa_hostapi.h \
    portaudio/src/common/pa_memorybarrier.h \
    portaudio/src/common/pa_process.h \
    portaudio/src/common/pa_ringbuffer.h \
    portaudio/src/common/pa_stream.h \
    portaudio/src/common/pa_trace.h \
    portaudio/src/common/pa_types.h \
    portaudio/src/common/pa_util.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/asio.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/asiodrvr.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/asiosys.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/combase.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/iasiodrv.h \
    portaudio/src/hostapi/asio/ASIOSDK/common/wxdebug.h \
    portaudio/src/hostapi/asio/ASIOSDK/driver/asiosample/asiosmpl.h \
    portaudio/src/hostapi/asio/ASIOSDK/host/ASIOConvertSamples.h \
    portaudio/src/hostapi/asio/ASIOSDK/host/asiodrivers.h \
    portaudio/src/hostapi/asio/ASIOSDK/host/ginclude.h \
    portaudio/src/hostapi/asio/ASIOSDK/host/pc/asiolist.h \
    portaudio/src/hostapi/asio/iasiothiscallresolver.h \
    portaudio/src/hostapi/coreaudio/pa_mac_core_blocking.h \
    portaudio/src/hostapi/coreaudio/pa_mac_core_internal.h \
    portaudio/src/hostapi/coreaudio/pa_mac_core_utilities.h \
    portaudio/src/hostapi/dsound/pa_win_ds_dynlink.h \
    portaudio/src/hostapi/wasapi/mingw-include/audioclient.h \
    portaudio/src/hostapi/wasapi/mingw-include/devicetopology.h \
    portaudio/src/hostapi/wasapi/mingw-include/endpointvolume.h \
    portaudio/src/hostapi/wasapi/mingw-include/functiondiscoverykeys.h \
    portaudio/src/hostapi/wasapi/mingw-include/ks.h \
    portaudio/src/hostapi/wasapi/mingw-include/ksguid.h \
    portaudio/src/hostapi/wasapi/mingw-include/ksmedia.h \
    portaudio/src/hostapi/wasapi/mingw-include/ksproxy.h \
    portaudio/src/hostapi/wasapi/mingw-include/ksuuids.h \
    portaudio/src/hostapi/wasapi/mingw-include/mmdeviceapi.h \
    portaudio/src/hostapi/wasapi/mingw-include/propkeydef.h \
    portaudio/src/hostapi/wasapi/mingw-include/propsys.h \
    portaudio/src/hostapi/wasapi/mingw-include/rpcsal.h \
    portaudio/src/hostapi/wasapi/mingw-include/sal.h \
    portaudio/src/hostapi/wasapi/mingw-include/structuredquery.h \
    portaudio/src/os/win/pa_win_coinitialize.h \
    portaudio/src/os/win/pa_win_wdmks_utils.h \
    portaudio/src/os/win/pa_x86_plain_converters.h \

FORMS += \
    mainwindow.ui \
    src/WindowAddOperand.ui \
    src/WindowBrakeMarkerEditor.ui \
    src/WindowConfig.ui \
    src/WindowFormulaEditor.ui \
    src/WindowLive.ui \
    src/WindowLoadFormula.ui \
    src/WindowLoadSignal.ui \
    src/WindowSignalEditor.ui \
    src/WindowSignalSetEditor.ui \
    src/WindowTelemetryView.ui \
    src/WindowTelemetryViewerOptions.ui \
    src/WindowTrackListEditor.ui \
    src/WindowTrackSectorEditor.ui

LIBS += -ldsound #Note to self: probably can remove some of these windows libs
LIBS += -ldxguid
LIBS += -lstrsafe
LIBS += -lwmvcore
LIBS += -lmsimg32
LIBS += -lmsacm32
LIBS += -lWinmm
LIBS += -lole32
LIBS += -lAdvapi32
LIBS += -lshell32
LIBS += -luser32

LIBS += -L"C:/Svasta/Mega-Nerd/libsndfile/lib" -llibsndfile-1 \

INCLUDEPATH += "C:/Dev/IRSF/trunk/portaudio/include" \
"C:/Dev/IRSF/trunk/portaudio/src/common" \
"C:/Dev/IRSF/trunk/portaudio/src/os/win" \
"C:/Program Files/Mega-Nerd/libsndfile/include" \
"C:/Dev/IRSF/trunk/portaudio/src/hostapi/asio/ASIOSDK/common" \
"C:/Dev/IRSF/trunk/portaudio/src/hostapi/asio/ASIOSDK/host" \
"C:/Dev/IRSF/trunk/portaudio/src/hostapi/asio/ASIOSDK/host/pc" \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    portaudio/src/SConscript \
#    portaudio/src/hostapi/asio/ASIO-README.txt \
#    portaudio/src/hostapi/asio/ASIOSDK/host/sample/hostsample.dsp \
#    portaudio/src/hostapi/coreaudio/notes.txt \
#    portaudio/src/hostapi/oss/low_latency_tip.txt \
#    portaudio/src/hostapi/skeleton/README.txt \
#    portaudio/src/hostapi/wasapi/readme.txt \
#    portaudio/src/hostapi/wdmks/readme.txt

DISTFILES += \
    portaudio/src/hostapi/asio/ASIO-README.txt \
    portaudio/src/hostapi/asio/ASIOSDK/ASIO SDK 2.3.pdf \
    portaudio/src/hostapi/asio/ASIOSDK/Steinberg ASIO Licensing Agreement.pdf \
    portaudio/src/hostapi/asio/ASIOSDK/Steinberg ASIO Logo Artwork.zip \
    portaudio/src/hostapi/asio/ASIOSDK/asio/asio.dsw \
    portaudio/src/hostapi/asio/ASIOSDK/asio/asio.opt \
    portaudio/src/hostapi/asio/ASIOSDK/changes.txt \
    portaudio/src/hostapi/asio/ASIOSDK/driver/asiosample/asiosample.def \
    portaudio/src/hostapi/asio/ASIOSDK/driver/asiosample/asiosample.txt \
    portaudio/src/hostapi/asio/ASIOSDK/driver/asiosample/asiosample/asiosample.dsp \
    portaudio/src/hostapi/asio/ASIOSDK/driver/asiosample/asiosample/asiosample.vcproj \
    portaudio/src/hostapi/asio/ASIOSDK/host/sample/hostsample.dsp \
    portaudio/src/hostapi/asio/ASIOSDK/host/sample/hostsample.vcproj \
    portaudio/src/hostapi/asio/ASIOSDK/readme.txt \
    portaudio/src/hostapi/asio/Callback_adaptation_.pdf \
    portaudio/src/hostapi/asio/Pa_ASIO.pdf

#RESOURCES += \
 #   gui.qrc
