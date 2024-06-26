#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include <G4UserSteppingAction.hh>
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

private:
    EventAction* fEventAction;
};

#endif
