#include "SteppingAction.hh"
#include <G4Step.hh>
#include <G4LogicalVolume.hh>

SteppingAction::SteppingAction(EventAction* eventAction, const std::vector<G4LogicalVolume*>& detectorVolumes)
    : G4UserSteppingAction(), fEventAction(eventAction), fDetectorVolumes(detectorVolumes) {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    G4double edep = step->GetTotalEnergyDeposit();

    for (size_t i = 0; i < fDetectorVolumes.size(); ++i) {
        if (volume == fDetectorVolumes[i]) {
            fEventAction->AddDose(i, edep);
            break;
        }
    }
}