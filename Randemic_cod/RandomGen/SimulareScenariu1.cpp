#include <iostream>
#include <fstream>



//sfml
#include <include/SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <map>

//header
#include "HeaderNpc.h"
#include "HeaderVirus.h"
#include "OmClass.h"
#include "HeaderSimulari.h"


namespace sim1 {

	bool isPaused;
	void pause() { isPaused = true; }
	void resume() { isPaused = false; }
	int counterMorti = 0;
	int counterVii;
	int counterInfectati = 0;
	int counterVindecati;
	void reset() {
		//chestii care se reseteaza
		counterInfectati = 0;
		counterMorti = 0;
		counterVii = 0;
		counterVindecati = 0;

	}
	const float nrFPS = FPS;
	int nrNpcuri = nrNpc;
	bool amClick = false;
	std::map<std::string, OmClass>::iterator lastClick;
	int tip = 0;//0 sanatos 
				//1 infectat
				//2	vindecat
				//3 mort

	sf::Text textNpc;//textul pt fiecare NPC
	sf::Text textCounter;//numarul text
	sf::Clock ceas;
	float dt;//delta time


	float deltaTime() {

		return ceas.restart().asSeconds();//pt miscare in functie de frameuri
	}

}

using namespace std;
using namespace sim1;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

#pragma warning(suppress : 4996)

std::map<string, OmClass> oameniSanatosi;//oamenii creati in header
std::map<string, OmClass> oameniInfectati;//oamenii creati in header
std::map<string, OmClass> oameniDecedati;//oamenii creati in header
std::map<string, OmClass> oameniVindecati;//oamenii creati in header

bool isHitDetection(OmClass sanatos)
{
	//avem hit-detection diferit in functie de infectati

	for (std::map<std::string, OmClass>::iterator col = oameniInfectati.begin(); col != oameniInfectati.end(); col++) {


		//folosim formula AABB pt hit detection
		int raza1 = stoi(sanatos.sociabilitate) + razaShape - 3, x1 = sanatos.pX, y1 = sanatos.pY;
		int raza2 = stoi(col->second.sociabilitate) + razaShape - 3, x2 = col->second.pX, y2 = col->second.pY;

		int dx = x1 - x2;
		int dy = y1 - y2;
		int distance = sqrt(dx * dx + dy * dy);

		int probInfectie = rand() % 100 + 1;

		if (distance < raza1 + raza2 && probInfectie <= infectabilitate && col->second.timpInfectare>=timpIncubare) {
			return true;

		}
	}
	return false;

}

void miscareNpc() {
	//functie de miscare
	for (std::map<string, OmClass>::iterator itr = oameniInfectati.begin(); itr != oameniInfectati.end(); itr++) {
		//aicea ne miscam(putin dans)
		sf::Vector2f vec1 = itr->second.misc;
		vec1.x = vec1.x * sim1::dt;
		vec1.y = vec1.y * sim1::dt;

		itr->second.shape.move(vec1);

		auto pozitie = itr->second.shape.getPosition();
		itr->second.pX = pozitie.x + razaShape;
		itr->second.pY = pozitie.y + razaShape;

		if (itr->second.pX >= 939.f || itr->second.pX <= 37.f) {

			itr->second.misc.x = itr->second.misc.x * (-1);
		}

		if (itr->second.pY >= 682.f || itr->second.pY <= 37.f) {

			itr->second.misc.y = itr->second.misc.y * (-1);
		}
	}

	std::vector<std::map<std::string, OmClass>::iterator> nouInfect;
	for (std::map<string, OmClass>::iterator itr = oameniSanatosi.begin(); itr != oameniSanatosi.end(); itr++) {

		sf::Vector2f vec1 = itr->second.misc;
		vec1.x = vec1.x * sim1::dt;
		vec1.y = vec1.y * sim1::dt;

		itr->second.shape.move(vec1);

		auto pozitie = itr->second.shape.getPosition();
		itr->second.pX = pozitie.x + razaShape;
		itr->second.pY = pozitie.y + razaShape;

		if (itr->second.pX >= 939.f || itr->second.pX <= 37.f) {

			itr->second.misc.x = itr->second.misc.x * (-1);
		}

		if (itr->second.pY >= 682.f || itr->second.pY <= 37.f) {

			itr->second.misc.y = itr->second.misc.y * (-1);
		}
		if (isHitDetection(itr->second)) {
			// coliziune detectata!
			//se transforma in infectat
			nouInfect.push_back(itr);
		}
	}

	for (int i = 0; i < nouInfect.size(); i++)
	{
		std::map<std::string, OmClass>::iterator itr = nouInfect.at(i);
		std::string key = itr->first;
		OmClass om = itr->second;
		om.shape.setFillColor(sf::Color(255, 125, 0));
		om.stare = "infectat";
		sim1::counterInfectati++;
		om.timpInfectare = 0;
		oameniInfectati.insert({ key,om });

		if (tip == 0)
		{
			if (sim1::lastClick == itr)
			{
				sim1::lastClick = oameniVindecati.find(key);
				tip = 1;
			}


		}
		//sim1::amClick = false;
		oameniSanatosi.erase(itr);

		textCounter.setString("In viata: " + to_string(sim1::counterVii) +
			"\nInfectati: " + to_string(sim1::counterInfectati) +
			"\nVindecati: " + to_string(sim1::counterVindecati) +
			"\nDecedati: " + to_string(sim1::counterMorti));

	}

	for (std::map<string, OmClass>::iterator itr = oameniVindecati.begin(); itr != oameniVindecati.end(); itr++) {
		sf::Vector2f vec1 = itr->second.misc;
		vec1.x = vec1.x * sim1::dt;
		vec1.y = vec1.y * sim1::dt;

		itr->second.shape.move(vec1);

		auto pozitie = itr->second.shape.getPosition();
		itr->second.pX = pozitie.x + razaShape;
		itr->second.pY = pozitie.y + razaShape;

		if (itr->second.pX >= 939.f || itr->second.pX <= 37.f) {

			itr->second.misc.x = itr->second.misc.x * (-1);
		}

		if (itr->second.pY >= 682.f || itr->second.pY <= 37.f) {

			itr->second.misc.y = itr->second.misc.y * (-1);
		}
	}
}

