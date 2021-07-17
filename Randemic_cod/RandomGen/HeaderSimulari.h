#pragma once
static const float FPS = 60;
//simulari
extern int nrNpc;


	long long populatii[101];
	void sortarePopulatie(long long pop[101], int limita) {
		for (int i = 0; i < limita-1; i++) {
			for (int j = i + 1; j < limita; j++) {
				if (pop[i] > pop[j]) {
					long long aux = pop[j];
					pop[j] = pop[i];
					pop[i] = aux;
				}
			}
		}
	}
