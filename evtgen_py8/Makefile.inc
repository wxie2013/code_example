# PYTHIA configuration file.
# Generated on Fri Feb 18 11:04:54 EST 2022 with the user supplied options:
# --prefix=/home/py8_evtgen_HepMC

# Install directory prefixes.
PY_BASE = /home/wxie/py8_evtgen_HepMC
PREFIX_BIN=$(PY_BASE)/bin
PREFIX_INCLUDE=$(PY_BASE)/include
PREFIX_LIB=$(PY_BASE)/lib
PREFIX_SHARE=$(PY_BASE)/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
CXX=g++
CXX_COMMON=-O2 -std=c++11 -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname,
LIB_SUFFIX=.so
OBJ_COMMON=

EVTGEN_USE=true
EVTGEN_CONFIG= 
EVTGEN_BIN=$(PY_BASE)/bin
EVTGEN_INCLUDE=-I$(PY_BASE)/include/EvtGen
EVTGEN_LIB= -L$(PY_BASE)/lib64 -lEvtGenExternal -lEvtGen
