#ifndef OmClass_HEADER
#define OmClass_HEADER

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class OmClass {
public:
	float pX, pY;//pozitia omului
	std::string prenume, inaltime, sociabilitate, varsta, sex;//identificatori
	mutable sf::CircleShape shape;//reprezentarea vizuala a omului
	//float speedY, speedX;//viteza individului pe cele 2 axe
	sf::Vector2f misc;
	std::string stare;//0 sanatos 
				//1 infectat
				//2	vindecat
				//3 mort
	long timpInfectare;//timpul in care e infectat


};


#endif