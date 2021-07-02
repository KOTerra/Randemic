#include "Buton.h"
#include "HeaderSimulari.h"

Buton::Buton(int tip, std::string Textura, float x, float y) {
	this->tipButon = tip;
	this->butonImg.loadFromFile(Textura);
	this->butonSprite.setTexture(this->butonImg);
	this->butonSprite.setPosition(sf::Vector2f(x, y));
	this->pozx = x;
	this->pozy = y;
}


Buton::~Buton() {

}



void Buton::update(const sf::Vector2f mousePos) {
	this->apasat = false;
	if (this->butonSprite.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			this->apasat = true;
			
		}
	}
}

void Buton::clic() {
	if (this->apasat == true) {
		switch (this->tipButon) {
		case(-1): {
			//sageti stanga
			
			counter -= 1;
			break;
		}
		case(0): {
			//sageti dreapta
			
			counter += 1;
			break;
		}
		case(1): {
			simulare1();


			break;
		}
		case(2): {

			break;
		}
		case(3): {

			break;
		}
		case(4): {

			break;
		}
		case(-5): {
			//text input
			
					if (event.type == sf::Event::TextEntered)
					{
							textInput += event.text.unicode;
					}
			
			break;
		}


		}
	}
}

void Buton::render(sf::RenderTarget* target) {
	target->draw(this->butonSprite);
}