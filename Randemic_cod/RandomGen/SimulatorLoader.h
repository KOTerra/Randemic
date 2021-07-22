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
std::map<std::string, OmClass> loadToSimulare1();
std::map<std::string, Oras> loadToSimulare2();
void openFile();






