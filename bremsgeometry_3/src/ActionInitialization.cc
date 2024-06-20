#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
}

void ActionInitialization::BuildForMaster() const
{}