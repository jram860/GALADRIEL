#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
{
    NbOfModules = 1;
    filter_thicknesses[3] = {3,4,2};

    ConstructMaterials();
}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;
    auto vacuum = G4Material::GetMaterial("G4_Galactic");
    auto aluminum = G4Material::GetMaterial("G4_Al");
    auto scintillator = G4Material::GetMaterial("G4_POLYETHYLENE");

    G4double sizeXY = 10.*cm;
    G4double filterZ = 20.*mm;
    G4double scintZ = 5*mm;
    G4double init_location = 3.*cm;

    G4double worldXY = 1.5*sizeXY;
    G4double worldZ = 5*(filterZ + scintZ);

    auto worldSolid = new G4Box("World", 0.5*worldXY,0.5*worldXY,0.5*worldZ);
    auto worldLogical = new G4LogicalVolume(worldSolid,vacuum,"World");
    auto worldPhysical = new G4PVPlacement(nullptr,G4ThreeVector(),worldLogical,"World",nullptr,false,0,checkOverlaps);

    G4ThreeVector zfilter = G4ThreeVector(0.,0.,init_location);
    auto filterSolid = new G4Box("Filter",0.5*sizeXY,0.5*sizeXY,0.5*filterZ);
    auto filterLogical = new G4LogicalVolume(filterSolid,aluminum,"Filter");
    new G4PVPlacement(nullptr,zfilter,filterLogical,"Filter", worldLogical,false,1,checkOverlaps);

    G4ThreeVector zscint = zfilter + G4ThreeVector(0.,0.,0.5*(filterZ + scintZ));
    auto scintSolid = new G4Box("Scintillator",0.5*sizeXY,0.5*sizeXY,0.5*scintZ);
    auto scintLogical = new G4LogicalVolume(scintSolid,scintillator, "Scintillator");
    new G4PVPlacement(nullptr,zscint,scintLogical,"Scintillator", worldLogical,false,1,checkOverlaps);

    fDetectorVol = scintLogical;
    return worldPhysical;
}

void DetectorConstruction::ConstructMaterials()
{
    auto nist = G4NistManager::Instance();

    // Vacuum
    nist->FindOrBuildMaterial("G4_Galactic");

    // Filter materials
    nist->FindOrBuildMaterial("G4_Al");

    // ScintMaterial (in future build add the Lyso construction)
    nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    G4cout<<G4endl<< "Filter Stack Materials: " << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

}