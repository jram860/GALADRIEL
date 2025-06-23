#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(DetectorConstruction*, EventAction*);
    virtual ~SteppingAction();
    
    virtual void UserSteppingAction(const G4Step*);
    
private:
    EventAction* fEventAction = nullptr;
    DetectorConstruction* detector;

    G4bool first;
    G4LogicalVolume* fDetectorVol;
};

#endif // STEPPINGACTION_HH
