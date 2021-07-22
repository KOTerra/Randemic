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

using namespace std;

string getSex(bool sexbool) {
	//functie pentru sex 
	string sex;
	if (sexbool == true) {
		sex = "M";
	}
	else {
		sex = "F";
	}
	return sex;
}

string getNextPrenume(bool sexbool, string prenPrec) {
	//functie de prenume
	string prenume;
	if (sexbool == true) {
		//citim datele din baza de date a prenumelor si luam un prenume aleator
		ifstream fisierIn("Date/prenumeM.json");
		Json::Reader reader;
		Json::Value val;
		reader.parse(fisierIn, val);
		const Json::Value& listaPrenume = val["listaPrenumeM"];
		prenume = listaPrenume[rand() % (listaPrenume.size())]["M"].asString();
		fisierIn.close();
	}
	else {
		//citim datele din baza de date a prenumelor si luam un prenume aleator
		ifstream fisierIn("Date/prenumeF.json");
		Json::Reader reader;
		Json::Value val;
		reader.parse(fisierIn, val);
		const Json::Value& listaPrenume = val["listaPrenumeF"];
		prenume = listaPrenume[rand() % (listaPrenume.size())]["F"].asString();
		fisierIn.close();

	}
	if (prenPrec.find(prenume) != std::string::npos) {
		return getNextPrenume(sexbool, prenPrec);
	}
	return prenume;
}

string getPrenume(bool sexbool) {
	//formez prenumele 
	string prenume;
	prenume = getNextPrenume(sexbool, prenume);
	int probabilitate = rand() % 100;
	if (probabilitate < 40) {

		prenume = prenume + "-" + getNextPrenume(sexbool, prenume);
		if (probabilitate < 10) {

			prenume = prenume + "-" + getNextPrenume(sexbool, prenume);

		}

	}

	return prenume;
}

void getNume(string prenume) {
	//inca nefolosita
}

int getVarsta() {
	//functie de varsta care depinde
	int probabilitate = rand() % 101;
	int varsta = rand() % 15;
	if (probabilitate == 0) {
		return  420;
	}
	if (probabilitate < 12) {
		return varsta;
	}
	if (probabilitate < 33) {
		return varsta + 15;
	}
	if (probabilitate < 45) {
		return  varsta % 10 + 30;
	}
	if (probabilitate < 69) {
		return varsta + 40;
	}
	if (probabilitate < 86) {
		return varsta + 55;
	}
	if (probabilitate < 95) {
		return varsta + 70;
	}
	if (probabilitate <= 100) {
		return varsta + 85;
	}

}

