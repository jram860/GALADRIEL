#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

#include <fstream>
#include <sstream>

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Construct World
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Box* solidWorld = new G4Box("World", 50*cm, 50*cm, 50*cm);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,worldMat,"World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0);

    std::vector<Layer> layers = ReadConfig("geomConfig.txt");
    ConstructProfiler(layers,logicWorld);

    return physWorld;
}

std::vector<Layer> DetectorConstruction::ReadConfig(const std::string& filename) {
    std::vector<Layer> layers;
    std::ifstream file(filename);
    if (!file.is_open()) {
        G4Exception("ReadConfig", "FileNotFound", FatalException, "Cannot open the config file");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0]== '#' || line.empty()) continue;
        std::istringstream iss(line);
        Layer layer;
        iss >> layer.type >> layer.material >> layer. thickness;
        layers.push_back(layer);
    }

    return layers;
}

void DetectorConstruction::ConstructProfiler(const std::vector<Layer>& layers,G4LogicalVolume* logicWorld) {
    G4NistManager* nist = G4NistManager::Instance();

    G4double zPos = 0.0; // Can Change to add offset
    for (const auto& layer : layers) {
        G4Material* material = nist->FindOrBuildMaterial("G4_" + layer.material);
        if (!material) {
            G4Exception("ConstructProfiler", "MaterialNotFound",FatalException,"Material not found in NIST database");
        }

        G4Box* solidLayer = new G4Box(layer.type + "_solid", 50.*mm,50.*mm, 0.5*layer.thickness*mm);
        G4LogicalVolume* logicLayer = new G4LogicalVolume(solidLayer, material, layer.type + "_logic");

        new G4PVPlacement(0,G4ThreeVector(0,0, zPos + 0.5*layer.thickness*mm), logicLayer, layer.type + "_phys", logicWorld,false,0,true);

        zPos += layer.thickness*mm;

        G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
        if (layer.type == "filter") {
            visAttr->SetColour(G4Colour(0.0,0.0,1.0));
        } else if (layer.type == "detector") {
            visAttr->SetColour(G4Colour(0.0,1.0,0.0));
        }
        logicLayer->SetVisAttributes(visAttr);
    }
}