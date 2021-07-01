#include <iostream>
#include <fstream>



//sfml
#include <include/SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <map>

//header
#include "HeaderSimulari.h"

int simulare1();

namespace start {
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

	}
	sf::Text textSimulare1;//text simulare
	sf::Clock ceas;
	float dt;//delta time

	float deltaTime() {

		return ceas.restart().asSeconds();//pt miscare in functie de frameuri

	}

}

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

#pragma warning(suppress : 4996)





#pragma once


int main() {

input:
	srand(time(0));
	start::pauza = false;

	int nrNpcuri;
	//logo();
	//cin >> infectabilitate >> timpRecuperare >> mortalitate;
	//cout << "Introdu numarul de persoane:";
	/*infectabilitate = 8;
	timpRecuperare = 1000;
	mortalitate = 20;
	//cin>> nrNpcuri;
	nrNpcuri = 100;
	counterVii = nrNpcuri;

	bool amClick = false;*/
	


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



	


display:
	window.display();

	//aici incepe nebunia dar tot Strafer e mai misto #quierres?

	start::deltaTime();
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
					start::reset();
					goto input;

				}

				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::LostFocus: {
				start::pause();
				break;
			}
			case sf::Event::GainedFocus: {
				start::resume();
				break;
			}
			default: {
				//ca sa poti sa dai click pe oamenii astia simulati
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
					simulare1();
					return 0;
				}
				break;


			}


			}

		}
		if (start::pauza == false) {
			//ruleaza
			window.clear();
			window.draw(backSprite);//fundalul
			start::dt = start::deltaTime();
			
			window.display();

		}


	}
	return 0;
}