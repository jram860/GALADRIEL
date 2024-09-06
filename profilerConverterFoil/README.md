# Filter Stack Profiler Sensitivity with Converter Foil

This program simulates the energy deposition and lateral spatial energy deposition profiles in detector layers for a particle beam of flexible energy distribution and size. This simulation supports single-shot mode operation. To create a batch of energy deposition profiles, the sensitivityProfiler project is better suited.

To run, you must specify the (1) detector geometry and (2) run conditions. 

To create the program executable, named ```profiler```: create a build directory and run ```cmake ..``` to generate the buildsystem for the project, then run ```make``` to compile and add macro files to build directory [^1]. You can then run the program using ```./profiler```. Note that these instructions are for UNIX-based systems. 

The Geant4 native GUI and 3D Visualization is automatically initialized when executing ```./profiler```, and visualization settings can be set in the ```/build/vis.mac``` macro file. To run the program in batch-mode, execute the program with the target macro file. For example ```./profiler loop.mac``` will execute the contents of ```loop.mac```. The GUI and visualization is not executed in batch-mode operation.

The script will output the energy deposition profile per-layer to the terminal and create spatial profiles of the energy deposition as .root files.[^2]
### 1. Geometry

The filter stack is comprised of a series of filtering and detecting layers of varying thicknesses in the beam axis. In the ```/build/geomConfig.txt```[^3] file, follow the instructions at the top to change the layer-type, material, and beam-axis-thickness of each layer. The entries are whitespace-delimited.  Specify the layer type with the ```Filter``` and ```Detector``` keywords, scoring will only occur in Detector geometries. 

You can choose from any material in the native [Geant4 NIST Material catalog](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html) for any filter or detector. Omit the ```G4_``` prefix. Additionally, several custom materials have been created, which you can specify with the ```LYSO, YAG, CSI``` keywords. 

Additionally, a converting foil geometry is available for conversion of electron beams into x-rays. By default, a converter foil is placed 3 cm ahead of the front of of the filter stack, in the beam axis. 

Before running a particle beam: remove it with the command ```/converter/remove/```, add it back with ```/converter/add/``` or place a new one with the command ```/converter/setPosition <z> <units>```, where z is distance ahead of the filter stack in the beam (z) axis. 

### 2. Run Conditions

Unlike the sensitivityProfiler, converterFoilProfiler utilizes the G4GeneralParticleSource class for primary particle beam creation. An example of a histogram-specified beam energy distribution is given in ```spectrum.mac```, however a full description of available beam characteristics and necessary syntax is available in the [Geant4 documentation](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/GettingStarted/generalParticleSource.html?highlight=general%20particle%20source). 

[^1]: Make sure that all of files in the ```/scripts``` folder are included in the build directory.
[^2]: To view these, you must have CERN ROOT installed. Installation instruction can be found [here](https://root.cern/install/) 
[^3]: To apply any new changes, you must make sure they are in the build directory, save the file, and restart the program. 