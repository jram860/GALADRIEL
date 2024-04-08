#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt)
: G4UserSteppingAction(),detector(det),fEventAction(evt)
{
    first = true;
    fDetectorVol = 0;
}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    if (first) {
        fDetectorVol = detector->GetDetectorVol();
        first = false;
    }

    G4double edep = step->GetTotalEnergyDeposit();

    G4int modNum = 0.;

    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
    G4LogicalVolume* lvol = touchable->GetVolume()->GetLogicalVolume();

    if (lvol != fDetectorVol) return;
    else if (lvol == fDetectorVol) {modNum = touchable->GetCopyNumber(0);}

    // const G4StepPoint* prePoint = step->GetPreStepPoint();
    // const G4StepPoint* endPoint = step->GetPostStepPoint();
    // G4int modNum  = prePoint->GetTouchableHandle()->GetCopyNumber(0);
       
    // G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
    // ->GetVolume()->GetLogicalVolume();

    // if (volume !=fDetectorVol) {
    //     return;
    // }

    fEventAction->AddEdep(modNum,edep);
}