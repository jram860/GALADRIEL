#include <iostream>

#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "ConverterMessenger.hh"
#include "PhysicsList.hh"

int main(int argc,char** argv)
{
	G4long seed = std::time(nullptr);
	CLHEP::HepRandom::setTheSeed(3); // 3 for good luck

    G4UIExecutive* ui = nullptr;
    if (argc == 1){
        ui = new G4UIExecutive(argc,argv);
    }

    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

	DetectorConstruction *detector = new DetectorConstruction();
	runManager -> SetUserInitialization(detector);
	runManager -> SetUserInitialization(new PhysicsList());
	PrimaryGeneratorAction *primary = new PrimaryGeneratorAction();
	runManager -> SetUserInitialization(new ActionInitialization(detector));

	G4VisManager *visManager = new G4VisExecutive;
	visManager -> Initialize();
	runManager -> Initialize();

	auto converterMessenger = new ConverterMessenger(detector);


	// DetectorConstruction* detector = new DetectorConstruction;
 	// runManager->SetUserInitialization(detector);

  	// auto physicsList = new FTFP_BERT;
  	// physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  	// runManager->SetUserInitialization(physicsList);

  	// runManager->SetUserInitialization(new ActionInitialization(detector));
    
	// runManager->Initialize();
    // G4VisManager* visManager = new G4VisExecutive;
	// visManager->Initialize();

	// auto converterMessenger = new ConverterMessenger(detector);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
	runManager->GeometryHasBeenModified();
	// Run macro or start UI
	if (!ui) {
		// batch mode
		
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	else {
		// run visualization

		UImanager->ApplyCommand("/control/execute vis.mac");

		// use UI
		ui->SessionStart();
		delete ui;
	}
	

	// clean up
	delete visManager;
	delete runManager;


	return 0;
}