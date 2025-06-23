#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction() = default;
        ~DetectorConstruction() override = default;
    
        G4VPhysicalVolume* Construct() override;

        G4LogicalVolume* GetBremsVolume() const {return fBremsVolume; }
        G4double GetTargetBackZ() const {return fTargetBackZ;} 
        void ConstructSDandField() override;

    private:
        G4double sizeXY = 50*mm;
        G4double sizeZ = 1000*um;
        G4LogicalVolume* fBremsVolume = nullptr;
        G4LogicalVolume* logicDetector = nullptr;
        G4double fTargetBackZ;
};
#endif