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
	/*void logo() {
		//functie de logo ca sa fie frumos
		cout << R"( 
 ____                             __                                         
/\  _`\                          /\ \                          __            
\ \ \L\ \       __       ___     \_\ \      __     ___ ___    /\_\     ___   
 \ \ ,  /     /'__`\   /' _ `\   /'_` \   /'__`\ /' __` __`\  \/\ \   /'___\ 
  \ \ \\ \   /\ \L\.\_ /\ \/\ \ /\ \L\ \ /\  __/ /\ \/\ \/\ \  \ \ \ /\ \__/ 
   \ \_\ \_\ \ \__/.\_\\ \_\ \_\\ \___,_\\ \____\\ \_\ \_\ \_\  \ \_\\ \____\
    \/_/\/ /  \/__/\/_/ \/_/\/_/ \/__,_ / \/____/ \/_/\/_/\/_/   \/_/ \/____/
_____________________________________________________________________________
Pentru a vedea detalii despre o persoana da CLICK pe aceasta.
Pentru a opri simularea apasa ESC.
Pentru a reseta simularea apasa R.


Introdu in ordine infectabilitatea bolii(default 8), timpul de recuperare al bolii(in frameuri_default 1000)
si mortalitatea(in procente_default 20):                                                                           
                                                                            
)";
	}*/
	bool pauza;
	void pause() { pauza = true; }
	void resume() { pauza = false; }
	void reset() {
		//chestii care se reseteaza
		counterInfectati = 0;
		counterMorti = 0;
		counterVii = 0;
		counterVindecati = 0;

	}

}

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

#pragma warning(suppress : 4996)

std::map<string, OmClass> oameni;//oamenii creati in header
sf::Text textNpc;//textul pt fiecare NPC
sf::Text textCounter;//numarul text
sf::Clock ceas;
float dt;//delta time

float deltaTime() {

	return ceas.restart().asSeconds();//pt miscare in functie de frameuri

}
void miscareNpc(std::map<string, OmClass>::iterator itr) {
	//functie de miscare

	OmClass om = itr->second;
	if (om.stare.compare("mort") == 0) {
		return;//daca e mort nu se misca
	}

	//float dt = deltaTime();

	//aicea ne miscam(putin dans)
	sf::Vector2f vec1 = om.misc;
	vec1.x = vec1.x*dt;
	vec1.y = vec1.y*dt;

	om.shape.move(vec1);

	auto pozitie = om.shape.getPosition();
	om.pX = pozitie.x+razaShape;
	om.pY = pozitie.y+razaShape;

	if (om.pX >= 939.f || om.pX <= 37.f) {
		//om.shape.setPosition(om.pX-om.pX*20/100, om.pY);
		
		om.misc.x = om.misc.x * (-1);
	}

	if (om.pY >= 682.f || om.pY <= 37.f) {
		//om.shape.setPosition(om.pX, om.pY - om.pY * 20 / 100);
		om.misc.y = om.misc.y* (-1);
	}



	
	//avem hit-detection diferit in functie de infectati
	if (om.stare.compare("infectat") == 0 && counterInfectati < (counterVii - counterInfectati))//daca e infectat 
	{

		for (std::map<string, OmClass>::iterator col = oameni.begin(); col != oameni.end(); col++) {

			if (itr != col && col->second.stare == "sanatos") {

				//cealalta coliziune
				//
				//folosim formula AABB pt hit detection
				int raza1 = stoi(om.sociabilitate) + razaShape - 3, x1 = om.pX, y1 = om.pY;
				int raza2 = stoi(col->second.sociabilitate) + razaShape - 3, x2 = col->second.pX, y2 = col->second.pY;

				int dx = x1 - x2;
				int dy = y1 - y2;
				int distance = sqrt(dx * dx + dy * dy);

				int probInfectie = rand() % 100 + 1;
				if (distance < raza1 + raza2 && probInfectie <= infectabilitate) {
					// coliziune detectata!
					col->second.shape.setFillColor(sf::Color(255, 0, 0));
					col->second.stare = "infectat";
					counterInfectati++;

					col->second.timpInfectare = 0;

					textCounter.setString("In viata: " + to_string(counterVii) +
						"\nInfectati: " + to_string(counterInfectati) +
						"\nVindecati: " + to_string(counterVindecati) +
						"\nMorti: " + to_string(counterMorti));
				}

			}


		}

	}
	else if (om.stare.compare("sanatos") == 0) {
		//cautam de la neinfectati spre infectati

		for (std::map<string, OmClass>::iterator col = oameni.begin(); col != oameni.end(); col++) {

			if (itr != col && col->second.stare.compare("infectat") == 0) {

				//cealalta coliziune

				//
				int raza1 = stoi(om.sociabilitate) + razaShape - 3, x1 = om.pX, y1 = om.pY;
				int raza2 = stoi(col->second.sociabilitate) + razaShape - 3, x2 = col->second.pX, y2 = col->second.pY;

				int dx = x1 - x2;
				int dy = y1 - y2;
				int distance = sqrt(dx * dx + dy * dy);

				int probInfectie = rand() % 100 + 1;
				if (distance < raza1 + raza2 && probInfectie <= infectabilitate) {
					// coliziune detectata!
					om.shape.setFillColor(sf::Color(255, 0, 0));
					om.stare = "infectat";
					counterInfectati++;

					om.timpInfectare = 0;

					textCounter.setString("In viata: " + to_string(counterVii) +
						"\nInfectati: " + to_string(counterInfectati) +
						"\nVindecati: " + to_string(counterVindecati) +
						"\nMorti: " + to_string(counterMorti));

					break;
				}


			}

		}

	}
	oameni[itr->first] = om;

}


