#include "SimulatorLoader.h"
#include <json/json.h>
#include <fstream>

void loadToSimulare1()
{
	std::ifstream fisierIn("Database/oameni.json");
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

void loadToSimulare2() {

}