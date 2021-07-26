#pragma once
#include "Oras.h"
#include "OmClass.h"
#include <map>
#include <string>
#include <cstddef> 

#include <Windows.h>
#include <commdlg.h>




namespace fisier {
	extern std::string fisierFolosit;
	
	extern bool fisierIncarcat;
}


void loadToSimulare1(std::map<std::string, OmClass>& oameniSanatosiHead, std::map<std::string, OmClass>& oameniInfectatiHead, std::map<std::string, OmClass>& oameniVindecatiHead, std::map<std::string, OmClass>& oameniDecedatiHead);
void loadToSimulare2(std::map<std::string, Oras>& oraseSigureHead, std::map<std::string, Oras>& oraseInfectHead);



void openFile();

std::string getFisierNume(const std::string& fisierFolosit);





