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

namespace ecranAleg {
	

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
	int nrNpcSource;
	int infectabilitateSource;
	int mortalitateSource;
	
}

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


int initEcranPrincipal() {

input:
	srand(time(0));
	ecranAleg::pauza = false;
	
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
	window.setFramerateLimit(ecranAleg::nrFPS);


background:
	//fundalul
	sf::Texture backTexture;
	backTexture.loadFromFile("Sprites/fundalStart.png");
	sf::Sprite backSprite(backTexture);
	window.clear();
	window.draw(backSprite);

previews:
	sf::Texture preview1texture;	preview1texture.loadFromFile("Sprites/previewScenariu1.png");
	sf::Texture preview2texture;	preview2texture.loadFromFile("Sprites/previewScenariu2.png");

	sf::Sprite preview1;	preview1.setTexture(preview1texture);	preview1.setPosition(480, 160); 
	sf::Sprite preview2;	preview2.setTexture(preview2texture);	preview2.setPosition(480, 160);


font_text:
	sf::Font font;
	font.loadFromFile("Fonts/KarmaFuture.ttf");

butoane:
	Buton butonStart(0,"", "Sprites/butonStart.png", 920, 390);
	Buton butonScenariuStanga(-1, "", "Sprites/selectStanga.png", 390, 200);
	Buton butonScenariuDreapta(0, "", "Sprites/selectDreapta.png", 805, 200);

textBoxuri:
	Buton butonText1(-5, "Numar Oameni",		"Sprites/textBox.png", 100, 480);
	Buton butonText2(-5, "Infectabilitate %",	"Sprites/textBox.png", 300, 480);
	Buton butonText3(-5, "Mortalitate %",		"Sprites/textBox.png", 500, 480);
	Buton butonText4(-5, "Timp de recuperare",	"Sprites/textBox.png", 100, 600);
	Buton butonText5(-5, "Imunitate grup", "Sprites/textBox.png", 500, 600); //(doar pe scenariul 1,default 0%)

	sf::Text textBox1;	textBox1.setPosition(120, 495);	textBox1.setColor(sf::Color::Black); textBox1.setFont(font);
	sf::Text textBox2;	textBox2.setPosition(320, 495);	textBox2.setColor(sf::Color::Black); textBox2.setFont(font);
	sf::Text textBox3;	textBox3.setPosition(520, 495);	textBox3.setColor(sf::Color::Black); textBox3.setFont(font);
	sf::Text textBox4;	textBox4.setPosition(120, 615);	textBox4.setColor(sf::Color::Black); textBox4.setFont(font);
	sf::Text textBox5;	textBox5.setPosition(520, 615);	textBox5.setColor(sf::Color::Black); textBox5.setFont(font);


	butonText1.labelText.setCharacterSize(20);	butonText1.labelText.setFont(font);	butonText1.labelText.setColor(sf::Color::Black);	butonText1.labelText.setPosition(butonText1.pozx, butonText1.pozy - 25);
	butonText2.labelText.setCharacterSize(20);	butonText2.labelText.setFont(font);	butonText2.labelText.setColor(sf::Color::Black);	butonText2.labelText.setPosition(butonText2.pozx, butonText2.pozy - 25);
	butonText3.labelText.setCharacterSize(20);	butonText3.labelText.setFont(font);	butonText3.labelText.setColor(sf::Color::Black);	butonText3.labelText.setPosition(butonText3.pozx, butonText3.pozy - 25);
	butonText4.labelText.setCharacterSize(20);	butonText4.labelText.setFont(font);	butonText4.labelText.setColor(sf::Color::Black);	butonText4.labelText.setPosition(butonText4.pozx, butonText4.pozy - 25);
	butonText5.labelText.setCharacterSize(20);	butonText5.labelText.setFont(font);	butonText5.labelText.setColor(sf::Color::Black);	butonText5.labelText.setPosition(butonText5.pozx, butonText5.pozy - 25);


display:
	window.display();

	//aici incepe nebunia, dar tot Strafer e mai misto #quierres?
	bool simOpen;
	simOpen = false;


test:
	


	ecranAleg::deltaTime();
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
					ecranAleg::reset();
					goto input;
				}

				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::LostFocus: {
				ecranAleg::pause();
				break;
			}
			case sf::Event::GainedFocus: {
				ecranAleg::resume();
				break;
			}

			}

		}
		if (ecranAleg::pauza == false) {
			//ruleaza
			window.clear();

			//fundalul
			window.draw(backSprite);
			ecranAleg::dt = ecranAleg::deltaTime();
			//fundalul



			//butoane

			window.draw(butonStart.butonSprite);
			if (butonStart.apasat == true) {
				window.close();
			}
			butonStart.clic(event);
			butonStart.update(sf::Vector2f(sf::Mouse::getPosition(window)));


			window.draw(butonScenariuStanga.butonSprite);
			butonScenariuStanga.clic(event);
			butonScenariuStanga.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			window.draw(butonScenariuDreapta.butonSprite);
			butonScenariuDreapta.clic(event);
			butonScenariuDreapta.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			int localScenariuCount=1;

			//if (localScenariuCount < 3 && localScenariuCount>0) {
				localScenariuCount = butonScenariuDreapta.counter + butonScenariuStanga.counter;
			//}
			 if(localScenariuCount>2) {
				localScenariuCount -= (localScenariuCount - 2);
			 }
			 else if (localScenariuCount < 1) {
				 localScenariuCount = 1;
			 }

		/*	if (localScenariuCount < 1) {
				localScenariuCount = 1;
			}
			if (localScenariuCount > 2) {
				localScenariuCount = 2;
			}*/

			butonStart.tipButon = localScenariuCount;
			bool scenariu1este = false;

			switch (localScenariuCount) {
			case 1: {//niste convertiri super ciudatele ca nu mergea stoi()
				scenariu1este = true;
				std::string nN = butonText1.getText();
				stringstream strnN(nN);
				strnN>>nrNpc;

				std::string inf = butonText2.getText();
				stringstream strinf(inf);
				strinf>>infectabilitate;

				std::string mrt = butonText3.getText();
				stringstream strmrt(mrt);
				strmrt>>mortalitate;

				std::string rec = butonText4.getText();
				stringstream strrec(rec);
				strrec >>timpRecuperare;

				std::string imn = butonText5.getText();
				stringstream strimn(imn);
				strimn >> imunitateGrup;
				
				break;
			}

			case 2: {
			//pt oras
				scenariu1este = false;
			}
				  

			}

			


			butonText1.renderTextBox(window, event);	window.draw(butonText1.labelText);
			butonText2.renderTextBox(window, event);	window.draw(butonText2.labelText);
			butonText3.renderTextBox(window, event);	window.draw(butonText3.labelText);
			butonText4.renderTextBox(window, event);	window.draw(butonText4.labelText);

			textBox1.setString(butonText1.getText());	window.draw(textBox1);
			textBox2.setString(butonText2.getText());	window.draw(textBox2);
			textBox3.setString(butonText3.getText());	window.draw(textBox3);
			textBox4.setString(butonText4.getText());	window.draw(textBox4);

			if (scenariu1este == true) {
				butonText5.renderTextBox(window, event);	window.draw(butonText5.labelText);
				textBox5.setString(butonText5.getText());	window.draw(textBox5);
			
				window.draw(preview1);
			}
			else if (localScenariuCount == 2) {
				window.draw(preview2);
			}
			//butoane

			window.display();



		}



	}
	return 0;
}