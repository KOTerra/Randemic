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
#include "SimulatorLoader.h"

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

ofstream fout("test.txt");

int initEcranPrincipal() {

input:
	srand(time(0));
	ecranAleg::pauza = false;



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
	Buton butonStart(0, "", "Sprites/butonStart.png", "Sprites/HbutonStart.png", 909, 428);
	Buton butonScenariuStanga(-1, "", "Sprites/selectStanga.png", "Sprites/HselectStanga.png", 361, 168);
	Buton butonScenariuDreapta(0, "", "Sprites/selectDreapta.png", "Sprites/HselectDreapta.png", 800, 168);

	Buton butonUpload(4,"", "Sprites/fileBox.png", "Sprites/HfileBox.png", 30, 60);
	sf::Text fileBoxText;
	fileBoxText.setCharacterSize(20); fileBoxText.setFont(font);	fileBoxText.setColor(sf::Color::Black);	fileBoxText.setPosition(55,82);


	int localScenariuCount = 1;
	butonScenariuDreapta.setCounter(&localScenariuCount);
	butonScenariuStanga.setCounter(&localScenariuCount);
textBoxuri:
	Buton butonText1(-5, "Numar Oameni", "Sprites/textBox.png", "Sprites/HtextBox.png", 100, 480);
	Buton butonText2(-5, "Infectabilitate %", "Sprites/textBox.png", "Sprites/HtextBox.png", 300, 480);
	Buton butonText3(-5, "Mortalitate %", "Sprites/textBox.png", "Sprites/HtextBox.png", 500, 480);
	Buton butonText4(-5, "Timp recuperare", "Sprites/textBox.png", "Sprites/HtextBox.png", 500, 600);
	Buton butonText5(-5, "Imunitate grup %", "Sprites/textBox.png", "Sprites/HtextBox.png", 700, 480); //(doar pe scenariul 1,default 0%)
	Buton butonText6(-5, "Timp incubare", "Sprites/textBox.png", "Sprites/HtextBox.png", 300, 600);
	Buton butonText7(-5, "Numar orase", "Sprites/textBox.png", "Sprites/HtextBox.png", 100, 600);
	Buton butonText8(-5, "Timp plecare", "Sprites/textBox.png", "Sprites/HtextBox.png", 300, 600);

	sf::Text textBox1;	textBox1.setPosition(120, 495);	textBox1.setColor(sf::Color::Black); textBox1.setFont(font);
	sf::Text textBox2;	textBox2.setPosition(320, 495);	textBox2.setColor(sf::Color::Black); textBox2.setFont(font);
	sf::Text textBox3;	textBox3.setPosition(520, 495);	textBox3.setColor(sf::Color::Black); textBox3.setFont(font);
	sf::Text textBox4;	textBox4.setPosition(520, 615);	textBox4.setColor(sf::Color::Black); textBox4.setFont(font);
	sf::Text textBox5;	textBox5.setPosition(720, 495);	textBox5.setColor(sf::Color::Black); textBox5.setFont(font);
	sf::Text textBox6;	textBox6.setPosition(320, 615);	textBox6.setColor(sf::Color::Black); textBox6.setFont(font);
	sf::Text textBox7;	textBox7.setPosition(120, 615);	textBox7.setColor(sf::Color::Black); textBox7.setFont(font);
	sf::Text textBox8;	textBox8.setPosition(320, 615);	textBox8.setColor(sf::Color::Black); textBox8.setFont(font);


	butonText1.labelText.setCharacterSize(20);	butonText1.labelText.setFont(font);	butonText1.labelText.setColor(sf::Color::Black);	butonText1.labelText.setPosition(butonText1.pozx, butonText1.pozy - 25);
	butonText2.labelText.setCharacterSize(20);	butonText2.labelText.setFont(font);	butonText2.labelText.setColor(sf::Color::Black);	butonText2.labelText.setPosition(butonText2.pozx, butonText2.pozy - 25);
	butonText3.labelText.setCharacterSize(20);	butonText3.labelText.setFont(font);	butonText3.labelText.setColor(sf::Color::Black);	butonText3.labelText.setPosition(butonText3.pozx, butonText3.pozy - 25);
	butonText4.labelText.setCharacterSize(20);	butonText4.labelText.setFont(font);	butonText4.labelText.setColor(sf::Color::Black);	butonText4.labelText.setPosition(butonText4.pozx, butonText4.pozy - 25);
	butonText5.labelText.setCharacterSize(20);	butonText5.labelText.setFont(font);	butonText5.labelText.setColor(sf::Color::Black);	butonText5.labelText.setPosition(butonText5.pozx, butonText5.pozy - 25);
	butonText6.labelText.setCharacterSize(20);	butonText6.labelText.setFont(font);	butonText6.labelText.setColor(sf::Color::Black);	butonText6.labelText.setPosition(butonText6.pozx, butonText6.pozy - 25);
	butonText7.labelText.setCharacterSize(20);	butonText7.labelText.setFont(font);	butonText7.labelText.setColor(sf::Color::Black);	butonText7.labelText.setPosition(butonText7.pozx, butonText7.pozy - 25);
	butonText8.labelText.setCharacterSize(20);	butonText8.labelText.setFont(font);	butonText8.labelText.setColor(sf::Color::Black);	butonText8.labelText.setPosition(butonText8.pozx, butonText8.pozy - 25);


display:
	window.display();

	//aici incepe nebunia, dar tot Strafer e mai misto 
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

			window.draw(butonUpload.butonSprite);
			butonUpload.clic(event);
			butonUpload.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			window.draw(butonScenariuStanga.butonSprite);
			butonScenariuStanga.clic(event);
			butonScenariuStanga.update(sf::Vector2f(sf::Mouse::getPosition(window)));

			window.draw(butonScenariuDreapta.butonSprite);
			butonScenariuDreapta.clic(event);
			butonScenariuDreapta.update(sf::Vector2f(sf::Mouse::getPosition(window)));


			if (localScenariuCount > 2) {
				localScenariuCount -= (localScenariuCount - 2);
			}
			else if (localScenariuCount < 1) {
				localScenariuCount = 1;
			}



			butonStart.tipButon = localScenariuCount;
			bool scenariu1este = false;
			bool scenariu2este = false;

			switch (localScenariuCount) {
			case 1: {//niste convertiri ciudatele ca nu mergea stoi()
				scenariu1este = true;
				scenariu2este = false;
				std::string nN = butonText1.getText();
				stringstream strnN(nN);
				strnN >> nrNpc;

				std::string inf = butonText2.getText();
				stringstream strinf(inf);
				strinf >> infectabilitate;

				std::string mrt = butonText3.getText();
				stringstream strmrt(mrt);
				strmrt >> mortalitate;

				std::string rec = butonText4.getText();
				stringstream strrec(rec);
				strrec >> timpRecuperare;
				if (!rec._Equal(""))
				{
					timpRecuperare *= 60;
				}

				std::string inc = butonText6.getText();
				stringstream strinc(inc);
				strinc >> timpIncubare;
				if (!inc._Equal(""))
				{
					timpIncubare *= 60;
				}

				std::string imn = butonText5.getText();
				stringstream strimn(imn);
				strimn >> imunitateGrup;



				break;
			}

			case 2: {
				//pt oras
				scenariu1este = false;
				scenariu2este = true;
				std::string nN = butonText1.getText();
				stringstream strnN(nN);
				strnN >> nrNpc;

				std::string ora = butonText7.getText();
				stringstream strora(ora);
				strora >> nrOrase;

				std::string inf = butonText2.getText();
				stringstream strinf(inf);
				strinf >> infectabilitate;

				std::string mrt = butonText3.getText();
				stringstream strmrt(mrt);
				strmrt >> mortalitate;
				if (mortalitate > 100)
				{
					//pentru andy care omoara 2 oameni dintr-o infectare
					mortalitate = 100;
				}

				std::string rec = butonText4.getText();
				stringstream strrec(rec);
				strrec >> timpRecuperare;
				if (!rec._Equal(""))
				{
					timpRecuperare *= 60;
				}

				std::string inc = butonText6.getText();
				stringstream strinc(inc);
				strinc >> timpIncubare;
				if (!inc._Equal(""))
				{
					timpIncubare *= 60;
				}

				std::string imn = butonText5.getText();
				stringstream strimn(imn);
				strimn >> imunitateGrup;

				std::string cal = butonText8.getText();
				stringstream strcal(cal);
				strcal >> timpCalator;



				break;
			}


			}

			if (fisier::fisierIncarcat == true) {
				//fisier::fisierIncarcat = false;
				std::string fis = fisier::fisierFolosit;
				fout << fis<<"\n";
			}
			
			butonText1.renderTextBox(window, event);	window.draw(butonText1.labelText);
			butonText2.renderTextBox(window, event);	window.draw(butonText2.labelText);
			butonText3.renderTextBox(window, event);	window.draw(butonText3.labelText);
			butonText4.renderTextBox(window, event);	window.draw(butonText4.labelText);
			butonText5.renderTextBox(window, event);	window.draw(butonText5.labelText);
			

			textBox1.setString(butonText1.getText());	window.draw(textBox1);
			textBox2.setString(butonText2.getText());	window.draw(textBox2);
			textBox3.setString(butonText3.getText());	window.draw(textBox3);
			textBox4.setString(butonText4.getText());	window.draw(textBox4);
			textBox5.setString(butonText5.getText());	window.draw(textBox5);
			fileBoxText.setString(getFisierNume(fisier::fisierFolosit));  window.draw(fileBoxText);

			if (scenariu1este == true) {
				butonText6.renderTextBox(window, event);	window.draw(butonText6.labelText);
				textBox6.setString(butonText6.getText());	window.draw(textBox6);
				window.draw(preview1);
			}
			else if (scenariu2este==true) {
				
				butonText7.renderTextBox(window, event);	window.draw(butonText7.labelText);
				textBox7.setString(butonText7.getText());	window.draw(textBox7);

				butonText8.renderTextBox(window, event);	window.draw(butonText8.labelText);
				textBox8.setString(butonText8.getText());	window.draw(textBox8);

				window.draw(preview2);
			}
			//butoane

			window.display();



		}



	}
	return 0;
}