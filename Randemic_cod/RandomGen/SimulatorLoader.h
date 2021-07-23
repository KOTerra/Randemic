#pragma once
#include "Oras.h"
#include "OmClass.h"
#include <map>
#include <string>

#include <Windows.h>
#include <commdlg.h>




namespace fisier {
	extern std::string fisierFolosit;
	extern bool fisierIncarcat;
}

//std::string openFile();
void loadToSimulare1();
std::map<std::string, Oras> loadToSimulare2();

std::map<std::string, OmClass> getOameniSiguri();
std::map<std::string, OmClass> getOameniInfect();
std::map<std::string, OmClass> getOameniVindec();
std::map<std::string, OmClass> getOameniDeced();
void openFile();






