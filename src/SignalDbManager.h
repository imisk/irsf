#ifndef SIGNALDBMANAGER_H
#define SIGNALDBMANAGER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "OUContainer.h"
namespace irsf {

struct IrsfSignal;
struct IrsfSignalSet;

/*
Class responsible for holding the data about user created signals.

to-do : this class no longer respects the single responsibility principle
*/
class SignalDbManager {
 public:
  SignalDbManager() noexcept;

  void SaveSignal(const IrsfSignal& sig);

  void SaveSignalSet(IrsfSignalSet* signalSet);

  void LoadDb();

  void RenameBakToMain();

  void GetSignalNamesForTrack(int32_t trackId,
                              int32_t trackConfigId,
                              std::vector<std::string>& ret) noexcept;

  std::vector<IrsfSignal*>& GetSignalList() noexcept;

  std::vector<IrsfSignalSet*>& GetSignalSetList() noexcept;

  IrsfSignal* GetSignal(std::string signalName) noexcept;

  IrsfSignalSet* GetSignalSet(const std::string& setName) noexcept;

  void DeleteSignalSet(const std::string& signalSetName);

  void RemoveSignalFromSignalSet(const std::string& signalSetName,
                                 const std::string& signalName);

  void AddSignalToSignalSet(const std::string& signalSetName,
                            const std::string& signalName);

  void SaveDb();

  void DeleteSignal(const std::string& signalName);

 private:
  void LoadDbSingleSignal(IrsfSignal& signal);

  void LoadDbSingleSignalSet(IrsfSignalSet& signalSet);

  void SaveDbSingleSignal(IrsfSignal* sig);

  void SaveDbSingleSignalSet(const IrsfSignalSet* set);

  void LoadDbSingleSignalSound(IrsfSignal& signal);

  void SaveDbSingleSignalSound(IrsfSignal* sig);

  OUContainer<IrsfSignal> ouAllSignals;

  OUContainer<IrsfSignalSet> ouAllSignalSets;

  std::ifstream* loadFile;

  std::fstream* saveFile;
};
}  // namespace irsf
#endif  // SIGNALDBMANAGER_H