void updateInfectati()
{
	std::vector<std::map<std::string, OmClass>::iterator> nouVindec = {};
	std::vector<std::map<std::string, OmClass>::iterator> nouDeced = {};
	for (std::map<string, OmClass>::iterator itr = oameniInfectati.begin(); itr != oameniInfectati.end(); itr++) {
		//desenez npc-urile pe ecran si calculam valorile

		itr->second.timpInfectare++;
		if (itr->second.timpInfectare >= timpRecuperare + timpIncubare) {
			int procSupravietuire = rand() % 100;
			if (procSupravietuire <= mortalitate)
			{
				//moare individul
				nouDeced.push_back(itr);
				sim1::counterMorti++;
				sim1::counterVii--;
			}
			else
			{
				nouVindec.push_back(itr);
				sim1::counterVindecati++;
			}
			textCounter.setString("In viata: " + to_string(counterVii) +
				"\nInfectati: " + to_string(sim1::counterInfectati) +
				"\nVindecati: " + to_string(sim1::counterVindecati) +
				"\nDecedati: " + to_string(sim1::counterMorti));
		}
		else if (itr->second.timpInfectare >= timpIncubare && itr->second.shape.getFillColor()!=sf::Color(255,0,0))
		{
			//ii schimb culoarea
			itr->second.shape.setFillColor(sf::Color(255, 0, 0));
		}

	}

	for (int i = 0; i < nouDeced.size(); i++)
	{
		std::map<std::string, OmClass>::iterator itr = nouDeced.at(i);
		OmClass om = itr->second;
		std::string key = itr->first;

		om.stare = "decedat";
		om.shape.setFillColor(sf::Color(0, 0, 0));
		oameniDecedati.insert({ key,om });

		if (tip == 1)
		{
			if (sim1::lastClick == itr)
			{
				sim1::lastClick = oameniDecedati.find(key);
				tip = 3;
			}

			//sim1::amClick = false;
		}
		oameniInfectati.erase(key);


	}

	for (int i = 0; i < nouVindec.size(); i++)
	{
		std::map<std::string, OmClass>::iterator itr = nouVindec.at(i);
		std::string key = itr->first;
		OmClass om = itr->second;
		om.stare = "vindecat";
		om.shape.setFillColor(sf::Color(0, 0, 255));
		oameniVindecati.insert({ key,om });

		if (tip == 1)
		{
			if (sim1::lastClick == itr)
			{
				sim1::lastClick = oameniVindecati.find(key);
				tip = 2;
			}
		}
		//sim1::amClick = false;
		oameniInfectati.erase(key);


	}
}

