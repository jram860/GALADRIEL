#ifndef DETECTOR_MESSENGER_HH
#define DETECTOR_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "DetectorConstruction.hh" 
class DetectorConstruction;

class DetectorMessenger : public G4UImessenger {
    public:
        DetectorMessenger(DetectorConstruction* det);
        ~DetectorMessenger();

        void SetNewValue(G4UIcommand* command, G4String newValues);

    private:
        G4UIdirectory* fDirectory;
        DetectorConstruction* fDetector;

        G4UIcmdWithAString* fFilterMaterialsCmd;
        G4UIcmdWithAString* fDetectorMaterialsCmd;
        G4UIcmdWithADoubleAndUnit* fFilterThicknessesCmd;
        G4UIcmdWithADoubleAndUnit* fDetectorThicknessesCmd; 


};

#endif // DETECTOR_MESSENGER_HH