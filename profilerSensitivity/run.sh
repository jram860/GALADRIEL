#!/bin/bash

echo "Energy Scan beginning..."

echo "Looping over energies 10 keV to 1 MeV in steps of 10 keV"

cd build
./profiler loop.mac
# python3 plotter.py
