#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include <iostream>

DetectorMessenger::DetectorMessenger(DetectorConstruction* det) : G4UImessenger(), fDetector(det) {
    
    fDirectory = new G4UIdirectory("/StackGeometry/");
    fDirectory->SetGuidance("Set the Filter Stack Construction.");

    //Filter
    fFilterThicknessesCmd = new G4UIcmdWithADoubleAndUnit("/StackGeometry/setFilterThicknesses",this);
    fFilterThicknessesCmd->SetGuidance("Set the filter Thicknesses");
    fFilterThicknessesCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    fDetectorThicknessesCmd = new G4UIcmdWithADoubleAndUnit("/StackGeometry/setDetectorThicknesses", this);
    fDetectorThicknessesCmd->SetGuidance("Set the detector Geometry");
    fDetectorThicknessesCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    fFilterMaterialsCmd = new G4UIcmdWithAString("/StackGeometry/setFilterMaterials",this);
    fFilterMaterialsCmd->SetGuidance("Set the filter thicknesses");
    fFilterMaterialsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fDetectorMaterialsCmd = new G4UIcmdWithAString("/StackGeometry/setDetectorMaterials",this);
    fDetectorMaterialsCmd->SetGuidance("Set the detector thicknesses");
    fDetectorMaterialsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

DetectorMessenger::~DetectorMessenger() {
    delete fFilterMaterialsCmd;
    delete fDetectorMaterialsCmd;
    delete fFilterThicknessesCmd;
    delete fDetectorThicknessesCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == fFilterThicknessesCmd) {
        fDetector->SetFilterThicknesses(newValue);
    } else if (command == fDetectorThicknessesCmd) {
        fDetector->SetDetectorThicknesses(newValue);
    } else if (command == fFilterMaterialsCmd) {
        fDetector->SetFilterMaterials(newValue);
    } else if (command == fDetectorMaterialsCmd) {
        fDetector->SetDetectorMaterials(newValue);
    }
    
    G4RunManager::GetRunManager()->ReinitializeGeometry();

}