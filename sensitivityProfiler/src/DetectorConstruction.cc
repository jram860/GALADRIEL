#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

#include <fstream>
#include <sstream>

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
  
DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct() {
    DefineMaterials();
    ReadGeometryFile("geomConfig.txt");
    // Construct the World
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeXY = 2*calorSizeXY;
    if (calorSizeZ<=1*m) {worldSizeZ = 2*m;} else {worldSizeZ =2.5*calorSizeZ;}
    worldMaterial = nist->FindOrBuildMaterial("G4_Galactic");
    auto solidWorld = new G4Box("World", worldSizeXY/2,worldSizeXY/2,worldSizeZ/2);
    auto logicWorld = new G4LogicalVolume(solidWorld,worldMaterial,"World");
    auto physiWorld = new G4PVPlacement(nullptr,G4ThreeVector(),logicWorld,"World",nullptr,false,0);

    ConstructCalorimeter(logicWorld);
    PrintCalorParameters();

    return physiWorld;
}

void DetectorConstruction::ReadGeometryFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        G4cerr << "Error opening file: " << fileName << G4endl;
        return;
    }

    while (std::getline(file,line)) {
        if (line.empty() || line[0] == '#') {continue;}

        std::istringstream iss(line);
        
        iss >> volType >> volMaterial >> volThickness;

        if (iss.fail()) {
            G4cerr << "Error reading line: " << line << G4endl;
            continue;
        }

        calorSizeZ += volThickness*mm;

        layerType.push_back(volType);
        layerMaterial.push_back(volMaterial);
        layerThickness.push_back(volThickness*mm);

    }
}

void DetectorConstruction::DefineMaterials() {
    G4NistManager* nist = G4NistManager::Instance();
    //Custom Materials:
    G4int ncomponents;

    G4double LYSO_density = 7.15*g/cm3;
    G4Material* LYSO= new G4Material("LYSO", LYSO_density, ncomponents=5);
    LYSO->AddElement(nist->FindOrBuildElement("Lu"),71*perCent);
    LYSO->AddElement(nist->FindOrBuildElement("Si"),6*perCent);
    LYSO->AddElement(nist->FindOrBuildElement("O"), 18*perCent);
    LYSO->AddElement(nist->FindOrBuildElement("Y"), 4*perCent);
    LYSO->AddElement(nist->FindOrBuildElement("Ce"),1*perCent);

    G4double YAG_density = 4.55*g/cm3;
    G4Material* YAG = new G4Material("YAG",YAG_density,ncomponents=4);
    YAG->AddElement(nist->FindOrBuildElement("Y"),44.92*perCent);
    YAG->AddElement(nist->FindOrBuildElement("Al"),22.72*perCent);
    YAG->AddElement(nist->FindOrBuildElement("O"),30*perCent);
    YAG->AddElement(nist->FindOrBuildElement("Ce"),2.36*perCent);

    G4double CSI_density = 4.51* g/cm3;
    G4Material* CSI = new G4Material("CsI",CSI_density,ncomponents=3);
    CSI->AddElement(nist->FindOrBuildElement("Cs"),50.12*perCent);
    CSI->AddElement(nist->FindOrBuildElement("I"), 48.81*perCent);
    CSI->AddElement(nist->FindOrBuildElement("Tl"),1.07*perCent);

}

void DetectorConstruction::ConstructCalorimeter(G4LogicalVolume* logicWorld) {

    // Set some visualization attributes:
    G4VisAttributes* calorVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //Calorimeter is blue
    calorVisAtt->SetVisibility(true);
    
    G4VisAttributes* filterVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Filters are red
    filterVisAtt->SetVisibility(true);    
    
    G4VisAttributes* detectorVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Detectors are green
    detectorVisAtt->SetVisibility(true);

    // Construct the Calorimeter
    G4NistManager *nist = G4NistManager::Instance();

    auto solidCalor = new G4Box("Calorimeter", calorSizeXY/2,calorSizeXY/2,calorSizeZ/2);
    auto logicCalor = new G4LogicalVolume(solidCalor,worldMaterial,"Calorimeter");
    //Assign the calorimeter volume to the logical volume. This makes some the logic easier to interpret in other classes. 
    calorVolume = logicCalor;
    logicCalor->SetVisAttributes(calorVisAtt);
    new G4PVPlacement(0,G4ThreeVector(0,0,calorSizeZ/2),logicCalor,"Calorimeter",logicWorld,false,0,false);

    // The initial position of the layers in the calorimeter.
    // The front face of calorimeter is at origin. 
    G4double z = -calorSizeZ/2;
    G4int j_filter = 0;
    G4int j_detector = 0;

    for (size_t i = 0; i < layerType.size(); ++i) {

        G4Material* layerMat = nist->FindOrBuildMaterial("G4_" + layerMaterial[i]);
        if (!layerMat) {layerMat = G4Material::GetMaterial(layerMaterial[i]);}

        if(layerType[i] == "Filter"){
            G4Box* solidFilter = new G4Box("Filter", calorSizeXY/2, calorSizeXY/2, layerThickness[i]/2);
            G4LogicalVolume* logicFilter = new G4LogicalVolume(solidFilter,layerMat,"logicFilter");
            logicFilter->SetVisAttributes(filterVisAtt);
            new G4PVPlacement(0,G4ThreeVector(0,0,z+layerThickness[i]/2),logicFilter,"Filter",logicCalor,false,j_filter,true);
            
            z += layerThickness[i];
            j_filter++;
        }

        if (layerType[i] == "Detector") {
            G4Box* solidDetector = new G4Box("Detector",calorSizeXY/2,calorSizeXY/2,layerThickness[i]/2);
            G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector,layerMat,"logicDetector");
            logicDetector->SetVisAttributes(detectorVisAtt);
            new G4PVPlacement(0,G4ThreeVector(0,0,z+layerThickness[i]/2),logicDetector,"Detector",logicCalor,false,j_detector,true);

            z += layerThickness[i];
            j_detector++;

            NbOfDetectors += 1;
        }
    }
}

void DetectorConstruction::PrintCalorParameters() {
    //Print out Calorimeter geometry information
    G4int nbLayers = layerType.size();
    G4cout << std::string(80, '-') << G4endl;
    G4cout << "---> Calorimeter is constructed" << G4endl;
    G4cout << "\t---> Number of Layers: " << nbLayers << G4endl;
    G4cout << "\t---> Number of Detectors: " << NbOfDetectors << G4endl;
    G4cout << "\t---> Total Thickness: " << calorSizeZ/mm << "mm" << G4endl;
    G4cout << "\t--->  Transverse Size: " << calorSizeXY/mm << "mm" << G4endl;
    G4cout << std::string(80, '-') << G4endl;
}

