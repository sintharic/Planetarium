COMPILER := g++
CPPFLAGS := -O2 -std=c++17
OBJECTS := solsys.cpp

solsys: header.h solsys.cpp
	@echo " compiling solsys.exe ..."
	@$(COMPILER) $(CPPFLAGS) solsys.cpp -o solsys.exe