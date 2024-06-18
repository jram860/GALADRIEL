#ifndef SteppingAction_h
#define SteppingAciton_h

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction: public G4UserSteppingAction
{
    public:
        SteppingAction(DetectorConstruction*,EventAction*);
        ~SteppingAction();

        void UserSteppingAction(const G4Step*) override;

    private:
        EventAction * fEventAction = nullptr;
        DetectorConstruction* detector;

        G4bool first;
        G4LogicalVolume* fDetectorVol;
};
#endif