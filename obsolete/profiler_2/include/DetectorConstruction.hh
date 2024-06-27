#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <vector>
#include <G4LogicalVolume.hh>

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

    const std::vector<G4LogicalVolume*>& GetDetectorVolumes() const { return fDetectorVolumes; }

private:
    std::vector<G4LogicalVolume*> fDetectorVolumes;
};

#endif
