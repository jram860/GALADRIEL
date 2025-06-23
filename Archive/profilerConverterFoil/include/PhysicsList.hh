#ifndef PHYSICS_LIST_HH
#define PHYSICS_LIST_HH

#include "G4VModularPhysicsList.hh"

class PhysicsList : public G4VModularPhysicsList {
    public:
        PhysicsList();
        virtual ~PhysicsList();

        virtual void ConstructParticles();
        virtual void ConstructProcess();
};

#endif