#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "EventAction.hh"

SteppingAction::SteppingAction(DetectorConstruction* det,EventAction* event)
: G4UserSteppingAction(),detector(det),fEventAction(event)
{}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    fDetectorVol = detector->GetCalorVolume();
    G4double edep = step->GetTotalEnergyDeposit();
    G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
    G4int detectorNo = detector->GetNbOfDetectors();
    if (!fDetectorVol) {return;}
    if (edep <=0.) {return;}

    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Use the copy number to identify the detector
    G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    // copy numbers correspond directly to detector indices
    if (volume->GetName() == "logicDetector")
    {
        fEventAction->AddEnergyDeposition(copyNo,edep);
    }


}
