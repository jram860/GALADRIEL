#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include <G4UserSteppingAction.hh>
#include <vector>
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(EventAction* eventAction, const std::vector<G4LogicalVolume*>& detectorVolumes);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step) override;

private:
    EventAction* fEventAction;
    std::vector<G4LogicalVolume*> fDetectorVolumes;
};

#endif