#include <iostream>
#include <fstream>
#include <cstdio>


//sfml
#include <include/SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <math.h>
#include <map>

//header
#include "Oras.h"
#include "HeaderSimulari.h"
#include "CalatorOras.h"
#include "HeaderVirus.h"
#include "SimulatorLoader.h"
#include "procenteOras.h"


namespace simOras {
	bool pauza;
	void pause() { pauza = true; }
	void resume() { pauza = false; }
	
	bool amClick = false;
	void reset() {
		//chestii care se reseteaza
		counterInfectati = 0;
		counterMorti = 0;
		counterVii = 0;
		counterVindecati = 0;
		amClick = false;
	}
	sf::Text textNpc;//textul pt fiecare NPC
	sf::Text textCounter;//numarul text
	sf::Clock ceas;
	float dt;//delta time
	const float nrFPS = FPS;
	int tipOrasClick = 0;//0 neinfectat 1 infectat  2 vindecat
	
	std::map<std::string, Oras>::iterator lastClick;
	float deltaTime() {

		return ceas.restart().asSeconds();//pt miscare in functie de frameuri

	}



}

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

#pragma warning(suppress : 4996)

std::map<string, Oras> infect;
std::map<string, Oras> sigur;
std::map<string, Oras> vindec;

std::map<string, CalatorOras>calatori;

int initEcranPrincipal();
std::map<std::string, Oras> generareOrase(int nrO, int nrN);


const float PI = 3.14159265359f;

#pragma once
double counterMorti=0;
double counterVii=0;
double counterInfectati=0;
double counterVindecati=0;

void drawOras(sf::RenderWindow& window)
{

	for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {
		Oras om = itr->second;
		//simOras::sumaInfectati += itr->second.getInfectati();
		window.draw(itr->second.shape);
		itr->second.orasSprite.setTexture(itr->second.textura);
		window.draw(itr->second.orasSprite);

	}
	for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {
		Oras om = itr->second;
		window.draw(itr->second.shape);
		itr->second.orasSprite.setTexture(itr->second.textura);
		window.draw(itr->second.orasSprite);
	}
	for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {
		Oras om = itr->second;
		//simOras::sumaInfectati += itr->second.getInfectati();
		window.draw(itr->second.shape);
		itr->second.orasSprite.setTexture(itr->second.textura);
		window.draw(itr->second.orasSprite);
	}

}

void setGroupOrasImunity()
{
	if (imunitateGrup != 0) {
		for (std::map<std::string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++)
		{
			itr->second.setVindec(itr->second.getPopulatie() * imunitateGrup / 100);
			counterVindecati += itr->second.getVindecati();
		}
	}

}


float computeAngle(float ax, float ay, float bx, float by) {
	return atan2((by - ay), (bx - ax));
};

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

void trimitCalator(Oras& oras)
{
	
	//aici calculez distanta dintre orase
	std::map<string, Oras>::iterator item = sigur.begin();
	if (sigur.size() == 0)
	{
		return;
	}
	std::advance(item, std::rand() % sigur.size());

	//in item este orasul pe care vrem sa il cotropim
	
	if (calatori.find(item->second.getDenum()) == calatori.end())
	{
		
		sf::Vector2f origin = sf::Vector2f(oras.pX, oras.pY);

		//Calculate the direction vector
		sf::Vector2f dirVec = sf::Vector2f(item->second.pX - origin.x, item->second.pY - origin.y);

		//Calculate the length^2
		float magSquare = std::sqrt((dirVec.x * dirVec.x) + (dirVec.y * dirVec.y));

		//Change the mag to 1 (you dont need the y for getting the angle
		dirVec.x = (dirVec.x) / magSquare;

		//Get the angle and change it to deg (SFML need deg)
		float rotAngle = std::acos(dirVec.x) * (180 / PI);

		float angle = computeAngle(oras.pX, oras.pY, item->second.pX, item->second.pY);

		sf::Vector2f dir;
		dir.x = cos(angle) * 100;
		dir.y = sin(angle) * 100;
		//dir=normalize(dir);

		CalatorOras calator = CalatorOras(oras.pX, oras.pY, dir, item);
		oras.setInfectati(oras.getInfectati() - 1);
		oras.setPopulatie(oras.getPopulatie() - 1);

		calatori.insert({ item->second.getDenum() ,calator });
		return;
	}
	else if (sigur.size() > calatori.size())
	{
		//trimitCalator(oras);
		return;
	}
	
}

