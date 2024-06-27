#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
{

    for (G4int i=0; i<=kMaxModules;++i){
        filterMat[i] = nullptr;
        filterZ[i] = 0.;
        LayerZ[i] = 0.;
        ModuleZ[i] = 0.;

        fSolidFilter[i]=nullptr;
        fLogicFilter[i]=nullptr;
        fPhysiFilter[i]=nullptr;

        fSolidLayer[i]=nullptr;
        fLogicLayer[i]=nullptr;
        fPhysiLayer[i]=nullptr;

        fSolidModule[i]=nullptr;
        fLogicModule[i]=nullptr;
        fPhysiModule[i]=nullptr;
    }

    sizeXY = 10.*cm;
    filterZ[1] = 2*mm;
    filterZ[2] = 4*mm;
    filterZ[3] = 6*mm;
    detectorZ = 0.5*mm;
    init_location = 3.*cm;

    NbOfModules = 3;
    NbOfLayers = 3;
    ConstructMaterials();
}

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    return ConstructFilterStack();
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

    auto vacuum = G4Material::GetMaterial("G4_Galactic");
    auto aluminum = G4Material::GetMaterial("G4_Al");
    auto scintillator = G4Material::GetMaterial("G4_POLYETHYLENE");

    defaultMat = vacuum;
    detectorMat = scintillator;
    filterMat[1] = aluminum;
    worldMat = defaultMat;
    layerMat = defaultMat;
    moduleMat = defaultMat;

    G4cout<<G4endl<< "Filter Stack Materials: " << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl; 
}

G4VPhysicalVolume* DetectorConstruction::ConstructFilterStack()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean(); 

    for (G4int iModule=1; iModule<=NbOfModules; iModule++){
        //Eg.) 3 Modules -> 3 Layer Thicknesses
        LayerZ[iModule] = filterZ[iModule] + detectorZ; 
        ModuleZ[iModule] = NbOfLayers * LayerZ[iModule]; G4cout<<ModuleZ[iModule]<<G4endl;
        stackZ += ModuleZ[iModule];
    }


    worldSizeXY = 1.2*sizeXY;
    worldSizeZ =  10*stackZ;

    fSolidWorld = new G4Box("World", 0.5*worldSizeXY,0.5*worldSizeXY,0.5*worldSizeZ); 

    fLogicWorld = new G4LogicalVolume(fSolidWorld, worldMat,"World");

    fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "World", 0, false, 0);
  
    //Detectors
    fSolidDetector = new G4Box("Detector",0.5*sizeXY,0.5*sizeXY,0.5*detectorZ);
    fDetectorVol = new G4LogicalVolume(fSolidDetector,detectorMat,"Detector");  

    //Filters
    for (G4int i=1;i<=NbOfModules;i++){
        fSolidFilter[i] = new G4Box("Filter",0.5*sizeXY, 0.5*sizeXY,0.5*filterZ[i]);
        fLogicFilter[i] = new G4LogicalVolume(fSolidFilter[i], detectorMat,"Filter");
    }
    // place filters and detectors in Layers
    for (G4int i=1;i<=NbOfModules;i++) {
        fSolidLayer[i] = new G4Box("Layer",0.5*sizeXY,0.5*sizeXY,0.5*LayerZ[i]);
        fLogicLayer[i] = new G4LogicalVolume(fSolidLayer[i],layerMat,"Layer");

        new G4PVPlacement(0,G4ThreeVector(0., 0., -0.5*LayerZ[i] + 0.5*filterZ[i]), fLogicFilter[i],"Filter",fLogicLayer[i],false,0);
        new G4PVPlacement(0,G4ThreeVector(0., 0., 0.5*LayerZ[i]-0.5*detectorZ), fDetectorVol,"Filter",fLogicLayer[i],false,i);
    }

    for (G4int i=1;i<=NbOfModules;i++) {
        fSolidModule[i] = new G4Box("Module", 0.5*sizeXY,0.5*sizeXY,0.5*ModuleZ[i]);
        fLogicModule[i] = new G4LogicalVolume(fSolidModule[i],moduleMat,"Module");
    }
    for (G4int i=1;i<=NbOfModules;i++) {
        new G4PVReplica("Layer",fLogicLayer[i],fLogicModule[i],kZAxis,NbOfLayers,LayerZ[i]);
    }
    G4double xcenter = init_location;
    for (G4int i=1;i<=NbOfModules;i++) {
        xcenter += 0.5*(ModuleZ[i] + ModuleZ[i-1]);
        new G4PVPlacement(0,G4ThreeVector(0.,0.,xcenter), fLogicModule[i],"Module",fLogicWorld,false,0);
    }
    for (G4int i=1;i<=NbOfModules;i++) {
        fLogicLayer[i]->SetVisAttributes (G4VisAttributes::GetInvisible());
        fLogicModule[i]->SetVisAttributes (G4VisAttributes::GetInvisible());
    }
    return fPhysiWorld;
}