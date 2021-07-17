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


/*
				x,y mapa :941x684

				dimensiune cel mai mare oras: 170x110

				dimensiune casuta in matrice: 170x170

				matrice: 5x4

*/

int mat[6][5];
void initMatrice() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = 0;
		}
	}
}
int matL=170;


std::pair<int, int> pozitie() {
	int pixelX, pixelY;
	initMatrice();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (mat[i][j] != 1) {
				pixelX = matL * i;
				pixelY = matL * j;
				mat[i][j] = 1;

				return std::pair<int, int>(pixelX, pixelY);
			}
		}
	}
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
			populatieMaxima = populatiile[nrO-1];
		}

	}

	for (std::map<std::string, Oras>::iterator itr = elemente.begin(); itr != elemente.end(); itr++) {
		
		itr->second.setTexture(populatieMaxima);
		itr->second.shape.setSize(sf::Vector2f(itr->second.orasSprite.getTexture()->getSize()));
		std::pair<int, int> per=pozitie();
		itr->second.orasSprite.setPosition(sf::Vector2f(per.first,per.second));
		itr->second.shape.setPosition(sf::Vector2f(itr->second.orasSprite.getPosition()));

	}


	return elemente;
}