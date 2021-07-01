#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <windows.h>


using namespace std;

string NpcMat[100][5];

	struct npc {

		string prenume;
		string nume;
		string sex;
		string varsta;
		string inaltime;

	};


	string Prenume(bool sex) {
		return 0;
	}
	string Nume(string prenume) {
		return 0;
	}
	string sex() {
		return 0;
	}
	string varsta() {
		return 0;
	}
	string inaltime(string varsta) {
		return 0;
	}




int main() {
	
	int NrNpc;
	cin >> NrNpc;
	for (int i = 0; i < NrNpc; i++) {
		npc Npc;
		int j = 0;
		Npc.nume = "Rozwe";
		bool sex = rand() % 2;
		if (sex == true) {
			Npc.sex = "M";
		}
		else {
			Npc.sex = "F";
		}
		Npc.varsta = to_string(rand() % 70 + 1);
		Npc.inaltime = to_string(rand() % 40 + 150);
		NpcMat[i][j++] = Npc.nume;
		NpcMat[i][j++] = Npc.sex;
		NpcMat[i][j++] = Npc.varsta;
		NpcMat[i][j++] = Npc.inaltime;
		
	}



	//afisare
	for (int i = 0; i < NrNpc; i++) {
		for (int j = 0; j < 4; j++) {
			cout << NpcMat[i][j] << " ";

		}
		cout << '\n';
	}

	return 0;
}