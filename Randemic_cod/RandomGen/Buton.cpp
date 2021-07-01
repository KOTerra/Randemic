#include "Buton.h"
#include "HeaderSimulari.h"

Buton::Buton(int tip, std::string Textura, float x, float y) {
	this->tipButon = tip;
	this->butonImg.loadFromFile(Textura);
	this->butonSprite.setTexture(this->butonImg);
	this->butonSprite.setPosition(sf::Vector2f(x, y));
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
		case(0): {
			//sageti
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
		case(5): {

			break;
		}


		}
	}
}

void Buton::render(sf::RenderTarget* target) {
	target->draw(this->butonSprite);
}