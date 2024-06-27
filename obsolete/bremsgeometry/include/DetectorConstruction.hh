#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4Box;

const G4int kMaxModules = 10;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public: 
        DetectorConstruction();
        ~DetectorConstruction() override;

        G4VPhysicalVolume* Construct() override;
        void ConstructMaterials();

        G4LogicalVolume* GetDetectorVol() const {return fDetectorVol;}
        
        G4int GetNbOfModules() {return NbOfModules;}
        G4int GetNbOfLayers() {return NbOfLayers;}

    private:
        G4Material* detectorMat;
        G4double detectorZ = 0.;
        
        G4Material* filterMat[kMaxModules];
        G4double filterZ[kMaxModules];

        G4int NbOfLayers = 0;
        G4double LayerZ[kMaxModules];
        G4Material* layerMat = nullptr;
        
        G4int NbOfModules = 0;
        G4double ModuleZ[kMaxModules];
        G4Material* moduleMat = nullptr;

        G4Material* worldMat = nullptr;
        G4double worldSizeXY = 0.;
        G4double worldSizeZ = 0;

        G4double stackZ = 0.;
        G4double sizeXY = 0.;

        G4Box*              fSolidDetector = nullptr;
        G4LogicalVolume*    fDetectorVol = nullptr;
        G4VPhysicalVolume*  fPhysiDetector = nullptr;

        G4Box*              fSolidFilter[kMaxModules];
        G4LogicalVolume*    fLogicFilter[kMaxModules];
        G4VPhysicalVolume*  fPhysiFilter[kMaxModules];

        G4Box*              fSolidLayer[kMaxModules];
        G4LogicalVolume*    fLogicLayer[kMaxModules];
        G4VPhysicalVolume*  fPhysiLayer[kMaxModules];

        G4Box*              fSolidModule[kMaxModules];
        G4LogicalVolume*    fLogicModule[kMaxModules];
        G4VPhysicalVolume*  fPhysiModule[kMaxModules];

        G4Box*              fSolidWorld = nullptr;
        G4LogicalVolume*    fLogicWorld = nullptr;
        G4VPhysicalVolume*  fPhysiWorld = nullptr;

        G4Material*         defaultMat;
        G4double            init_location = 0.;

        G4VPhysicalVolume* ConstructFilterStack();
};

#endif