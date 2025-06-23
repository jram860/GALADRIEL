#include "ConverterMessenger.hh"
#include "G4UImanager.hh"

#include <iostream>

ConverterMessenger::ConverterMessenger(DetectorConstruction* DetectorConstruction)
: G4UImessenger(), fDetector(DetectorConstruction) {
    
    // create the directory for the UI commands
    fDirectory = new G4UIdirectory("/converter/");
    fDirectory->SetGuidance("Commands to control the converter foil");

    // set the commands

    fAddConverterCmd = new G4UIcmdWithoutParameter("/converter/add",this);
    fAddConverterCmd->SetGuidance("Add converter foil");
    fAddConverterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    fRemoveConverterCmd = new G4UIcmdWithoutParameter("/converter/remove",this);
    fRemoveConverterCmd->SetGuidance("Remove the converter foil");
    fRemoveConverterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fPositionCmd = new G4UIcmdWithADoubleAndUnit("/converter/setPosition",this);
    fPositionCmd->SetGuidance("Set the midpoint location of converter w.r.t beam axis.");
    fPositionCmd->SetParameterName("z",false);
    fPositionCmd->SetDefaultUnit("mm");
    fPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

void ConverterMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == fAddConverterCmd) {
        fDetector->AddConverter();
    }
    if (command == fRemoveConverterCmd) {
        fDetector->RemoveConverter();
    }

    if (command == fPositionCmd) {
        fDetector->SetConverterPosition(fPositionCmd->GetNewDoubleValue(newValue));
    }

    // update the viewport
    G4UImanager *UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/viewer/rebuild");
}