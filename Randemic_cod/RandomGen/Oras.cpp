#include "Oras.h"
#include "HeaderVirus.h"

namespace oras {
	int infectabilitate = virus::infectabilitate; //procent din 100%
	int timpRecuperare = virus::timpRecuperare;//frameuri
	const int timpIncubare = virus::timpIncubare;//timp incubare
	int mortalitate = virus::mortalitate;//procent din 100%

}

Oras::Oras(std::string denumire,long long int populatie, long long int infectati, float pozX, float pozY) {
	this->denumire = denumire;
	this->populatie = populatie;
	this->infectati = infectati;
	this->pX = pozX;
	this->pY = pozY;
	this->cotaZilnic.push_back(infectati);
}

Oras::~Oras() {

}

void Oras::update()
{
	//aici updatez numerele pentru infectati, vindecati si decedati
	long long int nouInfectati = Oras::getInfectati() * oras::infectabilitate;
	if (Oras::getPopulatie() - Oras::getInfectati() - Oras::getDeced() - Oras::getVindecati() < nouInfectati)
	{
		//nu mai am atata populatie cat sa se poata infecta atati oameni
		nouInfectati = Oras::getPopulatie() - Oras::getInfectati() - Oras::getDeced() - Oras::getVindecati();
	}
	//noii infectati
	//ii pun in cota zilnica
	std::deque<long long int> cota = Oras::getNumVindZilnic();
	cota.push_back(nouInfectati);
	Oras::setCota(cota);

	long long int totalInfec = Oras::getInfectati() + nouInfectati;

	//elimin oamenii care din pacate mor pana sa se vindece
	long long int decedNoi = totalInfec * oras::mortalitate / 100;
	Oras::setDeced(Oras::getDeced() + decedNoi);
	//pe ei trebuie sa ii scot din cota
	while (decedNoi > 0)
	{
		if (cota.at(0) <= decedNoi)
		{
			decedNoi -= cota.at(0);
			cota.pop_front();
		}
		else
		{
			cota.at(0) = cota.at(0) - decedNoi;
			break;
		}
	}

	//verific daca nu cumva se vor vindeca cativa dintre cei deja infectati
	if (cota.size() >= virus::timpRecuperare)
	{
		//trebuie sa ii scot pe primii infectati
		long long int infecVind = cota.at(0);
		Oras::setVindec(Oras::getVindecati() + infecVind);
		cota.pop_front();
	}
}

void Oras::logicOras()
{
	//extinderea la alte orase
}