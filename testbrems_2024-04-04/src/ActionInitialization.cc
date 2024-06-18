#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* det)
: G4VUserActionInitialization(),fDetector(det)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction(fDetector));
}

void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primary = new PrimaryGeneratorAction;
    SetUserAction(primary);

    RunAction* runAction = new RunAction(fDetector,primary);
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(fDetector);
    SetUserAction(eventAction);

    SetUserAction(new SteppingAction(fDetector,eventAction));
}