void miscareCalatori()
{
	std::vector<std::map<std::string, CalatorOras>::iterator> vec;
	for (std::map<string, CalatorOras>::iterator itr = calatori.begin(); itr != calatori.end(); itr++) {
		itr->second.move(simOras::dt);

		float 
			X1, Y1, X2, Y2;
		sf::Transform matrix = itr->second.tinta->second.shape.getTransform();
		for (int i = 0; i < itr->second.tinta->second.shape.getPointCount(); ++i) {
			const auto pointInModelSpace = matrix.transformPoint(itr->second.tinta->second.shape.getPoint(i));
			switch (i) {
			case 0: {
				X1 = pointInModelSpace.x;
				break;
			}
			case 1: {
				Y1 = pointInModelSpace.y;
				break;

			}
			case 2: {
				X2 = pointInModelSpace.x;
				break;
			}
			case 3: {
				Y2 = pointInModelSpace.y;
				break;

			}
			}
		}
		if (itr->second.isTouchingOras(itr->second.razaShape, X1, Y1, X2, Y2))
		{
			vec.push_back(itr);
		}
	}
	for (int i = 0; i < vec.size(); i++)
	{
	    
		std::map<std::string, CalatorOras>::iterator itr = vec.at(i);

		std::string key = itr->second.tinta->first;
		Oras oras = itr->second.tinta->second;
		oras.shape.setFillColor(sf::Color(255, 122, 0));
		oras.setInfectati(oras.getInfectati() + 1);
		oras.setPopulatie(oras.getPopulatie()+1);


		std::deque<long long> nouaCota=oras.getNumVindZilnic();
		nouaCota.push_back(1);
		oras.setCota(nouaCota);

		oras.trimit = 0;
		infect.insert({ key,oras });
		//sumaInfectati++;
		if (simOras::tipOrasClick == 0)
		{
			if (simOras::lastClick == itr->second.tinta)
			{
				//modific iteratorul
				simOras::lastClick = infect.find(key);
				simOras::tipOrasClick = 1;
			}
		}
		if (sigur.find(key) != sigur.end()) {
			sigur.erase(key);
		}
		calatori.erase(itr);

		
	}
}

void drawCalatori(sf::RenderWindow& window)
{
	for (std::map<string, CalatorOras>::iterator itr = calatori.begin(); itr != calatori.end(); itr++) {
		CalatorOras om = itr->second;
		window.draw(itr->second.shape);
	}
}


