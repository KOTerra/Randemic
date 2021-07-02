
#include <sstream>
#include <cstdlib>

#include <include/SFML/Window.hpp>
#include <include/SFML/System.hpp>
#include <include/SFML/Graphics.hpp>


class Buton {
private:
	
	
	sf::RectangleShape shape;
	sf::Texture butonImg;
	


public:
	
	Buton(int tip, std::string Textura, float x, float y);
	~Buton();

	sf::Sprite butonSprite;
	bool apasat;
	int pozx, pozy;
	int tipButon;
	int counter = 1;
	sf::String textInput;
	sf::Text textPreview;
	sf::Event event;

	void clic();
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

