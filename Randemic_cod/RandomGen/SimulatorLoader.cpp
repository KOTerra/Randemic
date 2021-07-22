#include "SimulatorLoader.h"
#include <json/json.h>
#include <fstream>


#include <Windows.h>
#include <commdlg.h>

std::string fisier::fisierFolosit = "";
bool fisier::fisierIncarcat = false;

std::string openFile()
{
	
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	CHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	if (GetCurrentDirectoryA(256, currentDir)) {
		ofn.lpstrInitialDir = currentDir;
	}

	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == true) {
		return ofn.lpstrFile;
	}

	else { return std::string(); }
}

std::map<std::string, OmClass> loadToSimulare1(int caz) {
	std::string fisierFolosit = "";
	switch (caz) {
	case 1: {
		fisierFolosit = openFile();
		break;
	}
	default: {
		fisierFolosit = "Database/oameni.json";
		break;
	}
	}

	std::ifstream fisierIn(fisierFolosit);

	Json::Reader reader;
	Json::Value val;
	reader.parse(fisierIn, val);
	const Json::Value& listaOameni = val["Oameni"];

	std::map<std::string, OmClass> oameni;
	for (int i = 0; listaOameni.size(); i++) {
		OmClass om;
		std::string key = listaOameni[i]["ID"].asString();
		om.inaltime = listaOameni[i]["inaltime"].asString();
		om.prenume = listaOameni[i]["prenume"].asString();
		om.sex = listaOameni[i]["sex"].asString();
		om.sociabilitate = listaOameni[i]["sociabilitate"].asString();
		om.varsta = listaOameni[i]["varsta"].asString();

		om.shape.setFillColor(sf::Color(0, 255, 0));


		om.pX = stoi(listaOameni[i]["pozX"].asString());
		om.pY = stoi(listaOameni[i]["pozY"].asString());
		om.shape.setPosition(om.pX, om.pY);
		oameni.insert({ key,om });
	}

	fisierIn.close();
	return oameni;
}

std::map<std::string, Oras> loadToSimulare2(int caz) {
	std::string fisierFolosit = "";
	switch (caz) {
	case 1: {
		fisierFolosit = openFile();
		break;
	}
	default: {
		fisierFolosit = "Database/orase.json";
		break;
	}
	}

	std::ifstream fisierIn(fisierFolosit);

	Json::Reader reader;
	Json::Value val;
	reader.parse(fisierIn, val);
	const Json::Value& listaOrase = val["Orase"];

	std::map<std::string, Oras> orase;
	for (int i = 0; listaOrase.size(); i++) {
		Oras oras = Oras(listaOrase[i]["denumire"].asString(), std::stoll(listaOrase[i]["populatie"].asString()),
			std::stof(listaOrase[i]["pX"].asString()), std::stod(listaOrase[i]["pY"].asString()));
		std::string key = listaOrase[i]["ID"].asString();


		orase.insert({ key,oras });
	}
	
	fisierIn.close();
	return orase;
}


