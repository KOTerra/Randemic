#include <iostream>
#include <json/json.h>
#include <fstream>
#include <map>

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>

#include "OmClass.h"
#include "HeaderNpc.h"
#include "Oras.h"


std::string getNumeOras() {
	std::string nume;
	std::ifstream fisierIn("Date/numeOrase.json");
	Json::Reader reader;
	Json::Value val;
	reader.parse(fisierIn, val);
	const Json::Value& listaNume = val["Orase"];
	nume = listaNume[rand() % (listaNume.size())]["Nume"].asString();
	
	return nume;

}

long long getPopulatie(int nrO,int nrN) {
	long long populatie;
	
	long long populatieInitiala = nrN / nrO;
	nrN -= populatie;
	nrO--;

	return populatie;
}


std::map<std::string, Oras> generareOrase(int nrO, int nrN) {
	std::map<std::string, Oras> elemente;


	for (int i = 0; i < nrO; i++) {
	
		//Oras oras(getNume(),);
		std::string id;



		//elemente.insert(std::pair<std::string, Oras>(id, oras));
	}


	return elemente;
}