#pragma once


int simulare1(){

input:
	srand(time(0));
	sim1::pauza= false;

	int nrNpcuri;
	//logo();
	//cin >> infectabilitate >> timpRecuperare >> mortalitate;
	//cout << "Introdu numarul de persoane:";
	infectabilitate = 8;
	timpRecuperare = 1000;
	mortalitate = 20;
	//cin>> nrNpcuri;
	nrNpcuri = 100;
	counterVii = nrNpcuri;

	oameni.clear();
	oameni = simulare(nrNpcuri);
	bool amClick = false;
	std::map<string, OmClass>::iterator lastClick;


window:
	//aici bagam window-ul
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Randemic", sf::Style::Default);
	window.setFramerateLimit(FPS);


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
	//desenam infectatii
	for (std::map<string, OmClass>::iterator itr = oameni.begin(); itr != oameni.end(); itr++) {

		OmClass om = itr->second;


		if (itr==oameni.begin()) {
			//cout << itr->first;
			om.shape.setFillColor(sf::Color(255, 0, 0));
			om.stare = "infectat";
			counterInfectati++;
			om.shape.setRotation(rand() % 90);
			textCounter.setString("In viata: " + to_string(counterVii) +
				"\nInfectati: " + to_string(counterInfectati) +
				"\nVindecati: " + to_string(counterVindecati) +
				"\nMorti: " + to_string(counterMorti));
			om.timpInfectare = 0;
			oameni[itr->first] = om;
			
		}
		
		window.draw(om.shape);
	}



display:
	window.display();

	//aici incepe nebunia dar tot Strafer e mai misto #quierres?
	
	


	deltaTime();
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
					sim1::reset();
					goto input;

				}

				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::LostFocus: {
				sim1::pause();
				break;
			}
			case sf::Event::GainedFocus: {
				sim1::resume();
				break;
			}
			default: {
				//ca sa poti sa dai click pe oamenii astia simulati
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					
					for (std::map<string, OmClass>::iterator itr = oameni.begin(); itr != oameni.end(); itr++) {

						auto mouse_pos = sf::Mouse::getPosition(window); 
						auto translated_pos = window.mapPixelToCoords(mouse_pos); 
						OmClass om = itr->second;

						if (om.shape.getGlobalBounds().contains(translated_pos)) {
							amClick = true;
							lastClick = itr;
						}


					}
				}
				break;


			  }


			}

		}
	    if (sim1::pauza == false) {
			//ruleaza
			window.clear();
			window.draw(backSprite);//fundalul
			dt = deltaTime();
			for (std::map<string, OmClass>::iterator itr = oameni.begin(); itr != oameni.end(); itr++) {
				//desenez npc-urile pe ecran si calculam valorile
				if (itr->second.stare.compare("infectat") == 0) {
					itr->second.timpInfectare++;
					if (itr->second.timpInfectare == timpRecuperare) {
						int procSupravietuire = rand() % 100;
						if (procSupravietuire <= mortalitate)
						{
							//moare individul
							itr->second.stare = "mort";
							itr->second.shape.setFillColor(sf::Color(0, 0, 0));
							counterMorti++;
							counterVii--;
						}
						else
						{
							itr->second.stare = "vindecat";
							itr->second.shape.setFillColor(sf::Color(0, 0, 255));
							counterVindecati++;
							itr->second.shape.setRotation(rand() % 90);
						}
						textCounter.setString("In viata: " + to_string(counterVii) +
							"\nInfectati: " + to_string(counterInfectati) +
							"\nVindecati: " + to_string(counterVindecati) +
							"\nMorti: " + to_string(counterMorti));
					}

				}
				
				miscareNpc(itr);
				window.draw(itr->second.shape);
				window.draw(textCounter);
			}
			if (amClick == true) {
				//am dat click pe cineva
				textNpc.setString(lastClick->second.prenume + "\n Sex: " + lastClick->second.sex
					+ "\n Varsta: " + lastClick->second.varsta
					+ "\n Inaltime: " + lastClick->second.inaltime
					+ "\n Stare: " + lastClick->second.stare);
			}
			window.draw(textNpc);
			window.display();
			
		}


	}
	return 0;
}