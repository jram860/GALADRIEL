# Filter Stack Profiler Sensitivity

This program simulates the energy deposition in detector layers of monoenergetic particle beams. To run, you must specify the (1) detector geometry, (2) Run Conditions, and (3) Looping conditions.

To create the program executable, named ```profiler```: create a build directory and run ```cmake ..``` to generate the buildsystem for the project, then run ```make``` to compile and add macro files to build directory [^1]. You can then run the program using ```./profiler```. Note that these instructions are for UNIX-based systems. 

The Geant4 native GUI and 3D Visualization is automatically initialized when executing ```./profiler```, and visualization settings can be set in the ```/build/vis.mac``` macro file. To run the program in batch-mode, execute the program with the target macro file. For example ```./profiler loop.mac``` will execute the contents of ```loop.mac```. The GUI and visualization is not executed in batch-mode operation.

### 1. Geometry

The filter stack is comprised of a series of filtering and detecting layers of varying thicknesses in the beam axis. In the ```/build/geomConfig.txt```[^2] file, follow the instructions at the top to change the layer-type, material, and beam-axis-thickness of each layer. The entries are whitespace-delimited.  Specify the layer type with the ```Filter``` and ```Detector``` keywords, scoring will only occur in Detector geometries. 

You can choose from any material in the native [Geant4 NIST Material catalog](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html) for any filter or detector. Omit the ```G4_``` prefix. Additionally, several custom materials have been created, which you can specify with the ```LYSO, YAG, CSI``` keywords. 

### 2. Run Conditions

Specify the particle type, energy, and number of particles in the ```/build/run.mac```[^2] file as follows, using the ```/gun/particle, /gun/energy/, /run/beamOn``` macro commands. For example, 
```
/gun/particle e-
/gun/energy 5 keV
/run/beamOn 10
```

will run a beam of 10 electrons each at 5 keV, executing ```./profiler run.mac```. See the Geant4 Documentation for a comprehensive overview of particle simulation capabilities. 

### 3. Looping Conditions

It is also possible to loop over a range of beam energies in a for or foreach loop. In the ```/build/loop.mac```[^2] file, follow the syntax instructions to set the loop parameters, and specify a loop variable. 

Then in the ```/build/run.mac``` set the beam energy to ```/gun/energy {ind} Ene```, where ```ind``` is the loop variable, and ```Ene``` is the unit of energy. For example

```
/gun/particle gamma
/gun/energy {Ekin} keV
/run/beamOn 10
```
will for each run initialize a photon beam of 10 photons of energies 'Ekin', specified in the ```loop.mac``` loop control and executed with ```./profiler loop.mac```.

[^1]: An example post-processing script in python is included for reference. 
[^2]: To apply any new changes, you must make sure they are in the build directory, save the file, and restart the program. 

---

