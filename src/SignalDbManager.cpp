
#include "SignalDbManager.h"
#include <QDebug>
#include "BinaryReadWriteUtils.h"

namespace irsf {

constexpr int32_t kCurrentSignalDbFileVersion = 1;

SignalDbManager::SignalDbManager() noexcept {}

void SignalDbManager::SaveSignal(const IrsfSignal& sig) {
  bool found = false;
  size_t foundIndex = 0;

  auto& db = ouAllSignals.GetItemList();

  bool finished = false;
  size_t i = 0;

  while (!finished) {
    IrsfSignal* other = db[i];

    if (other->trackId == sig.trackId) {
      if (other->trackConfigId == sig.trackConfigId) {
        if (other->name.compare(sig.name) == 0) {
          found = true;
          foundIndex = i;
          finished = true;
        }
      }
    }

    ++i;
    if (i == db.size())
      finished = true;
  }

  if (found) {
    *db[foundIndex] = sig;

    std::cout << "Updating existing signal and saving: " << sig.name
              << std::endl;  // informative
  } else {
    auto newSig = ouAllSignals.AddItem(sig);

    std::cout << "Adding new signal and saving: " << newSig->name
              << std::endl;  // informative
    std::cout << "New signal count in db = "
              << ouAllSignals.GetItemList().size() << std::endl;
  }

  SaveDb();
}

void SignalDbManager::SaveSignalSet(IrsfSignalSet* signalSet) {
  bool exists = false;

  const auto& db = ouAllSignalSets.GetItemList();

  auto lam = [&](IrsfSignalSet* set) {
    if (set->name.compare(signalSet->name) == 0) {
      return true;
    }
    return false;
  };

  exists = std::any_of(db.begin(), db.end(), lam);

  if (exists)
    throw IrsfException(IrsfError::SignalSetWithThisNameAlreadyExists);

  std::cout << "Saving signal set: " << signalSet->name << std::endl;

  signalSet->signalNames.clear();

  ouAllSignalSets.AddItem(*signalSet);

  SaveDb();
}

void SignalDbManager::LoadDb() {
  bool ShouldLoad = false;

  if (ouAllSignals.GetItemList().size() == 0 &&
      ouAllSignalSets.GetItemList().size() == 0) {
    ShouldLoad = true;
  }

  if (!ShouldLoad)
    return;

  std::cout << "-------------------------- signals Load Db ------------- \n";

  std::string fileName = "Signals.idb";

  auto cstream = fstream_raii_read(fileName);
  loadFile = cstream.get();

  if (loadFile->good() != true)
    throw IrsfException(IrsfError::FileNotFound);

  int32_t readFileVersion = 0;
  ReadBinary(loadFile, &readFileVersion);

  size_t signalCount = 0;
  ReadBinary(loadFile, &signalCount);

  std::cout << "Signals in database: " << signalCount << std::endl;

  ouAllSignals.Clear();

  for (size_t i = 0; i < signalCount; i++) {
    IrsfSignal cSig;
    LoadDbSingleSignal(cSig);
    ouAllSignals.AddItem(cSig);
  }

  size_t signalSetCount = 0;
  ReadBinary(loadFile, &signalSetCount);

  std::cout << "Signal Sets in database: " << signalSetCount << std::endl;

  ouAllSignalSets.Clear();

  for (size_t i = 0; i < signalSetCount; i++) {
    IrsfSignalSet cSet;

    try {
      LoadDbSingleSignalSet(cSet);
    } catch (IrsfException& err) {
      if (err.GetError() == IrsfError::WarningMissingSignalForSignalSet) {
        std::cout << "Warning : missing signal for signal set. \n";
      } else {
        throw;
      }
    }
    ouAllSignalSets.AddItem(cSet);
  }

  std::cout << "Signals.idb loaded succesfuly.\n";
}

void SignalDbManager::RenameBakToMain() {
  int32_t status;

  std::cout << "Renaming bak to main: Signals.idb \n";

  status = remove("Signals.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file Signals.idb \n";

  status = rename("Signals_bak.idb", "Signals.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "Signals_bak.idb to Signals.idb \n";
}

void SignalDbManager::GetSignalNamesForTrack(
    int32_t trackId,
    int32_t trackConfigId,
    std::vector<std::string>& ret) noexcept {
  const auto& db = ouAllSignals.GetItemList();

  for (const auto& sig : db) {
    if (sig->trackId == trackId) {
      if (trackId != 0) {
        if (sig->trackConfigId == trackConfigId) {
          ret.push_back(sig->name);
        }
      } else {
        ret.push_back(sig->name);
      }
    }
  }
}

std::vector<IrsfSignal*>& SignalDbManager::GetSignalList() noexcept {
  return ouAllSignals.GetItemList();
}

std::vector<IrsfSignalSet*>& SignalDbManager::GetSignalSetList() noexcept {
  return ouAllSignalSets.GetItemList();
}

IrsfSignal* SignalDbManager::GetSignal(std::string signalName) noexcept {
  const auto& db = ouAllSignals.GetItemList();

  for (const auto& sig : db) {
    if (sig->name == signalName) {
      return sig;
    }
  }

  return nullptr;
}

IrsfSignalSet* SignalDbManager::GetSignalSet(
    const std::string& setName) noexcept {
  const auto& db = ouAllSignalSets.GetItemList();

  for (const auto& s : db) {
    if (s->name.compare(setName) == 0) {
      return s;
    }
  }

  std::cout << "Error : SignalSet not found. \n";
  return nullptr;
}

void SignalDbManager::DeleteSignalSet(const std::string& signalSetName) {
  bool found = false;
  std::streamsize deleteIndex = 0;

  const auto& db = ouAllSignalSets.GetItemList();

  size_t i = 0;
  bool finished = false;

  while (!finished) {
    if (signalSetName.compare(db[i]->name) == 0) {
      found = true;
      deleteIndex = static_cast<std::streamsize>(i);
      finished = true;
    }

    ++i;
    if (i == db.size())
      finished = true;
  }

  if (found) {
    ouAllSignalSets.EraseAtIndex(deleteIndex);

    SaveDb();

    return;
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void SignalDbManager::RemoveSignalFromSignalSet(
    const std::string& signalSetName,
    const std::string& signalName) {
  bool found = false;
  std::streamsize setIndex = 0;

  auto& db = ouAllSignalSets.GetItemList();

  size_t i = 0;
  bool finished = false;

  while (!finished) {
    if (signalSetName.compare(db[i]->name) == 0) {
      found = true;
      setIndex = static_cast<std::streamsize>(i);
      finished = true;
    }

    ++i;
    if (i == db.size())
      finished = true;
  }

  if (!found)
    throw IrsfError::ItemNotFound;

  IrsfSignalSet* set = db[static_cast<size_t>(setIndex)];

  found = false;
  std::streamsize deleteIndex = 0;
  for (size_t i = 0; i < set->signalNames.size(); i++) {
    if (set->signalNames[i].compare(signalName) == 0) {
      std::cout << "Deleting signal from set. \n";
      found = true;
      deleteIndex = static_cast<std::streamsize>(i);
      break;
    }
  }

  if (found) {
    set->signalNames.erase(set->signalNames.begin() + deleteIndex);

    SaveDb();

    return;
  } else {
    throw IrsfException(IrsfError::ItemNotFound);
  }
}

void SignalDbManager::AddSignalToSignalSet(const std::string& signalSetName,
                                           const std::string& signalName) {
  bool found = false;

  size_t foundIndex = 0;
  bool finished = false;
  auto& db = ouAllSignalSets.GetItemList();

  size_t i = 0;

  while (!finished) {
    if (signalSetName.compare(db[i]->name) == 0) {
      found = true;
      foundIndex = i;
      finished = true;
    }

    ++i;
    if (i == db.size())
      finished = true;
  }

  if (!found)
    throw IrsfException(IrsfError::ItemNotFound);

  IrsfSignalSet* set = db[foundIndex];

  found = false;

  // Check if signal already added
  for (size_t i = 0; i < set->signalNames.size(); i++) {
    if (set->signalNames[i].compare(signalName) == 0) {
      found = true;
    }
  }

  if (found)
    throw IrsfException(IrsfError::ItemAlreadyExists);

  set->signalNames.push_back(signalName);
}

void SignalDbManager::SaveDb() {
  int32_t status = 0;

  // Create backup
  status = remove("Signals_bak.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file Signals_bak.idb \n";

  status = rename("Signals.idb", "Signals_bak.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "Signals.idb to Signals_bak.idb \n";

  std::string fileName = "Signals.idb";
  auto f = fstream_raii_write(fileName);
  saveFile = f.get();

  if (saveFile->is_open() == false)
    throw IrsfException(IrsfError::CannotOpenFile);

  // file version
  auto ver = kCurrentSignalDbFileVersion;
  WriteBinary(*saveFile, &ver);

  //--- Signals count
  size_t count = ouAllSignals.GetItemList().size();
  WriteBinary(*saveFile, &count);

  // Save each one:
  auto& db = ouAllSignals.GetItemList();
  for (size_t i = 0; i < db.size(); i++) {
    SaveDbSingleSignal(db[i]);
  }

  //----- Signal sets
  count = ouAllSignalSets.GetItemList().size();
  WriteBinary(*saveFile, &count);

  auto& dbset = ouAllSignalSets.GetItemList();
  for (size_t i = 0; i < count; i++) {
    SaveDbSingleSignalSet(dbset[i]);
  }

  std::cout << "Signals database updated. \n";
}

void SignalDbManager::DeleteSignal(const std::string& signalName) {
  bool found = false;
  std::streamsize deleteIndex = 0;

  auto& db = ouAllSignals.GetItemList();
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (signalName.compare(db[i]->name) == 0) {
      found = true;
      deleteIndex = static_cast<std::streamsize>(i);
      finished = true;
    }

    ++i;
    if (i == db.size())
      finished = true;
  }

  if (found) {
    ouAllSignals.EraseAtIndex(deleteIndex);

    SaveDb();

    return;
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void SignalDbManager::LoadDbSingleSignal(IrsfSignal& signal) {
  size_t nameSize = 0;

  // name
  ReadBinary(loadFile, &nameSize);

  signal.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(loadFile, &signal.name[0], nameSize);

  ReadBinary(loadFile, &signal.trackId);
  ReadBinary(loadFile, &signal.trackConfigId);
  ReadBinary(loadFile, &nameSize);

  // formulaName
  signal.formulaName = std::string(nameSize, ' ');
  ReadBinaryCharArray(loadFile, &signal.formulaName[0], nameSize);

  ReadBinary(loadFile, &signal.secondRangeActive);
  ReadBinary(loadFile, &signal.range1.min);
  ReadBinary(loadFile, &signal.range1.max);
  ReadBinary(loadFile, &signal.range2.min);
  ReadBinary(loadFile, &signal.range2.max);
  ReadBinary(loadFile, &signal.useFullTrack);
  ReadBinary(loadFile, &signal.trackSectorId);

  LoadDbSingleSignalSound(signal);
}

void SignalDbManager::LoadDbSingleSignalSet(IrsfSignalSet& signalSet) {
  size_t nameSize = 0;

  // name
  ReadBinary(loadFile, &nameSize);

  signalSet.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(loadFile, &signalSet.name[0], nameSize);

  ReadBinary(loadFile, &signalSet.trackId);

  ReadBinary(loadFile, &signalSet.trackConfigId);

  size_t signalCount = 0;
  ReadBinary(loadFile, &signalCount);

  bool missingSignal = false;

  for (size_t i = 0; i < signalCount; i++) {
    std::string curSignalName;

    ReadBinary(loadFile, &nameSize);

    curSignalName = std::string(nameSize, ' ');
    ReadBinaryCharArray(loadFile, &curSignalName[0], nameSize);

    bool finished = false;
    bool found = false;
    auto& db = ouAllSignals.GetItemList();
    size_t j = 0;

    while (!finished) {
      auto& sig = db[j];
      if (sig->name.compare(curSignalName) == 0) {
        found = true;
        signalSet.signalNames.push_back(curSignalName);
        finished = true;
      }

      ++j;
      if (j == db.size())
        finished = true;
    }

    if (!found) {
      std::cout << "Cannot completely load signal set " << signalSet.name
                << ". Missing signal in database: " << curSignalName
                << std::endl;
      missingSignal = true;
    }
  }

  if (missingSignal)
    throw IrsfException(IrsfError::WarningMissingSignalForSignalSet);
}

void SignalDbManager::SaveDbSingleSignal(IrsfSignal* sig) {
  IrsfSignal s = *sig;

  size_t nameSize = s.name.size();
  WriteBinary(*saveFile, &nameSize);

  WriteBinaryCharArray(*saveFile, s.name.c_str(), nameSize);

  WriteBinary(*saveFile, &s.trackId);

  WriteBinary(*saveFile, &s.trackConfigId);

  size_t formulaNameSize = s.formulaName.size();
  WriteBinary(*saveFile, &formulaNameSize);

  WriteBinaryCharArray(*saveFile, s.formulaName.c_str(), formulaNameSize);

  WriteBinary(*saveFile, &s.secondRangeActive);

  //--- range 1
  WriteBinary(*saveFile, &s.range1.min);

  WriteBinary(*saveFile, &s.range1.max);

  //--- range 2
  WriteBinary(*saveFile, &s.range2.min);

  WriteBinary(*saveFile, &s.range2.max);

  WriteBinary(*saveFile, &s.useFullTrack);

  WriteBinary(*saveFile, &s.trackSectorId);

  SaveDbSingleSignalSound(sig);
}

void SignalDbManager::SaveDbSingleSignalSet(const IrsfSignalSet* set) {
  IrsfSignalSet s = *set;

  size_t nameSize = s.name.size();
  WriteBinary(*saveFile, &nameSize);

  WriteBinaryCharArray(*saveFile, s.name.c_str(), nameSize);

  WriteBinary(*saveFile, &s.trackId);

  WriteBinary(*saveFile, &s.trackConfigId);

  // write signal count
  size_t count = s.signalNames.size();
  WriteBinary(*saveFile, &count);

  for (const auto& sigName : s.signalNames) {
    nameSize = sigName.size();
    WriteBinary(*saveFile, &nameSize);

    WriteBinaryCharArray(*saveFile, sigName.c_str(), nameSize);
  }
}

void SignalDbManager::LoadDbSingleSignalSound(IrsfSignal& signal) {
  size_t nameSize = 0;

  // name
  ReadBinary(loadFile, &nameSize);

  if (nameSize > 0) {
    signal.sound.soundFileName = std::string(nameSize, ' ');
    ReadBinaryCharArray(loadFile, &signal.sound.soundFileName[0], nameSize);
  } else {
    signal.sound.soundFileName = "None";
  }

  ReadBinary(loadFile, &signal.sound.soundVolume);
  ReadBinary(loadFile, &signal.sound.curve);
}

void SignalDbManager::SaveDbSingleSignalSound(IrsfSignal* sig) {
  SignalSound s = sig->sound;

  size_t nameSize = s.soundFileName.size();
  WriteBinary(*saveFile, &nameSize);

  WriteBinaryCharArray(*saveFile, s.soundFileName.c_str(), nameSize);

  WriteBinary(*saveFile, &s.soundVolume);

  WriteBinary(*saveFile, &s.curve);
}
}  // namespace irsf
