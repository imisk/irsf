#ifndef CORECONTEXT_H
#define CORECONTEXT_H

#include <memory>
#include "AppDbManager.h"
#include "FormulaDbManager.h"
#include "SignalDbManager.h"
#include "TrackDataManager.h"

namespace irsf {

/*Context which holds the main data manager classes of the application.*/
class CoreContext {
 public:
  explicit CoreContext();

  /*
   * Load the data from disk
   */
  void Initialize();

  FormulaDbManager* GetFormulaDbManager();

  SignalDbManager* GetSignalDbManager();

  TrackDataManager* GetTrackDataManager();

  AppDbManager* GetAppDbManager();

 private:
  std::unique_ptr<FormulaDbManager> formulaDbManager{
      std::make_unique<FormulaDbManager>()};

  std::unique_ptr<SignalDbManager> signalDbManager{
      std::make_unique<SignalDbManager>()};

  std::unique_ptr<TrackDataManager> trackDataManager{
      std::make_unique<TrackDataManager>()};

  std::unique_ptr<AppDbManager> appDbManager{std::make_unique<AppDbManager>()};
};
}  // namespace irsf
#endif  // CORECONTEXT_H
