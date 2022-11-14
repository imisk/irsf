#ifndef APPDBMANAGER_H
#define APPDBMANAGER_H

#include <QString>
#include <fstream>
#include <vector>
#include "IrsfCommon.h"

/*
 * Manages general application data
 *
 * to-do : this class no longer respects the single responsibility principle
 */
namespace irsf {

class AppDbManager {
 public:
  AppDbManager();

  // Returns true if brake marker set with given name already exists
  bool BrakeMarkerSetExists(std::string& name);

  // Creates new set and returns pointer to it - nullptr on fail
  BrakeMarkerSet* CreateNewBrakeMarkerSet(std::string& name);

  // Returns nullptr on fail
  BrakeMarkerSet* GetBrakeMarkerSet(std::string& name);

  std::vector<QString> GetBrakeMarkerSetNameList();

  void LoadDb();

  void RenameBakToMain();

  void DeleteBrakeMarkerSet(std::string& name);

  void AddBrakeMarkerToBrakeMarkerSet(std::string& setName, BrakeMarker& bm);

  void DeleteBrakeMarkerFromBrakeMarkerSet(std::string& setName,
                                           std::string& brakeMarkerItemText);

  void SaveDb();

  AppConfig* GetAppConfig();

  void ResetAppConfigToDefault();

  void ResetTelemetryVariablesToDefault();

  void AddVariableIdToTelemetryRecording(VariableId varId);

  void DeleteVariableIdFromTelemetryRecording(VariableId varId);

 private:
  void LoadAppConfig();

  void SaveAppConfig();

  void SaveBrakeMarkerSet(BrakeMarkerSet& set);

  void LoadBrakeMarkerSet(BrakeMarkerSet& set);

  std::vector<BrakeMarkerSet> brakeMarkerSets;

  std::ifstream* loadFile{nullptr};

  std::fstream* saveFile{nullptr};

  std::unique_ptr<AppConfig> appConfig{std::make_unique<AppConfig>()};
};

}  // namespace irsf
#endif  // APPDBMANAGER_H
