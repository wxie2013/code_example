# PYTHIA configuration file.
# Generated on Fri Feb 18 11:04:54 EST 2022 with the user supplied options:
# --prefix=/home/py8_evtgen_HepMC

# Install directory prefixes.
PREFIX_BIN=/home/py8_evtgen_HepMC/bin
PREFIX_INCLUDE=/home/py8_evtgen_HepMC/include
PREFIX_LIB=/home/py8_evtgen_HepMC/lib
PREFIX_SHARE=/home/py8_evtgen_HepMC/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
CXX=g++
CXX_COMMON=-O2 -std=c++11 -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname,
LIB_SUFFIX=.so
OBJ_COMMON=

EVTGEN_USE=true
py8_evtgen_HepMC_dir=/home/py8_evtgen_HepMC
EVTGEN_CONFIG= 
EVTGEN_BIN=$(py8_evtgen_HepMC_dir)/bin
EVTGEN_INCLUDE=-I$(py8_evtgen_HepMC_dir)/include/EvtGen
EVTGEN_LIB= -lEvtGenExternal -lEvtGen
#EVTGEN_LIB=$(wildcard $(py8_evtgen_HepMC_dir)/lib/*)

HEPMC2_USE=true
HEPMC2_CONFIG=
HEPMC2_BIN=/home/py8_evtgen_HepMC/bin
HEPMC2_INCLUDE=/home/py8_evtgen_HepMC/include/HepMC3
HEPMC2_LIB=/home/py8_evtgen_HepMC/lib

