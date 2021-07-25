#include "SimulatorLoader.h"
#include <json/json.h>
#include <fstream>


#include <Windows.h>
#include <commdlg.h>
#include <sstream>
#include "HeaderNpc.h"
#include "HeaderSimulari.h"
#include "procenteOras.h"

std::string fisier::fisierFolosit = "";
bool fisier::fisierIncarcat = false;

std::string setTextura(Oras& oras, long long populatieMaxima);

std::map<std::string, OmClass> oameniSanatosiHead;
std::map<std::string, OmClass> oameniInfectatiHead;
std::map<std::string, OmClass> oameniVindecatiHead;
std::map<std::string, OmClass> oameniDecedatiHead;

std::map<std::string, Oras> oraseSigure;
std::map<std::string, Oras> oraseInfect;
std::map<std::string, Oras> oraseVindec;
void openFile()
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

	

	if (GetOpenFileNameA(&ofn) == TRUE) {
		fisier::fisierFolosit = ofn.lpstrFile;
		fisier::fisierIncarcat = true;
		return;
		//return ofn.lpstrFile;
	}

	fisier::fisierIncarcat = false;
	//return std::string(); 
	
}

void loadToSimulare1() {
    /* std::string fisierFolosit = "";
    switch (caz) {
    case 1: {
        fisierFolosit = openFile();
        break;
    }
    default: {
        fisierFolosit = "Database/oameni.json";
        break;
    }
    } */
        srand(time(0));
        oameniSanatosiHead.clear();
        oameniInfectatiHead.clear();
        oameniVindecatiHead.clear();
        oameniDecedatiHead.clear();
    std::ifstream fisierIn(fisier::fisierFolosit);

    Json::Reader reader;
    Json::Value val;
    reader.parse(fisierIn, val);
    const Json::Value& listaOameni = val["listaNPC"];

    //std::map<std::string, OmClass> oameni;
    nrNpc = listaOameni.size();
    //counterVii = nrNpc;
    for (int i = 0; i < listaOameni.size(); i++) {
        OmClass om;
        std::string key = listaOameni[i]["ID"].asString();
        om.inaltime = listaOameni[i]["inaltime"].asString();

        std::string pix = listaOameni[i]["pozX"].asString();
        std::stringstream strnN(pix);
        strnN >> om.pX;

        std::string piY = listaOameni[i]["pozY"].asString();
        std::stringstream strnNY(piY);
        strnNY >> om.pY;

        //om.pY = stoi(listaOameni[i]["pozY"].asString());
        om.shape.setPosition(om.pX, om.pY);

        om.prenume = listaOameni[i]["prenume"].asString();
        om.sex = listaOameni[i]["sex"].asString();
        om.sociabilitate = listaOameni[i]["sociabilitate"].asString();
        om.varsta = listaOameni[i]["varsta"].asString();


        om.shape.setRadius(razaShape);
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
        
        //0 sanatos
        //1 infectat
        //2 vindecat
        //3 decedat


        bool eGasit = listaOameni[i].isMember("stare");
        if (eGasit) 
        {
            //nu ia bine stringul
           int val = listaOameni[i]["stare"].asInt();
            if (val==0)
            {
                om.stare = "sanatos";
                om.shape.setFillColor(sf::Color(0, 255, 0));
                oameniSanatosiHead.insert({ {key, om} });
            }
            else if (val==1)
            {
                om.stare = "infectat";
                om.shape.setFillColor(sf::Color(255, 125, 0));
                
                bool isTimp = listaOameni[i].isMember("timpInfectare");
                if (isTimp) { om.timpInfectare = listaOameni[i]["timpInfectare"].asInt(); }
                else { om.timpInfectare = 0; }
                oameniInfectatiHead.insert({ {key, om} });
            }
            else if (val==2)
            {
                
                om.stare = "vindecat";
                om.timpInfectare = 0;
                om.shape.setFillColor(sf::Color(0, 0, 255));
                oameniVindecatiHead.insert({ {key, om} });
            }
            else if (val==3)
            {
                om.stare = "decedat";
                om.timpInfectare = 0;
                om.shape.setFillColor(sf::Color(0, 0, 0));
                oameniDecedatiHead.insert({ {key, om} });

            }
        }
        else
        {
            //e sanatos din default
            om.stare = "sanatos";
            om.shape.setFillColor(sf::Color( 0,255, 0));
            oameniSanatosiHead.insert({ {key, om} });

        }

        //oameni.insert({key, om});
    }

    fisierIn.close();

}

