#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"

class SensitiveDetector : public G4VSensitiveDetector {
    public:
        SensitiveDetector(const G4String& name);
        ~SensitiveDetector() override = default;

        G4bool ProcessHits(G4Step* step, G4TouchableHistory *history) override;
};

#endif