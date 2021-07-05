#include <sstream>
#include <cstdlib>

#include <include/SFML/Window.hpp>
#include <include/SFML/System.hpp>
#include <include/SFML/Graphics.hpp>

#define DELETE_KEY 8  //backspace
#define ESCAPE_KEY 27 //esc
#define RESET_KEY 359 //F1


class Buton {
private:


    sf::RectangleShape shape;
    sf::Texture butonImg;


    void inputLogic(int charTyped);
    void deleteLastChar();

public:

    Buton(int tip, sf::String label, std::string Textura, float x, float y);
    ~Buton();

    sf::Sprite butonSprite;
    bool apasat;
    bool peTasta = false;

    int pozx, pozy;
    int tipButon;
    int counter = 1;

    sf::Text textInBox;
    sf::Text labelText;
    std::ostringstream text;

    void typedOn(sf::Event input);
    std::string getText();

    void clic(sf::Event event);
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    void renderTextBox(sf::RenderWindow& window, sf::Event event);

};