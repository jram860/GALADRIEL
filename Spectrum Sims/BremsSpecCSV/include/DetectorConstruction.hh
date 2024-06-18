#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction() = default;
        ~DetectorConstruction() override = default;
    
        G4VPhysicalVolume* Construct() override;

        G4LogicalVolume* GetBremsVolume() const {return fBremsVolume; }

    private:
        G4LogicalVolume* fBremsVolume = nullptr;
};
#endif