int simulareOras() {

input:
	srand(time(0));
	simOras::pauza = true;


	sigur.clear();
	infect.clear();
	vindec.clear();
	calatori.clear();

	counterInfectati = 0;
	counterMorti = 0;
	counterVindecati = 0;
	counterVii = 0;

	/*Oras orastest("craiova", 100, 300, 300);
	orastest.shape.setSize(sf::Vector2f(60, 60));
	orastest.shape.setFillColor(sf::Color(0, 255, 0, 100));
	//orastest.shape.setPosition(300, 300);
	sigur.insert({ "1",orastest });

	Oras orastest2("galati", 100, 500.0, 200.0);
	orastest2.shape.setSize(sf::Vector2f(60, 60));
	orastest2.shape.setFillColor(sf::Color(0, 255, 0, 100));
	//orastest2.shape.setPosition(600, 300);
	sigur.insert({ "2",orastest2 });*/
	if (fisier::fisierIncarcat == true)
	{
		loadToSimulare2(sigur,infect);
	}
	else
	{
		sigur = generareOrase(nrOrase, nrNpc);
	}
	setGroupOrasImunity();

	


window:
	//aici bagam window-ul
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Randemic", sf::Style::Default);
	window.setFramerateLimit(simOras::nrFPS);


background:
	//fundalul
	sf::Texture backTexture;
	backTexture.loadFromFile("Sprites/fundal.png");
	sf::Sprite backSprite(backTexture);
	window.clear();
	window.draw(backSprite);


font_text:
	sf::Font font;
	font.loadFromFile("Fonts/KarmaFuture.ttf");


	simOras::textNpc.setFont(font);
	simOras::textCounter.setFont(font);


	simOras::textNpc.setCharacterSize(20);
	simOras::textCounter.setCharacterSize(20);

	simOras::textNpc.setFillColor(sf::Color::Black);
	simOras::textCounter.setFillColor(sf::Color::Black);

	simOras::textNpc.setStyle(sf::Text::Regular);
	simOras::textCounter.setStyle(sf::Text::Regular);

	simOras::textNpc.setPosition(995, 95);
	simOras::textCounter.setPosition(995, 300);

	// inside the main loop, between window.clear() and window.display()
	window.draw(simOras::textNpc);
	window.draw(simOras::textCounter);


adaugOmase:
	//generam 


	//desenam orasele
	drawOras(window);


display:
	window.display();

	//aici incepe nebunia dar tot Strafer e mai misto #quierres?
	simOras::deltaTime();


	int frames = 0;
	while (window.isOpen())
	{
		simOras::dt = simOras::deltaTime();
		

		sf::Event event;
		window.clear();
		window.draw(backSprite);//fundalul

		while (window.pollEvent(event))
		{
			//eventuri

			switch (event.type) {
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape)
				{
					sigur.clear();
					infect.clear();
					vindec.clear();
					std::map<std::string, Oras>::iterator iterator;
					simOras::lastClick = iterator;
					calatori.clear();
					window.close();
					return 0;
				}
				else if (event.key.code == sf::Keyboard::F1)
				{
					sigur.clear();
					infect.clear();
					vindec.clear();
					std::map<std::string, Oras>::iterator iterator;
					simOras::lastClick = iterator;
					calatori.clear();
					simOras::reset();
					goto input;
					return 0;

				}
				else if (event.key.code == sf::Keyboard::F2)
				{
					sigur.clear();
					infect.clear();
					vindec.clear();
					std::map<std::string, Oras>::iterator iterator;
					simOras::lastClick = iterator;
					calatori.clear();
					window.close();
					simOras::reset();
					simOras::amClick = false;
					fisier::fisierIncarcat = false;
					initEcranPrincipal();
					return 0;

				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					simOras::pauza = !simOras::pauza;

				}

				break;
			}
			case sf::Event::Closed: {
				
				sigur.clear();
				infect.clear();
				vindec.clear();
				std::map<std::string, Oras>::iterator iterator;
				simOras::lastClick = iterator;
				simOras::amClick = false;
				calatori.clear();
				window.close();
				return 0;
				
			}

			default: {
				//ca sa poti sa dai click pe orase

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					bool amOras = false;
					simOras::tipOrasClick = -1;

					for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {
						//simOras::counterMorti+=itr->second.getDeced();
						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 0;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true&&	
						simOras::lastClick->second.getPopulatie()-simOras::lastClick->second.getInfectati()-simOras::lastClick->second.getVindecati()-simOras::lastClick->second.getDeced()>0)
					{
						//adaug infectat
						counterInfectati++;
						std::string key = simOras::lastClick->first;
						Oras oras = simOras::lastClick->second;
						sigur.erase(key);

						

						oras.shape.setFillColor(sf::Color(255, 122, 0));
						oras.setInfectati(oras.getInfectati() + 1);
						

						std::deque<long long> nouaCota;
						nouaCota.push_back(1);
						oras.setCota(nouaCota);

						infect.insert({ key,oras });
						simOras::lastClick = infect.find(key);
						simOras::tipOrasClick = 1;

						if (calatori.find(simOras::lastClick->second.getDenum()) != calatori.end()) {
							//avem un calator spre oras
							calatori.find(simOras::lastClick->second.getDenum())->second.tinta = simOras::lastClick;
						}

						break;
					}
					for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;
						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true)
					{
						//adaug infectat
						counterInfectati++;
						if (simOras::lastClick->second.getPopulatie() == simOras::lastClick->second.getInfectati()) {

							simOras::lastClick->second.setPopulatie(simOras::lastClick->second.getPopulatie() + 1);
							nrNpc++;
						}
						simOras::lastClick->second.setInfectati(simOras::lastClick->second.getInfectati() + 1);

						std::deque<long long> nouaCota = simOras::lastClick->second.getNumVindZilnic();
						nouaCota.push_back(1);
						simOras::lastClick->second.setCota(nouaCota);
						break;
					}
					for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 2;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true)
					{
						//adaug un infectat
						simOras::lastClick->second.setInfectati(simOras::lastClick->second.getInfectati() + 1);
						if (simOras::lastClick->second.getPopulatie() == simOras::lastClick->second.getInfectati()) {

							simOras::lastClick->second.setPopulatie(simOras::lastClick->second.getPopulatie() + 1);
							nrNpc++;
						}
						counterInfectati++;
						std::deque<long long> nouaCota = simOras::lastClick->second.getNumVindZilnic();
						nouaCota.push_back(1);
						simOras::lastClick->second.setCota(nouaCota);
						
						break;
					}
					break;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					bool amOras = false;
					simOras::tipOrasClick = -1;

					for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 0;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true)
					{
						//nu fac nimic
						break;
					}
					for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;
						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true)
					{
						//sterg infectat
						simOras::lastClick->second.setInfectati(simOras::lastClick->second.getInfectati() - 1);
						std::deque<long long> nouaCota = simOras::lastClick->second.getNumVindZilnic();
						long long val = nouaCota.at(nouaCota.size() - 1);
						nouaCota.pop_back();
						nouaCota.push_back(val);
						simOras::lastClick->second.setCota(nouaCota);
						counterInfectati--;
						if (simOras::lastClick->second.getInfectati() == 0) {
							//trec in alta categorie
							std::string key = simOras::lastClick->first;
							Oras oras = simOras::lastClick->second;
							infect.erase(simOras::lastClick);
							if (oras.getPopulatie() == oras.getVindecati())
							{
								//am mai multi vindecati decat susceptibili
								oras.shape.setFillColor(sf::Color(0, 0, 255));
								vindec.insert({ key,oras });
								simOras::lastClick = vindec.find(key);

								simOras::tipOrasClick = 2;
							}
							else {
								//inca e susceptibil
								oras.shape.setFillColor(sf::Color(0, 255, 0));
								sigur.insert({ key,oras });
								simOras::lastClick = sigur.find(key);

								simOras::tipOrasClick = 0;
							}
						}

						break;
					}
					for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							simOras::amClick = true;
							simOras::lastClick = itr;
							simOras::tipOrasClick = 2;
							amOras = true;
							break;
						}
					}
					if (amOras == true && simOras::pauza == true)
					{
						//nu sterg nimic

						break;
					}

				}
				break;

			}


			}




		}
		if (simOras::pauza == false) {
			//ruleaza

			//merg in fiecare oras si ii dau update
			std::vector<std::map<string, Oras>::iterator> oraseVindec;
			std::vector<std::map<string, Oras>::iterator> oraseSigure;
			for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

				if (frames == 0)
				{

					itr->second.update();
					if (itr->second.getInfectati() <= 0)
					{
						itr->second.setInfectati(0);
						if (itr->second.getPopulatie() == itr->second.getVindecati())
						{
							//orasul e sigur
							oraseVindec.push_back(itr);
						}
						else
						{
							oraseSigure.push_back(itr);
						}
					}
					itr->second.trimit++;
					
					if (itr->second.trimit > timpCalator && itr->second.getInfectati()>10)
					{
						trimitCalator(itr->second);
						itr->second.trimit = 0;
					}
						
				}

			}
		
			for (int i = 0; i < oraseVindec.size(); i++)
			{
				//sterg din infectati
				std::map<string, Oras>::iterator iteratorInfectat = oraseVindec.at(i);
				Oras oras = iteratorInfectat->second;
				std::string key = iteratorInfectat->first;

				oras.shape.setFillColor(sf::Color(0, 0, 255));
				vindec.insert({ key,oras });
				if (simOras::tipOrasClick == 1 && iteratorInfectat == simOras::lastClick)
				{
					//modific lastClick si oras
					simOras::tipOrasClick = 2;
					simOras::lastClick = vindec.find(key);
				}
				infect.erase(key);
			}

			for (int i = 0; i < oraseSigure.size(); i++)
			{
				//sterg din infectati
				std::map<string, Oras>::iterator iteratorInfectat = oraseSigure.at(i);
				Oras oras = iteratorInfectat->second;
				std::string key = iteratorInfectat->first;

				oras.shape.setFillColor(sf::Color(0, 255, 0));
				sigur.insert({ key,oras });
				if (simOras::tipOrasClick == 1 && iteratorInfectat == simOras::lastClick)
				{
					//modific lastClick si oras
					simOras::tipOrasClick = 0;
					simOras::lastClick = sigur.find(key);
				}
				infect.erase(key);
			}
			miscareCalatori();
			frames++;
			if (frames >= FPS)
			{
				frames = 0;
			}
		}


		drawOras(window);
		drawCalatori(window);
		
		std::string infectatiProc = to_string(100 * double(counterInfectati / nrNpc));
		infectatiProc.erase(infectatiProc.length() - 5);

		std::string vindecProc = to_string(100 * double(counterVindecati / nrNpc));
		vindecProc.erase(vindecProc.length() - 5);

		std::string decedProc = to_string(100 * double(counterMorti / nrNpc));
		decedProc.erase(decedProc.length() - 5);

		if (simOras::amClick == true) {
			//am dat click pe cineva

			simOras::textNpc.setString((simOras::lastClick->second).getDenum() + "\n Populatie: " + to_string((simOras::lastClick->second).getPopulatie())
				+ "\n Infectati: " + to_string((simOras::lastClick->second).getInfectati())
				+ "\n Vindecati: " + to_string((simOras::lastClick->second).getVindecati())
				+ "\n Decedati: " + to_string((simOras::lastClick->second).getDeced())
				
				+"\n \n \n \n \nProcente populatie:"
				+"\n Infectata: "+ infectatiProc +"%"
				+ "\n Vindecata: " + vindecProc + "%"
				+"\n Decedata: " + decedProc+"%");
		}
		window.draw(simOras::textNpc);
		 
		window.display();
		
	}
	return 0;
}