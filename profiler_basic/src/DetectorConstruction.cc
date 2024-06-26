#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction()
{
    // Initialize materials and thicknesses
    G4NistManager* nist = G4NistManager::Instance();

    // Populate materials and thicknesses directly
    filterMaterials = {nist->FindOrBuildMaterial("G4_Al"), nist->FindOrBuildMaterial("G4_Pb")};
    filterThicknesses = {0.5*mm, 0.5*mm};

    detectorMaterials = {nist->FindOrBuildMaterial("G4_POLYETHYLENE"), nist->FindOrBuildMaterial("G4_Al")};
    detectorThicknesses = {0.5*mm, 5*mm};

    NbOfDetectors = filterMaterials.size();
}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    return ConstructCalorimeter();
}

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{
    // World
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    
    G4double worldSize = 1.0*m;
    G4Box* solidWorld = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);
    
    // Calorimeter
    G4double posZ = 3*cm; // Initial Z position
    
    for(size_t i = 0; i < filterMaterials.size(); ++i)
    {
        // Filter
        G4Box* solidFilter = new G4Box("Filter", 5*cm, 5*cm, filterThicknesses[i]/2);
        G4LogicalVolume* logicFilter = new G4LogicalVolume(solidFilter, filterMaterials[i], "Filter");
        new G4PVPlacement(0, G4ThreeVector(0, 0, posZ + filterThicknesses[i]/2), logicFilter, "Filter", logicWorld, false, i, true);
        posZ += filterThicknesses[i];

        // Detector
        G4Box* solidDetector = new G4Box("Detector", 5*cm, 5*cm, detectorThicknesses[i]/2);
        G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, detectorMaterials[i], "Detector");
        new G4PVPlacement(0, G4ThreeVector(0, 0, posZ + detectorThicknesses[i]/2), logicDetector, "Detector", logicWorld, false, i, true);
        posZ += detectorThicknesses[i];
    }
    
    return physWorld;
}
