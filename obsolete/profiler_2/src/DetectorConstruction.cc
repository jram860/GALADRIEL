#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4double world_size = 1.0 * m;
    G4Box* solidWorld = new G4Box("World", world_size, world_size, world_size);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    G4double filterThicknesses[] = {3.0 * mm, 1.0 * mm};
    G4double detectorThicknesses[] = {2.0 * mm, 8.0 * mm};
    G4String filterMaterials[] = {"G4_Pb", "G4_W"};
    G4String detectorMaterials[] = {"G4_Al", "G4_PLASTIC_SC_VINYLTOLUENE"};

    G4double zPosition = -0.5 * world_size;

    for (size_t i = 0; i < 2; ++i) {
        G4Box* filterSolid = new G4Box("Filter", 10.0 * cm, 10.0 * cm, filterThicknesses[i] / 2);
        G4LogicalVolume* filterLogic = new G4LogicalVolume(filterSolid, nist->FindOrBuildMaterial(filterMaterials[i]), "Filter");
        new G4PVPlacement(0, G4ThreeVector(0, 0, zPosition + filterThicknesses[i] / 2), filterLogic, "Filter", logicWorld, false, i, true);
        zPosition += filterThicknesses[i];

        G4Box* detectorSolid = new G4Box("Detector", 10.0 * cm, 10.0 * cm, detectorThicknesses[i] / 2);
        G4LogicalVolume* detectorLogic = new G4LogicalVolume(detectorSolid, nist->FindOrBuildMaterial(detectorMaterials[i]), "Detector");
        new G4PVPlacement(0, G4ThreeVector(0, 0, zPosition + detectorThicknesses[i] / 2), detectorLogic, "Detector", logicWorld, false, i, true);
        zPosition += detectorThicknesses[i];

        fDetectorVolumes.push_back(detectorLogic);
    }

    return physWorld;
}
