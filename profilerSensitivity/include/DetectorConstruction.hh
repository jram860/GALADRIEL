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
    G4double GetCalorSizeZ() const {return calorSizeZ;}
    G4LogicalVolume* GetCalorVolume() const {return calorVolume; }

    
private:
    void ReadGeometryFile(const std::string& fileName);
    void ConstructCalorimeter(G4LogicalVolume* logicalWorld);
    void DefineMaterials();
    void PrintCalorParameters();

    G4int NbOfDetectors =0;

    G4LogicalVolume* calorVolume = nullptr;
    G4double calorSizeXY = 10*cm;
    G4double calorSizeZ = 0;
    G4double worldSizeZ;
    G4Material* worldMaterial;


    G4String volType;
    G4String volMaterial;
    G4double volThickness;
    std::vector<G4String> layerType;
    std::vector<G4String> layerMaterial;
    std::vector<G4double> layerThickness;
};

#endif // DETECTORCONSTRUCTION_HH