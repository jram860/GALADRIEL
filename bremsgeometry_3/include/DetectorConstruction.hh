#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include <vector>
#include <string>

struct Layer {
    std::string type;
    std::string material;
    double thickness;
};

class DetectorConstruction : public G4VUserDetectorConstruction {
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct();

    private:
        std::vector<Layer> ReadConfig(const std::string& filename);
        void ConstructProfiler(const std::vector<Layer>& layers, G4LogicalVolume* logicWorld);
};

#endif