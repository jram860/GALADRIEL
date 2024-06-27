#include "RunAction.hh"
#include <G4Run.hh>
#include <G4SystemOfUnits.hh>
#include <numeric>
#include <G4RunManager.hh>

RunAction::RunAction() : G4UserRunAction(), fTotalDoses(2, 0.0) {}
RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    std::fill(fTotalDoses.begin(), fTotalDoses.end(), 0.0);
}

void RunAction::EndOfRunAction(const G4Run*) {
    G4double totalDose = std::accumulate(fTotalDoses.begin(), fTotalDoses.end(), 0.0);

    G4cout << "Total Dose in Calorimeter: " << totalDose / joule << " J" << G4endl;
    for (size_t i = 0; i < fTotalDoses.size(); ++i) {
        G4cout << "Dose in detector " << i << ": " << fTotalDoses[i] / joule << " J" << G4endl;
    }
}

void RunAction::AddDose(G4int detectorID, G4double dose) {
    fTotalDoses[detectorID] += dose;
}

const std::vector<G4double>& RunAction::GetDoses() const {
    return fTotalDoses;
}