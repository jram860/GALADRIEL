#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include <vector>
#include "globals.hh"
class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization(DetectorConstruction*);
    virtual ~ActionInitialization();
    
    virtual void BuildForMaster() const;
    virtual void Build() const;
    
private:
    DetectorConstruction* fDetector;
};

#endif // ACTIONINITIALIZATION_HH