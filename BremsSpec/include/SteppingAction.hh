#ifndef SteppingAction_hh
#define SteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

class SteppingAction : public G4UserSteppingAction
{
    public:
        SteppingAction();
        ~SteppingAction();

        void UserSteppingAction(const G4Step*) override;
    
    private:
        G4LogicalVolume* fBremsVolume = nullptr;
        G4double fTargetBackZ;
};
#endif