void loadToSimulare2() {
	/*std::string fisierFolosit = "";
	switch (caz) {
	case 1: {
		fisierFolosit = openFile();
		break;
	}
	default: {
		fisierFolosit = "Database/orase.json";
		break;
	}
	}*/
    oraseInfect.clear();
    oraseSigure.clear();
    oraseVindec.clear();

    counterVii = 0;
    counterMorti = 0;
    counterInfectati = 0;
    counterVindecati = 0;
	std::ifstream fisierIn(fisier::fisierFolosit);

	Json::Reader reader;
	Json::Value val;
	reader.parse(fisierIn, val);
	const Json::Value& listaOrase = val["Orase"];

	
	long long populatieMaxima = 0;
	for (int i = 0; i<listaOrase.size(); i++) {
		//
		float peX;
		double peY;
		long long peL;
		std::string pix = listaOrase[i]["pX"].asString();
		std::stringstream strnN(pix);
		strnN >> peX;

		std::string piY = listaOrase[i]["pY"].asString();
		std::stringstream strnNY(piY);
		strnNY >> peY;
		//

		std::string piL = listaOrase[i]["populatie"].asString();
		std::stringstream strnNL(piL);
		strnNL >> peL;
        
		Oras oras = Oras(listaOrase[i]["denumire"].asString(),
			peL,
			peX, peY);//std::stof(listaOrase[i]["pX"].asString()), std::stod(listaOrase[i]["pY"].asString()));
		
		oras.orasSprite.setPosition(sf::Vector2f(peX, peY));
		oras.shape.setPosition(sf::Vector2f(oras.orasSprite.getPosition()));
		std::string key = listaOrase[i]["ID"].asString();
        if (listaOrase[i].isMember("infectati"))
        {
            std::string infect = listaOrase[i]["infectati"].asString();
            std::stringstream strnINFECT(infect);
            long long int infectari=0;
            strnINFECT >> infectari;
            oras.setInfectati(infectari);
            counterInfectati += infectari;
            std::deque<long long int> nouaCota;
            nouaCota.push_back(infectari);
            oras.setCota(nouaCota);
            oraseInfect.insert({ key,oras });
        }
        else
        {
           oraseSigure.insert({ key,oras });
        }
		populatieMaxima += peL;
		
	}
	for (std::map<std::string, Oras>::iterator itr = oraseSigure.begin(); itr != oraseSigure.end(); itr++) {


		itr->second.textura.loadFromFile(setTextura(itr->second, populatieMaxima));
		itr->second.orasSprite.setTexture(itr->second.textura);
		int marimeY = itr->second.orasSprite.getTextureRect().height;
		int marimeX = itr->second.orasSprite.getTextureRect().width;
		itr->second.shape.setSize(sf::Vector2f(marimeX, marimeY));
		itr->second.shape.setFillColor(sf::Color(0, 255, 0));
	}
    for (std::map<std::string, Oras>::iterator itr = oraseInfect.begin(); itr != oraseInfect.end(); itr++) {


        itr->second.textura.loadFromFile(setTextura(itr->second, populatieMaxima));
        itr->second.orasSprite.setTexture(itr->second.textura);
        int marimeY = itr->second.orasSprite.getTextureRect().height;
        int marimeX = itr->second.orasSprite.getTextureRect().width;
        itr->second.shape.setSize(sf::Vector2f(marimeX, marimeY));
        itr->second.shape.setFillColor(sf::Color(255, 122, 0));
    }
    
	fisierIn.close();
	
}

std::map<std::string, OmClass> getOameniSiguri() {
    return oameniSanatosiHead;
}
std::map<std::string, OmClass> getOameniInfect() {
    return oameniInfectatiHead;
}
std::map<std::string, OmClass> getOameniVindec() {
    return oameniVindecatiHead;
}
std::map<std::string, OmClass> getOameniDeced() {
    return oameniDecedatiHead;
}

std::map<std::string, Oras> getOraseSigure() {
    return oraseSigure;
}
std::map<std::string, Oras> getOraseInfect() {
    return oraseInfect;
}
std::map<std::string, Oras> getOraseVindec()
{
    return oraseVindec;
}