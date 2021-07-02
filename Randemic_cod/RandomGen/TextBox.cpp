#include "TextBox.h"
#include <sstream>
#include <cstdlib>

#include <include/SFML/Window.hpp>
#include <include/SFML/System.hpp>
#include <include/SFML/Graphics.hpp>

TextBox::TextBox(std::string Textura, float x, float y,bool sel) {
	this->textInBox.setCharacterSize(this->size);
	this->font.loadFromFile("Fonts/KarmaFuture.ttf");
	this->textInBox.setFont(font);
	this->textInBox.setColor(color);

	this->textBoxImg.loadFromFile(Textura);
	this->textBoxSprite.setTexture(this->textBoxImg);
	this->textBoxSprite.setPosition(x, y);

	if (sel == true) {
		textInBox.setString("_");
	}
	else {
		textInBox.setString("");
	}
}

TextBox::~TextBox() {
}


void TextBox::inputLogic(int charTyped) {
	if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != RESET_KEY) {
		text << static_cast<char>(charTyped);

	}
	else if(charTyped==DELETE_KEY){

		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textInBox.setString(text.str() + "_");
}


void TextBox::deleteLastChar() {
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length(); i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;
	textInBox.setString(text.str());



}


void TextBox::setSelected(bool sel) {
	this->selected = sel;
	if (sel==false) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++) {
			newT += t[i];
		}
		textInBox.setString(newT);

	}

}

std::string TextBox::getText() {
	return text.str();
}

void TextBox::drawIn(sf::RenderWindow& window) {
	window.draw(textInBox);
}

void TextBox::typedOn(sf::Event input) {
	if (selected == true) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			inputLogic(charTyped);
		}
	}
		

}

void TextBox::update(const sf::Vector2f mousePos) {
	this->selected = false;
	if (this->textBoxSprite.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->selected = true;

		}
	}
	else{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->selected = false;
		}
	}
}


void TextBox::setFont(sf::Font& font) {
	textInBox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos) {
	textInBox.setPosition(pos);
}