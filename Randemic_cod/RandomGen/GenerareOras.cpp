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

long long getPopulatia(int nrO, int nrN) {

	long long populatieInitiala = nrN / nrO;
	long long populatie = 0;
	long long limitaInf = nrO / 100;
	int coef = rand() % 3 + 1;
	int mod = rand() % 2000 - 1000;
	populatie = populatieInitiala + (rand() % (coef * populatieInitiala+1) / 2 - (populatieInitiala / coef)) + mod;
	if (populatie < limitaInf) {
		populatie = limitaInf;
	}

	return populatie;
}

long long populatiile[101];

std::map<std::string, Oras> generareOrase(int nrO, int nrN) {
	std::map<std::string, Oras> elemente;
	long long populatieMaxima;

	for (int i = 1; i <= nrO; i++) {

		Oras oras(getNumeOras(), getPopulatia(nrO, nrN), 0, 0);
		populatiile[i] = oras.getPopulatie();

		std::string id;
		//ID
		if (i < 10) {
			int j = i;
			id = "c0x00" + std::to_string(j);
		}
		else if (i >= 10 && i < 100) {
			int j = i;
			id = "c0x0" + std::to_string(j);
		}
		else {
			int j = i;
			id = "c0x" + std::to_string(j);
		}
		//ID


		elemente.insert(std::pair<std::string, Oras>(id, oras));
		if (i == nrO) {
			oras.sortarePopulatie(populatiile, nrO);
			populatieMaxima = populatiile[nrO];
		}

	}

	for (std::map<std::string, Oras>::iterator itr = elemente.begin(); itr != elemente.end(); itr++) {
		Oras oras = itr->second;
		oras.setTexture(populatieMaxima);
		oras.shape.setSize(sf::Vector2f(oras.orasSprite.getTexture()->getSize()));
		oras.shape.setPosition(sf::Vector2f(oras.orasSprite.getPosition()));

	}


	return elemente;
}