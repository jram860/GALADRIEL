#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {
    auto runAction = new RunAction();
    auto eventAction = new EventAction();
    SetUserAction(runAction);
    SetUserAction(eventAction);
    SetUserAction(new PrimaryGeneratorAction);
    auto detectorConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    auto detectorVolumes = detectorConstruction->GetDetectorVolumes();

    SetUserAction(new SteppingAction(eventAction, detectorVolumes));
}
