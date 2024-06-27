#include <iostream>
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);

  auto physicsList = new FTFP_BERT;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization(detector));

  runManager->Initialize();

  G4UIExecutive* ui = new G4UIExecutive(argc,argv);
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  auto UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/execute vis.mac");

  ui->SessionStart();

  delete visManager;
  delete runManager;
    return 0;
}