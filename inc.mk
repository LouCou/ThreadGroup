# This file is included by all the Makefiles of this repository.

# Uncomment to use g++
COMPILER = g++ -Wall -pedantic -Wfatal-errors -fdiagnostics-color -std=c++1y -O2
LIBS = -lpthread

# Uncomment to use clang
#COMPILER = clang++ -pedantic -Wall -Wfatal-errors -fdiagnostics-color -std=c++1y -O2
#LIBS = -lpthread

