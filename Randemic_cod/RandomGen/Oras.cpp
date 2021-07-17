#include "Oras.h"
#include "HeaderVirus.h"


Oras::Oras(std::string denumire, long long int populatie, float pozX, float pozY) {
    this->denumire = denumire;
    this->populatie = populatie;
    this->infectati = 0;
    this->decedati = 0;
    this->vindecati = 0;
    this->pX = pozX;
    this->pY = pozY;
    this->shape.setPosition(pX, pY);
    this->trimit = 0;
    this->cotaZilnic.push_back(infectati);
}

Oras::~Oras() {

}


void Oras::update()
{


    //aici updatez numerele pentru infectati, vindecati si decedati
    long long int nouInfectati = Oras::getInfectati() * infectabilitate / 100;

    if (Oras::getPopulatie() - Oras::getDeced() - Oras::getVindecati() < nouInfectati + Oras::getInfectati()) {
        //nu mai am atata populatie cat sa se poata infecta atati oameni
        nouInfectati = (Oras::getPopulatie() - Oras::getInfectati() - Oras::getDeced() - Oras::getVindecati()) * infectabilitate / 100;
        if (nouInfectati < 0)
        {
            nouInfectati = 0;
        }
    }

    long long int totalInfec = Oras::getInfectati() + nouInfectati;
    Oras::setInfectati(totalInfec);


    //noii infectati
    //ii pun in cota zilnica
    std::deque<long long int> cota = Oras::getNumVindZilnic();




    //verific daca nu cumva se vor vindeca cativa dintre cei deja infectati
    if (cota.size() >= timpRecuperare / 60) {
        //elimin oamenii care din pacate mor pana sa se vindece
        long long int decedNoi = cota.at(cota.size() - 1) * mortalitate / 100;
        Oras::setDeced(Oras::getDeced() + decedNoi);
        this->populatie -= decedNoi;
        this->infectati -= decedNoi;

        //pe ei trebuie sa ii scot din cota
        cota.at(cota.size() - 1) -= decedNoi;
        if (cota.at(cota.size() - 1) <= 0)
        {
            cota.pop_back();

        }
        if (cota.size() >= timpRecuperare / 60)
        {
            //trebuie sa ii scot pe primii infectati
            long long int infecVind = cota.at(cota.size() - 1);
            this->infectati -= infecVind;
            Oras::setVindec(Oras::getVindecati() + infecVind);
            cota.pop_back();
        }

    }
    cota.push_front(nouInfectati);
    Oras::setCota(cota);
}

void Oras::logicOras() {
    //extinderea la alte orase
}

void Oras::setTexture(long long populatieMaxima) {

    sf::Texture texture;

    if (getPopulatie() <= populatieMaxima / 4) {
        texture.loadFromFile("Sprites/oras1.png");
    }
    else if (getPopulatie() > populatieMaxima / 4 && getPopulatie() <= populatieMaxima / 2) {
        texture.loadFromFile("Sprites/oras2.png");
    }
    else if (getPopulatie() > populatieMaxima / 2 && getPopulatie() <= ((3 * populatieMaxima) / 4)) {
        texture.loadFromFile("Sprites/oras3.png");
    }
    else {
        texture.loadFromFile("Sprites/oras4.png");
    }

    this->orasSprite.setTexture(texture);
}

void Oras::sortarePopulatie(long long pop[101], int limita) {
    for (int i = 1; i < limita; i++) {
        for (int j = i + 1; j < limita + 1; j++) {
            if (pop[i] > pop[j]) {
                long long aux = pop[j];
                pop[j] = pop[i];
                pop[i] = aux;
            }
        }
    }
}
