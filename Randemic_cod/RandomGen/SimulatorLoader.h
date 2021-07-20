#pragma once
#include "Oras.h"
#include "OmClass.h"
#include <map>
#include <string>


class SimulatorLoader
{
private:
	
	std::map<std::string, OmClass> oameni;
	std::map<std::string, Oras> orase;
public:
	void loadToSimulare1();
	void loadToSimulare2();

	std::map<std::string, OmClass> getOameni() {
		return oameni;
	};
	std::map<std::string, Oras> getOrase() {
		return orase;
	};
};

