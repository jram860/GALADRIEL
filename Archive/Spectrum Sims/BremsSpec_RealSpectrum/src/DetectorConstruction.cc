#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"

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
    G4double sizeXY = 50*mm;
    G4double sizeZ = 997*um;
    G4double sizeKapton = 0.094*mm;
    G4Material * kapton = nist->FindOrBuildMaterial("G4_KAPTON");
    auto solidTape = new G4Box("Tape", 0.5*sizeXY, 0.5*sizeXY, 0.5*sizeKapton);
    auto logicTape = new G4LogicalVolume(solidTape,kapton,"Tape");

    G4ThreeVector tapePos = G4ThreeVector(0,0,-0.5*(sizeZ+sizeKapton));
    new G4PVPlacement(nullptr,tapePos,logicTape,"Tape",logicWorld,false,0);

    // Create target

    G4Material* tantalum = nist->FindOrBuildMaterial("G4_Ta");
    auto solidTarget = new G4Box("Target", 0.5*sizeXY, 0.5*sizeXY, 0.5*sizeZ);
    auto logicTarget = new G4LogicalVolume(solidTarget,tantalum,"Target");

    G4ThreeVector targetPos = G4ThreeVector(); // at origin 0,0,0
    new G4PVPlacement(nullptr,targetPos,logicTarget,"Target",logicWorld,false,0);

    fBremsVolume = logicTarget;
    return physWorld;
}