string getInaltime(int varsta, bool sexbool) {
	//inaltime in functie de sex si desigur de varsta individului
	int inaltime = 0;
	int mod;
	if (varsta < 26) {
		switch (varsta) {
		case 0: {
			inaltime = 50;
			break;
		}
		case 1: {
			inaltime = 65;
			break;
		}

			  //de aici difera inaltimile


		case 2: {
			inaltime = 90;
			mod = rand() % 10 - 5;
			inaltime += mod;
			//mod 5
			break;
		}
		case 3: {
			inaltime = 98;
			mod = rand() % 12 - 6;
			inaltime += mod;
			//mod 6
			break;
		}
		case 4: {
			inaltime = 103;
			mod = rand() % 14 - 7;
			inaltime += mod;
			//mod 7
			break;
		}
		case 5: {
			inaltime = 110;
			mod = rand() % 16 - 8;
			inaltime += mod;
			//mod 8
			break;
		}
		case 6: {
			inaltime = 117;
			mod = rand() % 18 - 9;
			inaltime += mod;
			//mod 9
			break;
		}
		case 7: {
			inaltime = 123;
			mod = rand() % 20 - 10;
			inaltime += mod;
			//mod 10
			break;
		}
		case 8: {
			inaltime = 127;
			mod = rand() % 22 - 11;
			inaltime += mod;
			//mod 11
			break;
		}
		case 9: {
			inaltime = 134;
			mod = rand() % 22 - 11;
			inaltime += mod;
			//mod 11
			break;
		}
		case 10: {
			inaltime = 140;
			mod = rand() % 24 - 12;
			inaltime += mod;
			//mod 12
			break;
		}
		case 11: {
			inaltime = 148;
			mod = rand() % 24 - 12;
			inaltime += mod;
			//mod 12
			break;
		}

			   //difera in fct de sex de aici ca incep sa creasca fetele fir ar ele de frumoase//

		case 12: {
			if (sexbool) {
				inaltime = 154;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 152;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			break;

			//mod b12
			//mod f12
		}
		case 13: {
			if (sexbool) {
				inaltime = 160;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 158;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		case 14: {
			if (sexbool) {
				inaltime = 168;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 161;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		case 15: {
			if (sexbool) {
				inaltime = 170;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 162;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		case 16: {
			if (sexbool) {
				inaltime = 174;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 164;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
			   //pana aici se opresc fetele au crescut destul//

		case 17: {
			if (sexbool) {
				inaltime = 177;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 164;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		case 18: {
			if (sexbool) {
				inaltime = 180;
				mod = rand() % 24 - 12;
				inaltime += mod;
			}
			else {
				inaltime = 166;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		default: {
			if (sexbool) {
				inaltime = 181;
				mod = rand() % 24 - 12;
				inaltime += mod;

			}
			else {
				inaltime = 166;
				mod = rand() % 20 - 10;
				inaltime += mod;
			}
			break;
		}
		}
	}

	//de aici mergem din 15 in 15 ca omu ramane scund dupa 20 years
	else {
		if (sexbool) {
			inaltime = 179;
			mod = rand() % 24 - 12;
			inaltime += mod;

		}
		else {
			inaltime = 164;
			mod = rand() % 20 - 10;
			inaltime += mod;
		}

		int v = varsta;
		while (v % 15 == 0) {
			inaltime -= 4;
			v /= 15;
		}

	}






	return to_string(inaltime);
}

string getSociabilitate(int inaltime, int varsta) {
	//sociabilitatea persoanei
	//cat de probabil e sa se bage in seama cu lumea
	int social = inaltime / 60;
	if (varsta < 50 && varsta>25) {
		social += 1;
	}
	else {
		social += 2;
	}
	social += rand() % 8 - 2;


	return to_string(social);
}




std::map<string, OmClass> simulare(int NrNpc) {
	
	//aici sunt efectiv simulati oamenii
	std::map<string, OmClass> elemente;//un map cu keyurile oamenilor(la fel ca in data.json)
	srand(time(0));



	fstream fileData;
	fileData.open("Date/data.json", 'W');
	fileData << "{" << '\n' <<
		"\"listaNPC\": [" << '\n';

	for (int i = 0; i < NrNpc; i++) {

		OmClass om;
		string id;
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

		//elemente.insert(Npc.ID);

		//sex
		bool sexbool = rand() % 2;
		string sex = getSex(sexbool);
		om.sex = sex;
		//sex

		//prenume
		string prenume = getPrenume(sexbool);
		om.prenume = prenume;
		//prenume

		//Nume

		//Nume


		//varsta
		string varsta = to_string(getVarsta());
		om.varsta = varsta;
		om.varsta = varsta;
		//varsta


		//inaltime
		string inaltime = getInaltime(stoi(varsta), sexbool);
		om.inaltime = inaltime;
		//inaltime


		//social
		string sociabilitate = getSociabilitate(stoi(inaltime), stoi(varsta));
		om.sociabilitate = sociabilitate;
		//social

		//creez oameni
		om.pX = rand() % 900 + 38;
		om.pY = rand() % 645 + 38;

		sf::CircleShape circle;
		om.shape = circle;

		//cum arata omul
		om.shape.setRadius(razaShape);
		om.shape.setOutlineColor(sf::Color(0, 0, 0));
		om.shape.setFillColor(sf::Color(100, 255, 0));
		om.shape.setOutlineThickness(1);
		om.shape.setPosition(om.pX, om.pY);
		om.misc.x = speed;
		om.misc.y = speed;

		int rand1 = rand() % 2;
		if (rand1 == 0) {
			om.misc.x = -om.misc.x;
		}
		int rand2 = rand() % 2;
		if (rand2 == 0) {
			om.misc.y = -om.misc.y;
		}
		om.shape.setRotation(rand() % 90);

		om.stare = "sanatos";
		elemente.insert(pair<string, OmClass>(id, om));
		//
				///std::cout << Npc.ID << " " << sex << " " << prenume << " " << varsta << " " << inaltime << '\n';
		//
				//
				/////scrie in json oamenii de mai sus 
				//
		string str;
		Json::FastWriter writer;
		Json::Value element;
		element["ID"] = id;
		element["sex"] = sex;
		element["prenume"] = prenume;
		element["varsta"] = varsta;
		element["inaltime"] = inaltime;
		element["sociabilitate"] = sociabilitate;
		str = writer.write(element);
		fileData << endl << str;
		if (i != NrNpc - 1) {
			fileData << ",";
		}

	}
	fileData << "]" << '\n' << "}";
	fileData.close();
	//
	/////scrie in json 
	//

	return elemente;
}