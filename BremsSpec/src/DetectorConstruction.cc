#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // create world
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSize = 1*m;
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    auto solidWorld = new G4Box("World",0.5*worldSize,0.5*worldSize,worldSize);
    auto logicWorld = new G4LogicalVolume(solidWorld,vacuum,"World");
    auto physWorld = new G4PVPlacement(nullptr,G4ThreeVector(),logicWorld,"World",
    nullptr,false,0);

    // create kapton tape
    // G4double sizeKapton = 0.094*mm;
    // G4Material * kapton = nist->FindOrBuildMaterial("G4_KAPTON");
    // auto solidTape = new G4Box("Tape", 0.5*sizeXY, 0.5*sizeXY, 0.5*sizeKapton);
    // auto logicTape = new G4LogicalVolume(solidTape,kapton,"Tape");

    // G4ThreeVector tapePos = G4ThreeVector(0,0,-0.5*(sizeZ+sizeKapton));
    // new G4PVPlacement(nullptr,tapePos,logicTape,"Tape",logicWorld,false,0);

    // Create target

    G4Material* tantalum = nist->FindOrBuildMaterial("G4_Ta");
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
    auto solidTarget = new G4Box("Target", 0.5*sizeXY, 0.5*sizeXY, 0.5*sizeZ);
    auto logicTarget = new G4LogicalVolume(solidTarget,tungsten,"Target");

    G4double targetPos = 0; // at origin 0,0,0
    new G4PVPlacement(nullptr,G4ThreeVector(0,0,targetPos),logicTarget,"Target",logicWorld,false,0);

    fTargetBackZ = targetPos + 0.5*sizeZ;

    fBremsVolume = logicTarget;

    // Define sensitive detector volume
    G4double detectorThickness = 5*cm;
    G4Box* solidDetector = new G4Box("Detector", 0.5*sizeXY,0.5*sizeXY,0.5*detectorThickness);
    logicDetector = new G4LogicalVolume(solidDetector,vacuum,"Detector");

    // place the detector behind target
    new G4PVPlacement(nullptr,G4ThreeVector(0,0,fTargetBackZ + 0.5*detectorThickness),logicDetector,"Detector",logicWorld,false,0);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    // register as sensitive detector
    auto exitSD = new SensitiveDetector("Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(exitSD);
    logicDetector->SetSensitiveDetector(exitSD);
}