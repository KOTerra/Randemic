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
	//extern std::string fisierNume;
	extern bool fisierIncarcat;
}

//std::string openFile();
void loadToSimulare1();
void loadToSimulare2(std::map<std::string, Oras>& oraseSigureHead, std::map<std::string, Oras>& oraseInfectHead);

std::map<std::string, OmClass> getOameniSiguri();
std::map<std::string, OmClass> getOameniInfect();
std::map<std::string, OmClass> getOameniVindec();
std::map<std::string, OmClass> getOameniDeced();

std::map<std::string, Oras> getOraseSigure();
std::map<std::string, Oras> getOraseInfect();
std::map<std::string, Oras> getOraseVindec();

void resetOraseSigure();
void resetOraseInfect();



void openFile();

std::string getFisierNume(const std::string& fisierFolosit);





