#pragma once
#include <sstream>
#include <cstdlib>

#include <include/SFML/Window.hpp>
#include <include/SFML/System.hpp>
#include <include/SFML/Graphics.hpp>


class Buton {
private:
	bool apasat;

	sf::RectangleShape shape;
	sf::Texture butonImg;
	

	int tipButon;

public:
	sf::Sprite butonSprite;
	Buton(int tip, std::string Textura, float x, float y);
	~Buton();

	void clic();
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};