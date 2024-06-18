#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"

void ActionInitialization::Build() const 
{
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction());
    SetUserAction(new SteppingAction());
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}