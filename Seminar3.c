#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}

struct Masina* MasiniSport(struct Masina* masini, int nrMasini, int* nrMasiniSport) {
	*nrMasiniSport = 0;
	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi < 4) {
			(*nrMasiniSport)++;
		}
	}
	int k = 0;
	struct Masina* masiniSport = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniSport));
	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi < 4) {
			masiniSport[k++] = masini[i];
		}
	}
	return masiniSport;

}


int main() {

	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		printf("Masina nr. %d \n", i);
		printf("Id: %d \n", masini[i].id);
		printf("Producator: %s \n", masini[i].producator);
		printf("Nr usi: %d \n", masini[i].nrUsi);
		printf("Pret: %5.2f \n", masini[i].pret);
		printf("\n");
	}
	printf("\n");
	printf("Masini cu mai putin de 4 usi: \n\n");
	int nrMasiniSport = 0;
	struct Masina* masiniSport = MasiniSport(masini, nrMasini, &nrMasiniSport);
	for (int i = 0; i < nrMasiniSport; i++)
	{
		printf("Masina nr. %d \n", i);
		printf("Id: %d \n", masiniSport[i].id);
		printf("Producator: %s \n", masiniSport[i].producator);
		printf("Nr usi: %d \n", masiniSport[i].nrUsi);
		printf("Pret: %5.2f \n", masiniSport[i].pret);
		printf("\n");
	}

	return 0;
}