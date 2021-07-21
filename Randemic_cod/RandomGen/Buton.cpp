#include "Buton.h"
#include "HeaderSimulari.h"
#include "SimulatorLoader.h"
#include <fstream>


Buton::Buton(int tip, sf::String label, std::string Textura, float x, float y) {
    this->tipButon = tip;
    this->labelText.setString(label);
    this->butonImg.loadFromFile(Textura);
    this->butonSprite.setTexture(this->butonImg);
    this->butonSprite.setPosition(sf::Vector2f(x, y));
    this->pozx = x;
    this->pozy = y;

    this->peTasta = false;
    this->textInBox.setCharacterSize(20);
    sf::Font font;
    font.loadFromFile("Fonts/KarmaFuture.ttf");
    this->textInBox.setFont(font);
    this->textInBox.setColor(sf::Color::Black);
    this->textInBox.setPosition(this->pozx, this->pozy);


}


Buton::~Buton() {

}


//std::ofstream fout("text.txt");

void Buton::setCounter(int* counter)
{
    this->counter = counter;
}

void Buton::update(const sf::Vector2f mousePos) {

    //
    if (this->butonSprite.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->apasat = true;

        }

    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->apasat == true) {
            this->apasat = false;
        }

    }




}

int simulare1();
int simulareOras();
int initEcranPrincipal();


void Buton::clic(sf::Event event) {
    if (this->apasat == true) {
        switch (this->tipButon) {
        
        case(-1): {
            //sageti stanga

            (*counter) -= 1;
            break;
        }
        case(0): {
            //sageti dreapta

            (*counter) += 1;
            break;
        }
        case(1): {
            simulare1();


            break;
        }
        case(2): {
            simulareOras();
            break;
        }
        case(3): {
            initEcranPrincipal();
            break;
        }
        case(4): {
            SimulatorLoader incarcator;
            incarcator.openFile();
            break;
        }
        case(-5): {
            //text input


            if (event.type == sf::Event::TextEntered)
            {

                if (this->peTasta == false) {
                    this->peTasta = true;
                    typedOn(event);
                }


            }
            else {
                this->peTasta = false;
            }


            break;
        }


        }
    }
}

void Buton::render(sf::RenderTarget* target) {
    target->draw(this->butonSprite);
}



void Buton::typedOn(sf::Event input) {

    int charTyped = input.text.unicode;
    if (charTyped < 128) {
        inputLogic(charTyped);

    }

}

void Buton::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != RESET_KEY && charTyped>='0' && charTyped<='9') {
        text << static_cast<char>(charTyped);
    }
    else if (charTyped == DELETE_KEY) {

        if (text.str().length() > 0) {
            deleteLastChar();
        }
    }
    textInBox.setString(text.str() + "");
}

void Buton::deleteLastChar() {
    std::string t = text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {//prost io
        newT += t[i];
    }
    text.str("");
    text << newT;
    textInBox.setString(text.str());

}

void Buton::renderTextBox(sf::RenderWindow& window, sf::Event event) {
    window.draw(butonSprite);
    clic(event);
    update(sf::Vector2f(sf::Mouse::getPosition(window)));
}

std::string Buton::getText() {
    return text.str();
}