#ifndef CONVERTER_MESSENGER_HH
#define CONVERTER_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
// Converter Messenger defines some user controls over the converter
// foil. The user can add/remove it, and change its z distance. 
class ConverterMessenger : public G4UImessenger {
    public:
        ConverterMessenger(DetectorConstruction* DetectorConstruction);
        ~ConverterMessenger() = default;

        void SetNewValue(G4UIcommand* command,G4String newValue) override;

    private:
        DetectorConstruction* fDetector; //var hold pointer to detectorConstruction
        G4UIdirectory* fDirectory; // ui directory

        // Commands
        G4UIcmdWithoutParameter *fRemoveConverterCmd;
        G4UIcmdWithoutParameter *fAddConverterCmd;
        G4UIcmdWithADoubleAndUnit* fPositionCmd;
};

#endif