#include "SimulatorLoader.h"
#include <json/json.h>
#include <fstream>


#include <Windows.h>
#include <commdlg.h>

void loadToSimulare1(int caz){
	switch (caz) {
	case 1: {
		loaderF::fisierFolosit = openFile();
		break;
	}
	default: {
		loaderF::fisierFolosit = "Database/oameni.json";
		break;
	}
	}
		std::ifstream fisierIn(loaderF::fisierFolosit);
	
	Json::Reader reader;
	Json::Value val;
	reader.parse(fisierIn, val);
	const Json::Value& listaOameni = val["Oameni"];

	std::map<std::string, OmClass> oameni;
	for (int i = 0; listaOameni.size(); i++) {
		OmClass om;
		std::string key=listaOameni[i]["ID"].asString();
		om.inaltime=listaOameni[i]["inaltime"].asString();
		om.prenume=listaOameni[i]["prenume"].asString();
		om.sex=listaOameni[i]["sex"].asString();
		om.sociabilitate=listaOameni[i]["sociabilitate"].asString();
		om.varsta=listaOameni[i]["varsta"].asString();

		om.stare = listaOameni[i]["stare"].asString();

		om.pX = stoi(listaOameni[i]["pozX"].asString());
		om.pY = stoi(listaOameni[i]["pozY"].asString());

	}

	fisierIn.close();
}

void loadToSimulare2(int caz) {


}


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

	return std::string();

}