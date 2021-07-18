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
	const Json::Value& listaNume = val["Nume"];
	nume = listaNume[rand() % (listaNume.size())]["Orase"].asString();

	fisierIn.close();
	return nume;

}
std::string setTextura(Oras& oras, long long populatieMaxima) {

	sf::Texture texture;
	std::string texturaMia;

	if (oras.getPopulatie() <= populatieMaxima / 4) {
		texturaMia = "Sprites/oras1.png";
	}
	else if (oras.getPopulatie() > populatieMaxima / 4 && oras.getPopulatie() <= populatieMaxima / 2) {

		texturaMia = "Sprites/oras2.png";
	}
	else if (oras.getPopulatie() > populatieMaxima / 2 && oras.getPopulatie() <= ((3 * populatieMaxima) / 4)) {

		texturaMia = "Sprites/oras3.png";
	}
	else {

		texturaMia = "Sprites/oras4.png";
	}

	return texturaMia;

}

long long getPopulatia(int nrO, int nrN) {

	long long populatieInitiala = nrN / nrO;
	long long populatie = 0;
	long long limitaInf = nrO / 100;
	int coef = rand() % 3 + 1;
	int mod = 0;
	populatie = populatieInitiala + (rand() % (coef * populatieInitiala+1) / 2 - (populatieInitiala / coef))+mod;
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
const int matL=182;


std::pair<int, int> pozitie() {
	int pixelX, pixelY;
	srand(time(0));
	int ir = rand() % 5;
	int jr = rand() % 4;
	if (mat[ir][jr] != 1) {
		pixelX = matL * ir;
		pixelY = matL * jr;
		mat[ir][jr] = 1;
		return std::pair<int, int>(pixelX + 25, pixelY + 25);
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 4; j++) {
				if (mat[i][j] != 1) {
					pixelX = matL * i;
					pixelY = matL * j;
					mat[i][j] = 1;

					return std::pair<int, int>(pixelX + 25, pixelY + 25);
				}
			}
		}
	}
}
int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

long long populatiile[101];

std::map<std::string, Oras> generareOrase(int nrO, int nrN) {
	std::map<std::string, Oras> elemente;
	long long populatieMaxima=nrN;
	long long nrOcop = nrO, nrNcop = nrN;
	long long suma = 0;
	initMatrice(); 
	
	int i=0;
	while(i<nrO*nrOcop){
		
		populatiile[i] = getPopulatia(nrO,nrN);
		Oras oras(getNumeOras() , populatiile[i], 0, 0);
		long long pop = populatiile[i];
		suma += pop;
		nrN -= pop;
		nrO--;

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
		i++;
	}
	i++;
	long long ultima = nrNcop - suma;
	populatiile[i] = ultima;
	qsort(populatiile, i, sizeof(int),compare);
	populatieMaxima = populatiile[i];
	Oras oras(getNumeOras(), populatiile[i], 0, 0);
	std::string id="";
	elemente.insert(std::pair<std::string, Oras>(id, oras));

	

	for (std::map<std::string, Oras>::iterator itr = elemente.begin(); itr != elemente.end(); itr++) {
		
		
		itr->second.textura.loadFromFile(setTextura(itr->second,populatieMaxima));
		itr->second.orasSprite.setTexture(itr->second.textura);
		int marimeY = itr->second.orasSprite.getTextureRect().height;
		int marimeX = itr->second.orasSprite.getTextureRect().width;
		itr->second.shape.setSize(sf::Vector2f(marimeX, marimeY));
		itr->second.shape.setFillColor(sf::Color(0, 255, 0));
		std::pair<int, int> per=pozitie();
		itr->second.orasSprite.setPosition(sf::Vector2f(per.first,per.second));
		itr->second.shape.setPosition(sf::Vector2f(itr->second.orasSprite.getPosition()));
		itr->second.pX = per.first;
		itr->second.pY = per.second;
		
	}


	return elemente;
}