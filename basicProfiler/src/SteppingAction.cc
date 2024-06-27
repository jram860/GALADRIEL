#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "EventAction.hh"

SteppingAction::SteppingAction(DetectorConstruction* det,EventAction* event)
: G4UserSteppingAction(),detector(det),fEventAction(event)
{
    first = true;
    fDetectorVol = 0;
    // may or may not use the above.
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0.) return;

    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Use the copy number to identify the detector
    G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0);

    // copy numbers correspond directly to detector indices
    if (volume)
    if (volume->GetName() == "Detector")
    {
        fEventAction->AddEnergyDeposition(copyNo,edep);
    }


}
