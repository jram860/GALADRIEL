#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include <vector>

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    G4int GetNbOfDetectors() {return NbOfDetectors;}
    
private:
    std::vector<G4Material*> filterMaterials;
    std::vector<G4double> filterThicknesses;
    std::vector<G4Material*> detectorMaterials;
    std::vector<G4double> detectorThicknesses;
    G4VPhysicalVolume* ConstructCalorimeter();
    G4int NbOfDetectors;
};

#endif // DETECTORCONSTRUCTION_HH