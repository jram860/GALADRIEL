#ifndef ActionInitialization_hh
#define ActionInitialization_hh

#include "G4VUserActionInitialization.hh"
class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
    public:
        ActionInitialization(DetectorConstruction*); 
        ~ActionInitialization() override;

        void BuildForMaster() const override;
        void Build() const override;

    private:
        DetectorConstruction* fDetector;
};

#endif