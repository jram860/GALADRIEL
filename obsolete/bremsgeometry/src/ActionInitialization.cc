#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* det)
: G4VUserActionInitialization(),fDetector(det)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{}

void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primary = new PrimaryGeneratorAction;
    SetUserAction(primary);
}