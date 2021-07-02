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
#include "Buton.h"
#include "TextBox.h"

//.

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
	backTexture.loadFromFile("Sprites/fundalStart.png");
	sf::Sprite backSprite(backTexture);
	window.clear();
	window.draw(backSprite);

font_text:
	sf::Font font;
	font.loadFromFile("Fonts/KarmaFuture.ttf");

butoane:
	Buton butonStart(0,"Sprites/butonStart.png",920,390);
	Buton butonScenariuStanga(-1, "Sprites/selectStanga.png", 390, 200);
	Buton butonScenariuDreapta(0, "Sprites/selectDreapta.png", 805, 200);

textBoxuri:
	TextBox textBox1("Sprites/textBox.png",300,600,false);
	textBox1.setFont(font);
	textBox1.setPosition({ 300,600 });

display:
	window.display();

	//aici incepe nebunia, dar tot Strafer e mai misto #quierres?
	bool simOpen;
	simOpen = false;
	

test:
	sf::Text testText;
	testText.setPosition(100, 100);
	testText.setColor(sf::Color::Red);
	testText.setFont(font);


	start::deltaTime();
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
				}
				else if (event.key.code == sf::Keyboard::F1)
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
			case sf::Event::TextEntered: {
				textBox1.typedOn(event);
				break;
			}
			/*default: {
				//ca sa poti sa dai click pe oamenii astia simulati
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
					simulare1();
					return 0;
				}
				break;


			}*/


			}

		}
		if (start::pauza == false) {
			//ruleaza
			window.clear();

			//fundalul
			window.draw(backSprite);
			start::dt = start::deltaTime();
			//fundalul

			//butoane

			window.draw(butonStart.butonSprite);
			if (butonStart.apasat == true) {
				window.close();
			}
			butonStart.clic();
			butonStart.update(sf::Vector2f(sf::Mouse::getPosition(window)));


			window.draw(butonScenariuStanga.butonSprite);
			butonScenariuStanga.clic();
			butonScenariuStanga.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			window.draw(butonScenariuDreapta.butonSprite);
			butonScenariuDreapta.clic();
			butonScenariuDreapta.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			int localScenariuCount = butonScenariuDreapta.counter + butonScenariuStanga.counter;

			if (localScenariuCount < 1) {
				localScenariuCount = 1;
			}
			if (localScenariuCount > 1) {
				localScenariuCount = 1;
			}

			butonStart.tipButon = localScenariuCount;



			//window.draw(textBox1.textBoxSprite);
			//window.draw(textBox1.textInBox);
			textBox1.drawIn(window);
			//textBox1.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			testText.setString(textBox1.getText());
			window.draw(testText);

			//butoane
			window.display();



		}
		


	}
	return 0;
}