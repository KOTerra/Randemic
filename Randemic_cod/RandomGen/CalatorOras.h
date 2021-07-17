#pragma once
#include <include\SFML\System\Vector2.hpp>
#include <include\SFML\Graphics\CircleShape.hpp>
#include <map>
#include <string>
#include "Oras.h"
class CalatorOras
{
public:
	float pX, pY;//pozitia omului
	mutable sf::CircleShape shape;//reprezentarea vizuala a omului
	//float speedY, speedX;//viteza individului pe cele 2 axe
	sf::Vector2f misc;
	std::map<std::string, Oras>::iterator tinta;
	long timpInfectare;//timpul in care e infectat

	CalatorOras(float pX, float pY, sf::Vector2f directie, std::map<std::string, Oras>::iterator tinta);
	~CalatorOras();

	bool isTouchingOras(int R, int X1, int Y1, int X2, int Y2);
	void move(float dt);
private:
	const int razaShape = 5;
};