void drawOameni(sf::RenderWindow& window)
{
	for (std::map<string, OmClass>::iterator itr = oameniSanatosi.begin(); itr != oameniSanatosi.end(); itr++) {
		OmClass om = itr->second;
		window.draw(itr->second.shape);
	}
	for (std::map<string, OmClass>::iterator itr = oameniInfectati.begin(); itr != oameniInfectati.end(); itr++) {
		OmClass om = itr->second;
		window.draw(itr->second.shape);
	}
	for (std::map<string, OmClass>::iterator itr = oameniVindecati.begin(); itr != oameniVindecati.end(); itr++) {
		OmClass om = itr->second;
		window.draw(itr->second.shape);
	}
	for (std::map<string, OmClass>::iterator itr = oameniDecedati.begin(); itr != oameniDecedati.end(); itr++) {
		OmClass om = itr->second;
		window.draw(itr->second.shape);
	}
	window.draw(textCounter);
}

void setGroupImunity()
{
	if (imunitateGrup != 0) {
		int size = 1ll * nrNpc / 100 * imunitateGrup;
		std::vector< std::map<std::string, OmClass>::iterator> vindec;
		std::map<std::string, OmClass>::iterator itr = oameniSanatosi.begin();
		while (1) {
			size--;
			if (size == 0)
			{
				break;
			}
			vindec.push_back(itr);


			itr++;
		}
		for (int i = 0; i < vindec.size(); i++)
		{
			itr = vindec.at(i);
			//trec de la sanatos la vindecat
			OmClass om = itr->second;
			std::string key = itr->first;

			oameniSanatosi.erase(itr);

			om.shape.setFillColor(sf::Color(0, 0, 255));
			om.stare = "vindecat";
			counterVindecati++;
			//om.shape.setRotation(rand() % 90);
			textCounter.setString("In viata: " + to_string(counterVii) +
				"\nInfectati: " + to_string(counterInfectati) +
				"\nVindecati: " + to_string(counterVindecati) +
				"\nDecedati: " + to_string(counterMorti));
			om.timpInfectare = 0;
			oameniVindecati.insert({ key,om });
		}
	}

}
#pragma once
int initEcranPrincipal();

