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
    ~DetectorConstruction() override = default;
    virtual G4VPhysicalVolume* Construct() override;

    G4int GetNbOfDetectors() {return NbOfDetectors;}
    G4double GetCalorSize() const {return calorSizeZ;}
    G4LogicalVolume* GetCalorVolume() const {return calorVolume;}

    // for detectormessenger
    void AddConverter();
    void RemoveConverter();
    void SetConverterPosition(G4double z);
    
private:
    // world parameters
    G4LogicalVolume* logicWorld;
    G4double worldSizeZ;
    G4Material* worldMaterial;

    void ReadGeometryFile(const std::string& fileName);
    void ConstructConverter(G4LogicalVolume* logicWorld);
    void ConstructCalorimeter(G4LogicalVolume* logicalWorld);
    void DefineMaterials();
    void PrintCalorParameters();

    G4int NbOfDetectors =0;
    // Calorimeter parameters
    G4LogicalVolume* calorVolume = nullptr;
    G4double calorSizeXY = 10*cm;
    G4double calorSizeZ = 0;

    // Converter Foil Parameters
    G4VPhysicalVolume *fConverterVol = nullptr;
    G4double foilSizeZ = 997*um;
    G4double tapeSizeZ = 0.094*mm;
    G4double convPosZ  = 3*cm;

    G4String volType;
    G4String volMaterial;
    G4double volThickness;
    std::vector<G4String> layerType;
    std::vector<G4String> layerMaterial;
    std::vector<G4double> layerThickness;
};

#endif // DETECTORCONSTRUCTION_HH