
#include "irsdkmanager.h"
#include "InputVariableRaw.h"
#include "Utilities.h"
#include "irsdkutility.h"

using namespace irsf;

namespace irsf {
namespace irsdk {

IrsdkManager::IrsdkManager() {
  varData->data = nullptr;
}

bool IrsdkManager::Startup() {
  if (!winCtr->hMemMapFile) {
    // ugly code copied from IRSDK examples...
    winCtr->hMemMapFile =
        OpenFileMapping(FILE_MAP_READ, FALSE, IRSDK_MEMMAPFILENAME);
  }

  if (winCtr->hMemMapFile) {
    if (!winCtr->pSharedMem) {
      winCtr->pSharedMem = static_cast<const char*>(
          MapViewOfFile(winCtr->hMemMapFile, FILE_MAP_READ, 0, 0, 0));

      // option 2
      varData->pHeader = static_cast<irsdk_header*>(
          MapViewOfFile(winCtr->hMemMapFile, FILE_MAP_READ, 0, 0, 0));
    }

    if (winCtr->pSharedMem) {
      if (!winCtr->hDataValidEvent) {
        winCtr->hDataValidEvent =
            OpenEvent(SYNCHRONIZE, false, IRSDK_DATAVALIDEVENTNAME);
      }

      if (winCtr->hDataValidEvent) {
        isInitialized = true;
        varData->lastTickCount = INT_MIN;

        if (varData->variableHeaders.empty())
          UpdateVarHeaders();

        if (!IrsdkResizeData(varData.get()))
          return false;

        return true;
      }
    }
  }
  return false;
}

bool IrsdkManager::WaitForData() {
  unsigned long timeOut = 100;

  if (isInitialized) {
    // just to be sure, check before we sleep       ...
    // if(irsdk_getNewData(data))   //code not relevent (from irsdk)
    //  return true;

    if (UpdateTelemetry())
      return true;

    // sleep till signaled
    WaitForSingleObject(winCtr->hDataValidEvent, timeOut);

    // we woke up, so check for data
    // if(irsdk_getNewData(data))
    // return true;
    if (UpdateTelemetry())
      return true;
    else
      return false;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(timeOut));

  return false;
}

void IrsdkManager::GetIrsdkValuePointer(const std::string& varName,
                                        irsdk_VarType& retType,
                                        void*& retPtr) {
  int32_t valIdx = -1;

  valIdx = irsdk_varNameToIndex(varData.get(), winCtr.get(), varName.c_str());

  if (valIdx == -1) {
    qDebug() << "Error : variable name not found.";
    throw IrsfException(IrsfError::IrsdkVariableNameNotFound);
  }

  irsdk_varHeader* item =
      varData->variableHeaders[static_cast<unsigned>(valIdx)];

  retType = static_cast<irsdk_VarType>(item->type);
  // ugly code copied from IRSDK examples...
  retPtr = reinterpret_cast<void*>((varData->data + item->offset));

  return;
}

void IrsdkManager::InitVariables(
    const std::vector<VariableId>& inputVariablesIn,
    std::vector<iVarInterface_sp>& retInputVariables,
    std::vector<iVarRawInterface_sp>& retInputVariablesNonFloat) {
  for (const auto& varId : inputVariablesIn) {
    irsdk_VarType curType = irsdk_int;
    void* curPtr = nullptr;

    GetIrsdkValuePointer(GetVariableNameFromVariableId(varId), curType, curPtr);

    if (curType == irsdk_int) {
      int32_t* curPtrI = reinterpret_cast<int32_t*>(curPtr);
      std::unique_ptr<int32_t> is(curPtrI);

      auto ivi =
          std::make_shared<InputVariableRaw<int32_t>>(varId, std::move(is));

      retInputVariables.push_back(ivi);
      retInputVariablesNonFloat.push_back(ivi);

    } else if (curType == irsdk_float) {
      float* curPtrF = reinterpret_cast<float*>(curPtr);
      std::unique_ptr<float> fs(curPtrF);

      auto iv = std::make_shared<InputVariableRaw<float>>(varId, std::move(fs));

      retInputVariables.push_back(iv);

    } else if (curType == irsdk_double) {
      double* curPtrD = reinterpret_cast<double*>(curPtr);
      std::unique_ptr<double> ds(curPtrD);

      auto iv =
          std::make_shared<InputVariableRaw<double>>(varId, std::move(ds));

      retInputVariables.push_back(iv);
      retInputVariablesNonFloat.push_back(iv);
    } else {
      /*
       * this can happen if iRacing implements new data
       * type we don't support
       */
      throw IrsfError::IrsdkVariableIsUnsupportedType;
    }
  }

  qDebug() << "Added variable count = " << retInputVariables.size();
  qDebug() << "Added variable count non-float = "
           << retInputVariablesNonFloat.size();
}

void IrsdkManager::UpdateVarHeaders() {
  varData->variableHeaders.clear();

  for (int32_t index = 0; index < varData->pHeader->numVars; ++index) {
    irsdk_varHeader* pVarHeader =
        &(reinterpret_cast<irsdk_varHeader*>(const_cast<char*>(
            (winCtr->pSharedMem + varData->pHeader->varHeaderOffset))))[index];

    varData->variableHeaders.push_back(pVarHeader);
  }
}

bool IrsdkManager::UpdateTelemetry() {
  if (isInitialized && varData->pHeader->status == irsdk_stConnected) {
    // Find latest buffer
    int32_t latestBufferIndex = 0;
    for (int32_t i = 1; i < varData->pHeader->numBuf; i++) {
      if (varData->pHeader->varBuf[latestBufferIndex].tickCount <
          varData->pHeader->varBuf[i].tickCount)
        latestBufferIndex = i;
    }

    if (varData->lastTickCount <
        varData->pHeader->varBuf[latestBufferIndex].tickCount) {
      if (varData->dataLength !=
          static_cast<unsigned long long>(varData->pHeader->bufLen))
        IrsdkResizeData(varData.get());

      // try twice to get the data out
      for (int32_t count = 0; count < 2; count++) {
        int32_t curTickCount =
            varData->pHeader->varBuf[latestBufferIndex].tickCount;

        memcpy(varData->data,
               winCtr->pSharedMem +
                   varData->pHeader->varBuf[latestBufferIndex].bufOffset,
               static_cast<size_t>(varData->pHeader->bufLen));

        if (curTickCount ==
            varData->pHeader->varBuf[latestBufferIndex].tickCount) {
          /*Check that a tick didn't happen during memcpy
           *NOTE: lastValidTime is only used to check for
           *timeout, perhaps not needed.
           *see irsdk_isConnected()
           */
          varData->lastTickCount = curTickCount;
          varData->lastValidTime = time(nullptr);
          return true;
        }
      }
    }
  } else {
    return false;
  }

  return false;
}

}  // namespace irsdk
}  // namespace irsf
