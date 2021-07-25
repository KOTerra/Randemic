#pragma once
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
#include "HeaderVirus.h"
#include "Buton.h"
#include "TextBox.h"

//.
int initEcranPrincipal();


namespace ecranStart {
	
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

	const float nrFPS = FPS;


}

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


int main() {

input:
	srand(time(0));


window:
	//aici bagam window-ul
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Randemic", sf::Style::Default);
	window.setFramerateLimit(ecranStart::nrFPS);


background:
	//fundalul
	sf::Texture backTexture;
	backTexture.loadFromFile("Sprites/fundalTutorial.png");
	sf::Sprite backSprite(backTexture);
	window.clear();
	window.draw(backSprite);

font_text:
	sf::Font font;
	font.loadFromFile("Fonts/KarmaFuture.ttf");

butoane:
	Buton butonStart(3, "", "Sprites/butonStart.png", "Sprites/HbutonStart.png", 468, 459);


display:
	window.display();

	//aici incepe nebunia, dar tot Strafer e mai misto #quierres?
	bool simOpen;
	simOpen = false;


test:

	while (window.isOpen())
	{

		if (simOpen == true) {
			window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			//eventuri

			switch (event.type) {
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return 0;
				}
				else if (event.key.code == sf::Keyboard::F1)
				{
					ecranStart::reset();
					goto input;

				}

				break;
			}
			case sf::Event::Closed: {
				window.close();
				return 0;
			}
			case sf::Event::LostFocus: {
				ecranStart::pause();
				break;
			}
			case sf::Event::GainedFocus: {
				ecranStart::resume();
				break;
			}

			}

		}
		if (ecranStart::pauza == false) {

			window.clear();

			window.draw(backSprite);
			ecranStart::dt = ecranStart::deltaTime();
			//fundalul



			//butoane

			window.draw(butonStart.butonSprite);
			if (butonStart.apasat == true) {
				window.close();
			}
			butonStart.clic(event);
			butonStart.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			window.display();
		}



	}
	return 0;
}