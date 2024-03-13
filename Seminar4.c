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

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++)
		{
			printf("%d, %s, %d, %.2f  \t ", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}
}

void citireMatrice(const char* numeFisier, struct Masina** matrice, int nrLinii, int* nrCol) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	int(*nrMasini) = 0;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = (char*)malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atoi(element);
		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]));

	}
	fclose(file);
}

//pretul mediu al masinilor cu nr de usi dat  ca parametru
float pretMediu(struct Masina** matrice, int nrLinii, int* nrCol, int nrUsi) {
	if (nrUsi <= 1 || nrUsi > 4) {
		return 0;
	}
	float pretTotal = 0;
	int nrMaini = 0;
	int index = nrUsi - 2;
	if (nrCol[index] == 0) {
		return 0;
	}
	for (int i = 0; i < nrCol[index]; i++)
	{
		pretTotal += matrice[index][i].pret;
	}
	return pretTotal / nrCol[index];
}

//functie care cauta masini dupa id

struct Masina cautaMasinaDupaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if (matrice[i][j].id == id)
				return matrice[i][j];
		}
	}
	struct Masina m;
	m.id = -1;
	m.producator = NULL;
	m.nrUsi = -1;
	m.pret = -1;
	return m;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrCol)[i]; j++) {
			free((*matrice)[i][j].producator);
		}
		free((*matrice)[i]);
	}
	free(*nrCol);
	(*nrCol) = NULL;
	free(*matrice);
	(*matrice) = NULL;

}

int main() {

	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int) * nrLinii);//vectorul de lungimi
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrCol[i] = 0;
		matrice[i] = NULL;
	}

	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);
	printf("\n");
	printf("Pretul mediu este: %5.2f\n", pretMediu(matrice, nrLinii, nrCol, 2));
	printf("\n");
	struct Masina masina_cautata;
	masina_cautata = cautaMasinaDupaID(matrice, nrLinii, nrCol, 2);
	printf("%i %s %i %.2f\n", masina_cautata.id, masina_cautata.producator, masina_cautata.nrUsi, masina_cautata.pret);
	dezalocareMatrice(&matrice, nrLinii, &nrCol);

	return 0;
}