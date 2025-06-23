# Codebase for Geant4 simulations of beam profiler diagnostics at GALADRIEL

[!IMPORTANT] 

Some of interactive plotting and data processing is done through CERN ROOT, particularly histogram generation. Documentation and an installation guide may be found here: https://root.cern/.

If you don't want to use ROOT, you can change the data output type in the `RunAction` class.

### Contents
- Archive: Contains old, buggy scripts

- BremSpec: Find the forward secondary particle energy distribution off of a converter foil from an electrion pencil beam of known energy spectrum.

- ConverterFoilProfiler: Generate the spatial energy distribution in scintillating fiber arrays for the JBP Filter Pack experiment. There is a converter foil in front of the detector.

- SensitivityProfiler: Generate the Sensitivity curves for a profiler over a range of monoenergetic pencil beams.

[!TIP]
See each directory's `README` for specific user instructions
