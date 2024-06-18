#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

const G4int kMaxDetector = 10;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public: 
        DetectorConstruction();
        ~DetectorConstruction() override;

        G4VPhysicalVolume* Construct() override;
        void ConstructMaterials();

        G4LogicalVolume* GetDetectorVol() const {return fDetectorVol;}
        
        G4int GetNbOfLayers() {return NbOfLayers;}

    private:
        G4LogicalVolume* fDetectorVol = nullptr;
        G4int NbOfLayers;
};

#endif