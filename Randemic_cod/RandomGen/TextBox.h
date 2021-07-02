#pragma once

#include <sstream>
#include <cstdlib>

#include <include/SFML/Window.hpp>
#include <include/SFML/System.hpp>
#include <include/SFML/Graphics.hpp>

#define DELETE_KEY 8  //backspace
#define ESCAPE_KEY 27 //esc
#define RESET_KEY 359 //F1

class TextBox {
private :
	sf::Texture textBoxImg;
	bool selected = false;


	void inputLogic(int charTyped);
	void deleteLastChar();


public:

	TextBox(std::string Textura, float x, float y,bool sel);
	~TextBox();

	sf::Sprite textBoxSprite;

	int size;
	sf::Font font;
	
	sf::Color color=sf::Color::Black;
	sf::Text textInBox;
	std::ostringstream text;




	void setSelected(bool sel);
	std::string getText();
	void drawIn(sf::RenderWindow& window);
	void typedOn(sf::Event input);
	void update(const sf::Vector2f mousePos);
};