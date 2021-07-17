#include <iostream>
#include <fstream>



//sfml
#include <include/SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <map>

//header
#include "Oras.h"
#include "HeaderSimulari.h"
#include "CalatorOras.h"


namespace simOras {
	bool pauza;
	void pause() { pauza = true; }
	void resume() { pauza = false; }
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
	sf::Text textNpc;//textul pt fiecare NPC
	sf::Text textCounter;//numarul text
	sf::Clock ceas;
	float dt;//delta time
	const float nrFPS = FPS;

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


int initEcranPrincipal();


#pragma once

void drawOras(sf::RenderWindow& window)
{
	for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {
		Oras om = itr->second;
		window.draw(itr->second.shape);
	}
	for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {
		Oras om = itr->second;
		window.draw(itr->second.shape);
	}
	for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {
		Oras om = itr->second;
		window.draw(itr->second.shape);
	}

}

void trimitCalator(Oras oras)
{
	//aici calculez distanta dintre orase
	std::map<string,Oras>::iterator item = sigur.begin();
	std::advance(item, rand()/ sigur.size());

	//in item este orasul pe care vrem sa il cotropim
	
	//CalatorOras calator=CalatorOras(oras.pX,oras.pY)
}

int simulareOras() {

input:
	srand(time(0));
	simOras::pauza = true;


	sigur.clear();
	infect.clear();
	vindec.clear();


	int tipOrasClick = 0;//0 neinfectat 1 infectat  2 vindecat
	bool amClick = false;
	std::map<string, Oras>::iterator lastClick;


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
	for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(255, 0, 0, 110));
		window.draw(oras.shape);
	}

	for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(0, 255, 0, 110));
		window.draw(oras.shape);
	}
	for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(0, 0, 255, 110));
		window.draw(oras.shape);
	}



display:
	window.display();

	//aici incepe nebunia dar tot Strafer e mai misto #quierres?
	simOras::deltaTime();

	Oras orastest("craiova", 100, 0, 200, 200);
	orastest.shape.setSize(sf::Vector2f(60, 60));
	orastest.shape.setFillColor(sf::Color(0, 255, 0, 100));
	orastest.shape.setPosition(300, 300);
	sigur.insert({ "1",orastest });
	int frames = 0;
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
					simOras::reset();
					goto input;

				}
				else if (event.key.code == sf::Keyboard::T)
				{
					window.close();
					initEcranPrincipal();

				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					simOras::pauza = !simOras::pauza;

				}

				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}

			default: {
				//ca sa poti sa dai click pe orase
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					bool amOras = false;
					tipOrasClick = -1;

					for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
					{
						//adaug infectat
						std::string key = lastClick->first;
						Oras oras = lastClick->second;
						sigur.erase(key);

						oras.shape.setFillColor(sf::Color(255, 122, 0));
						oras.setInfectati(oras.getInfectati() + 1);

						std::deque<long long> nouaCota;
						nouaCota.push_back(1);
						oras.setCota(nouaCota);

						infect.insert({ key,oras });
						lastClick = infect.find(key);
						tipOrasClick = 1;

						break;
					}
					for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
					{
						//adaug infectat
						lastClick->second.setInfectati(lastClick->second.getInfectati() + 1);
						std::deque<long long> nouaCota = lastClick->second.getNumVindZilnic();
						nouaCota.push_back(1);
						lastClick->second.setCota(nouaCota);
						break;
					}
					for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 2;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
					{
						//adaug un infectat
						lastClick->second.setInfectati(lastClick->second.getInfectati() + 1);
						std::deque<long long> nouaCota = lastClick->second.getNumVindZilnic();
						nouaCota.push_back(1);
						lastClick->second.setCota(nouaCota);
						break;
					}
					break;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					bool amOras = false;
					tipOrasClick = -1;

					for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
					{
						//nu fac nimic
						break;
					}
					for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 1;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
					{
						//sterg infectat
						lastClick->second.setInfectati(lastClick->second.getInfectati() - 1);
						std::deque<long long> nouaCota = lastClick->second.getNumVindZilnic();
						long long val = nouaCota.at(nouaCota.size() - 1);
						nouaCota.pop_back();
						nouaCota.push_back(val);
						lastClick->second.setCota(nouaCota);

						if (lastClick->second.getInfectati() == 0) {
							//trec in alta categorie
							std::string key = lastClick->first;
							Oras oras = lastClick->second;
							infect.erase(lastClick);
							if (oras.getPopulatie() / 2 < oras.getVindecati())
							{
								//am mai multi vindecati decat susceptibili
								oras.shape.setFillColor(sf::Color(0, 0, 255));
								vindec.insert({ key,oras });
								lastClick = vindec.find(key);

								tipOrasClick = 2;
							}
							else {
								//inca e susceptibil
								oras.shape.setFillColor(sf::Color(0, 255, 0));
								sigur.insert({ key,oras });
								lastClick = sigur.find(key);

								tipOrasClick = 0;
							}
						}

						break;
					}
					for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 2;
							amOras = true;
							break;
						}
					}
					if (amOras == true)
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

			simOras::dt = simOras::deltaTime();

			//merg in fiecare oras si ii dau update
			for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {
				Oras oras = itr->second;
				if (frames == 0)
				{
					oras.update();
					if (itr->second.trimit > 0)
					{
						trimitCalator(oras);
						itr->second.trimit = 0;
					}
					itr->second.trimit++;
				}

				itr->second = oras;
			}
		}

		drawOras(window);
		if (amClick == true) {
			//am dat click pe cineva

			simOras::textNpc.setString((lastClick->second).getDenum() + "\n Populatie: " + to_string((lastClick->second).getPopulatie())
				+ "\n Infectati: " + to_string((lastClick->second).getInfectati())
				+ "\n Vindecati: " + to_string((lastClick->second).getVindecati())
				+ "\n Decedati: " + to_string((lastClick->second).getDeced()));
		}
		window.draw(simOras::textNpc);

		window.display();
		frames++;
		if (frames >= FPS)
		{
			frames = 0;
		}
	}
	return 0;
}