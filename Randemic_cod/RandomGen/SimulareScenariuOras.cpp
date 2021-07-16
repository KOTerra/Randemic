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

std::map<string,Oras> infect;
std::map<string,Oras> sigur;
std::map<string,Oras> vindec;


int initEcranPrincipal();


#pragma once


int simulareOras() {

input:
	srand(time(0));
	simOras::pauza = false;

	

	

	int tipOrasClick = 0;//0 infectat 1 neinfectat 2 vindecat
	bool amClick = false;
	std::map<string,Oras>::iterator lastClick;


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


adaugOameni:
	//desenam orasele
	for (std::map<string,Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(255, 0, 0));
		window.draw(oras.shape);
	}

	for (std::map<string, Oras>::iterator itr = sigur.begin(); itr != sigur.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(0, 255, 0));
		window.draw(oras.shape);
	}
	for (std::map<string, Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

		Oras oras = itr->second;
		oras.shape.setFillColor(sf::Color(0, 0, 255));
		window.draw(oras.shape);
	}



display:
	window.display();

	//aici incepe nebunia dar tot Strafer e mai misto #quierres?
	simOras::deltaTime();
	while (window.isOpen())
	{
		sf::Event event;
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
					for (std::map<string, Oras>::iterator itr = infect.begin(); itr != infect.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window);
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Oras oras = itr->second;

						if (oras.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
							tipOrasClick = 0;
							amOras = true;
							break;
						}			   
					}
					if (amOras == true)
					{
						break;
					}
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
						break;
					}
					for (std::map<string,Oras>::iterator itr = vindec.begin(); itr != vindec.end(); itr++) {

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
				}
				break;


			}


			}

		}
		if (simOras::pauza == false) {
			//ruleaza
			window.clear();
			window.draw(backSprite);//fundalul
			simOras::dt = simOras::deltaTime();

            //merg in fiecare oras si ii dau update
			for (std::map<string, Oras>::iterator itr = infect.begin(); itr != vindec.end(); itr++) {
				Oras oras=itr->second;
				oras.update();
				itr->second = oras;
			}

			if (amClick == true) {
				//am dat click pe cineva
				
				simOras::textNpc.setString((lastClick->second).getDenum() + "\n Populatie: " + to_string((lastClick->second).getPopulatie())
					+ "\n Infectati: " + to_string((lastClick->second).getInfectati())
					+ "\n Decedati: " + to_string((lastClick->second).getDeced()));
			}
			window.draw(simOras::textNpc);
			window.display();

		}


	}
	return 0;
}