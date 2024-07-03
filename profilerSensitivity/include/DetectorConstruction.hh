#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include <vector>

class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    void SetFilterThicknesses(const G4String& thicknesses);
    void SetDetectorThicknesses(const G4String& thicknesses);
    void SetFilterMaterials(const G4String& materials);
    void SetDetectorMaterials(const G4String& materials);

    G4int GetNbOfDetectors() {return NbOfDetectors;}
    
private:
    std::vector<G4String> fFilterMaterials;
    std::vector<G4double> fFilterThicknesses;
    std::vector<G4String> fDetectorMaterials;
    std::vector<G4double> fDetectorThicknesses;
    G4VPhysicalVolume* ConstructCalorimeter();
    G4int NbOfDetectors;
    
    DetectorMessenger* fMessenger;
    void DefineMaterials();
};

#endif // DETECTORCONSTRUCTION_HH