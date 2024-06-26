#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
{
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

    fDetectorVol = filterLogical;
    return worldPhysical;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;
    //Generate materials
    auto vacuum = G4Material::GetMaterial("G4_Galactic"); 
    //generate filter materials:
    auto aluminum = G4Material::GetMaterial("G4_Al");
    //generate detector materials
    auto fiberArrays = G4Material::GetMaterial("G4_POLYETHYLENE");

    //place each material in order
    filterMat = aluminum;
    detectorMat = fiberArrays;

    G4double detectorThicknesses[]= {2.,2.,2.};
    G4double filterThicknesses[] = {2.,4.,6.};

    double init_pos = 5.*cm;
    
    size_t filterSize = sizeof(filterThicknesses)/sizeof(filterThicknesses[0]);
    size_t detectorSize = sizeof(detectorThicknesses)/sizeof(detectorThicknesses[0]);

    size_t NbOfLayers = detectorSize;

    double midpoint[2*NbOfLayers];

    double finalPos = stackPlacements(detectorThicknesses,detectorSize,filterThicknesses,filterSize,init_pos,midpoint,midposSize);
    //These parameters are constant for the geometry
    G4double sizeXY = 50.*mm;
    G4double init_loc = 3.*cm;
    G4double worldXY = 1.5*sizeXY;
    G4double worldZ = 1.5 * finalPos;
    
    // create wolrd geometry
    auto worldSolid = new G4Box("World", 0.5*worldXY,0.5*worldXY,0.5*worldZ);
    auto worldLogical = new G4LogicalVolume(worldSolid,vacuum,"World");
    auto worldPhysical = new G4PVPlacement(nullptr,G4ThreeVector(),worldLogical,"World",nullptr,false,0,checkOverlaps);

    //create detector geometry
    auto detectorSolid[i] = new G4Box("Detector", 0.5*sizeXY, 0.5*sizeXY,0.5*detectorThicknesses[i]);
    auto detectorLogical[i] = new G4LogicalVolume(detectorSolid[i],detectorMat,)

    





    
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

    G4cout<<G4endl<< "Filter Stack Material Choices: " << G4endl;
    G4cout<< "-----------------------------------" << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
    G4cout<< "-----------------------------------" << G4endl;

}

double stackPlacements(const double* detectorThicknesses, size_t detectorSize, const double* filterThicknesses, size_t filterSize, double init_pos,double* midpoint,size_t& midposSize){
    double currentPos = init_pos;
    midposSize = 0;
    size_t maxSize = (detectorSize >=filterSize) ? detectorSize : filterSize; //this is just for robustness in case of user input error.

    for (size_t i =0; i<maxSize; ++i) {
        if (i < filterSize) {
            double filterPos = currentPos + 0.5*filterThicknesses[i];
            midpoint[midposSize++] = filterPos;
            currentPos += filterThicknesses[i];
        }

        if (i < detectorSize) {
            double detectorPos = currentPos + 0.5*detectorThicknesses[i];
            midpoint[midposSize++] = detectorPos;
            currentPos += detectorThicknesses[i];
        }
        
    }

    return currentPos;
}