int simulare1() {

input:
	srand(time(0));
	sim1::isPaused = true;



	nrNpcuri = nrNpc;
	counterVii = sim1::nrNpcuri;

	oameniSanatosi.clear();
	oameniInfectati.clear();
	oameniVindecati.clear();
	oameniDecedati.clear();

	oameniSanatosi = simulare(sim1::nrNpcuri);
	sim1::amClick = false;
	sim1::lastClick = oameniSanatosi.begin();
	sim1::tip = 0;//0 sanatos 
				//1 infectat
				//2	vindecat
				//3 mort

	setGroupImunity();
window:
	//aici bagam window-ul
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Randemic", sf::Style::Default);
	window.setFramerateLimit(nrFPS);


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


	textNpc.setFont(font);
	textCounter.setFont(font);


	textNpc.setCharacterSize(20);
	textCounter.setCharacterSize(20);

	textNpc.setFillColor(sf::Color::Black);
	textCounter.setFillColor(sf::Color::Black);

	textNpc.setStyle(sf::Text::Regular);
	textCounter.setStyle(sf::Text::Regular);

	textNpc.setPosition(995, 95);
	textCounter.setPosition(995, 300);

	// inside the main loop, between window.clear() and window.display()
	window.draw(textNpc);
	window.draw(textCounter);


adaugOameni:
	//desenam oamenii

	textCounter.setString("In viata: " + to_string(sim1::counterVii) +
		"\nInfectati: " + to_string(sim1::counterInfectati) +
		"\nVindecati: " + to_string(sim1::counterVindecati) +
		"\nMorti: " + to_string(sim1::counterMorti));



display:
	window.display();
	drawOameni(window);
	//aici incepe nebunia dar tot Strafer e mai misto #quierres?




	deltaTime();
	while (window.isOpen())
	{
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
					window.close();
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					sim1::reset();
					goto input;
				}
				else if (event.key.code == sf::Keyboard::T)
				{
					window.close();
					initEcranPrincipal();

				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					sim1::isPaused = !sim1::isPaused;

				}
				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}

			default: {
				//ca sa poti sa dai click pe oamenii astia simulati

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					tip = -1;
					for (std::map<string, OmClass>::iterator itr = oameniSanatosi.begin(); itr != oameniSanatosi.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							sim1::lastClick = itr;
							tip = 0;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniInfectati.begin(); itr != oameniInfectati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 1;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniVindecati.begin(); itr != oameniVindecati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 2;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniDecedati.begin(); itr != oameniDecedati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 3;
						}
					}

					if (sim1::isPaused == true)
					{
						//pot sa le schimb si pozitia
						if (tip == 0)
						{
							//e sanatos,il schimb in infectat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniSanatosi.erase(sim1::lastClick);

							om.shape.setFillColor(sf::Color(255, 125, 0));
							om.stare = "infectat";
							counterInfectati++;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniInfectati.insert({ key,om });
							lastClick = oameniInfectati.find(key);
							tip = 1;
						}
						else if (tip == 1)
						{
							//trec la vindecat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniInfectati.erase(key);

							om.shape.setFillColor(sf::Color(0, 0, 255));
							om.stare = "vindecat";
							counterInfectati--;
							counterVindecati++;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniVindecati.insert({ key,om });
							lastClick = oameniVindecati.find(key);
							tip = 2;
						}
						else if (tip == 2)
						{
							//trec la decedat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniVindecati.erase(sim1::lastClick);

							om.shape.setFillColor(sf::Color(0, 0, 0));
							om.stare = "decedat";
							counterMorti++;
							counterVindecati--;
							sim1::counterVii--;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniDecedati.insert({ key,om });
							lastClick = oameniDecedati.find(key);
							tip = 3;
						}
						else if (tip == 3)
						{
							//il schimb inapoi in sanatos
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniDecedati.erase(key);

							om.shape.setFillColor(sf::Color(0, 255, 0));
							om.stare = "sanatos";
							counterMorti--;
							sim1::counterVii++;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniSanatosi.insert({ key,om });
							lastClick = oameniSanatosi.find(key);
							tip = 0;
						}
					}


				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					tip = -1;
					for (std::map<string, OmClass>::iterator itr = oameniSanatosi.begin(); itr != oameniSanatosi.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							sim1::lastClick = itr;
							tip = 0;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniInfectati.begin(); itr != oameniInfectati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 1;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniVindecati.begin(); itr != oameniVindecati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 2;
						}
					}
					for (std::map<string, OmClass>::iterator itr = oameniDecedati.begin(); itr != oameniDecedati.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tip = 3;
						}
					}

					if (sim1::isPaused == true)
					{
						//pot sa le schimb si pozitia
						if (tip == 0)
						{
							//e sanatos,il schimb la decedat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniSanatosi.erase(sim1::lastClick);

							om.shape.setFillColor(sf::Color(0, 0, 0));
							om.stare = "decedat";
							counterMorti++;
							sim1::counterVii--;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniDecedati.insert({ key,om });
							lastClick = oameniDecedati.find(key);
							tip = 3;
						}
						else if (tip == 1)
						{
							//trec la sanatos
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniInfectati.erase(key);

							om.shape.setFillColor(sf::Color(0, 255, 0));
							om.stare = "sanatos";

							counterInfectati--;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniSanatosi.insert({ key,om });
							lastClick = oameniSanatosi.find(key);
							tip = 0;
						}
						else if (tip == 2)
						{
							//trec la infectat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniVindecati.erase(sim1::lastClick);

							om.shape.setFillColor(sf::Color(255, 125, 0));
							om.stare = "infectat";
							counterInfectati++;;
							counterVindecati--;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniInfectati.insert({ key,om });
							lastClick = oameniInfectati.find(key);
							tip = 1;
						}
						else if (tip == 3)
						{
							//il schimb inapoi in vindecat
							std::string key = lastClick->first;
							OmClass om = lastClick->second;
							oameniDecedati.erase(key);

							om.shape.setFillColor(sf::Color(0, 0, 255));
							om.stare = "vindecat";
							counterMorti--;
							counterVindecati++;
							sim1::counterVii++;
							//om.shape.setRotation(rand() % 90);
							textCounter.setString("In viata: " + to_string(counterVii) +
								"\nInfectati: " + to_string(counterInfectati) +
								"\nVindecati: " + to_string(counterVindecati) +
								"\nDecedati: " + to_string(counterMorti));
							om.timpInfectare = 0;

							oameniVindecati.insert({ key,om });
							lastClick = oameniVindecati.find(key);
							tip = 2;
						}
					}
				}
				break;


			}


			}

		}
		dt = deltaTime();
		if (sim1::isPaused == false) {
			//ruleaza

			updateInfectati();
			miscareNpc();

		}

		drawOameni(window);
		if (amClick == true)
		{
			textNpc.setString(lastClick->second.prenume + "\n Sex: " + lastClick->second.sex
				+ "\n Varsta: " + lastClick->second.varsta
				+ "\n Inaltime: " + lastClick->second.inaltime
				+ "\n Stare: " + lastClick->second.stare);

		}
		else {
			textNpc.setString(" ");
		}
		window.draw(textNpc);
		window.display();

	}
	return 0;
}