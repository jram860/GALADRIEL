#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

#include <sstream>

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(),
  fFilterMaterials(),
  fDetectorMaterials(),
  fFilterThicknesses(),
  fDetectorThicknesses() {}
  
DetectorConstruction::~DetectorConstruction() {
    delete fMessenger;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();
    return ConstructCalorimeter();
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
    
    //G4cout << *(G4Material::GetMaterialTable()) << G4endl;

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

    G4double sizeXY = 50*mm; // transverse dimension

    //Converter Foil

    G4Material*kapton = nist->FindOrBuildMaterial("G4_KAPTON");
    G4Material*converterMat = nist->FindOrBuildMaterial("G4_Ta");
    G4double foil_thickness = 997*um;
    G4double kapton_thickness = 0.094*mm;

    G4Box*solidtape = new G4Box("Tape",sizeXY/2,sizeXY/2, kapton_thickness/2);
    G4LogicalVolume* logicTape = new G4LogicalVolume(solidtape,kapton,"Tape");
    new G4PVPlacement(0,G4ThreeVector(0,0,-kapton_thickness/2),logicTape,"Tape",logicWorld,false,0,true);

    G4Box* solidFoil = new G4Box("Foil", sizeXY/2,sizeXY/2,foil_thickness/2);
    G4LogicalVolume* logicFoil = new G4LogicalVolume(solidFoil,converterMat,"Foil");
    new G4PVPlacement(0,G4ThreeVector(0,0,foil_thickness/2),logicFoil,"Foil",logicWorld,false,0,true);

    // Calorimeter
    G4double posZ = 3*cm; // Initial Z position

    G4VisAttributes* detectorVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Green
    detectorVisAtt->SetVisibility(true);

    G4VisAttributes* filterVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red
    filterVisAtt->SetVisibility(true);

    NbOfDetectors = fFilterMaterials.size();
    G4cout << "### The stack is: " << fFilterMaterials.size() << " Layers" << G4endl;
    
    for(G4int i = 0; i < fFilterMaterials.size(); ++i)
    {
         // Filter
        G4Material* filter_mat = nist->FindOrBuildMaterial(fFilterMaterials[i]);
        G4Box* solidFilter = new G4Box("Filter", 0.5*sizeXY, 0.5*sizeXY, fFilterThicknesses[i]/2);
        G4LogicalVolume* logicFilter = new G4LogicalVolume(solidFilter, filter_mat, "Filter");
        logicFilter->SetVisAttributes(filterVisAtt);
        new G4PVPlacement(0, G4ThreeVector(0, 0, posZ + fFilterThicknesses[i]/2), logicFilter, "Filter", logicWorld, false, i, true);
        posZ += fFilterThicknesses[i];

        // Detector

        G4Material* detector_mat = nist->FindOrBuildMaterial(fDetectorMaterials[i]);
        if (!detector_mat) {
            G4Material* detector_mat = G4Material::GetMaterial(fDetectorMaterials[i]);
        }
        G4Box* solidDetector = new G4Box("Detector", 0.5*sizeXY, 0.5*sizeXY, fDetectorThicknesses[i]/2);
        G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, detector_mat, "Detector");
        logicDetector->SetVisAttributes(detectorVisAtt);
        new G4PVPlacement(0, G4ThreeVector(0, 0, posZ + fDetectorThicknesses[i]/2), logicDetector, "Detector", logicWorld, false, i, true);
        posZ += fDetectorThicknesses[i];
    }
    return physWorld;
}

void DetectorConstruction::SetFilterMaterials(const G4String& materials) {
    std::istringstream iss(materials);
    fFilterMaterials.clear();
    G4String material;
    while (iss >> material) {
        fFilterMaterials.push_back(material);
    }
}

void DetectorConstruction::SetDetectorMaterials(const G4String& materials) {
    std::istringstream iss(materials);
    fDetectorMaterials.clear();
    G4String material;
    while (iss >> material) {
        fDetectorMaterials.push_back(material);
    }
}

void DetectorConstruction::SetFilterThicknesses(const G4String& thicknesses) {
    std::istringstream iss(thicknesses);
    fFilterThicknesses.clear();
    G4double thickness;
    while (iss >> thickness) {
        fFilterThicknesses.push_back(thickness*mm);
    }
}

void DetectorConstruction::SetDetectorThicknesses(const G4String& thicknesses) {
    std::istringstream iss(thicknesses);
    fDetectorThicknesses.clear();
    G4double thickness;
    while (iss >> thickness) {
        fDetectorThicknesses.push_back(thickness*mm);
    }
}

