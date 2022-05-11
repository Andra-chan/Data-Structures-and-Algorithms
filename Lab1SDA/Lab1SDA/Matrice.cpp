#include "Matrice.h"

#include <exception>
#include <iostream>
using namespace std;


Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0)
		throw;				// exceptie daca numar_linii sau numar_coloane este <=0

	numar_linii = m;		// primeste din functie m (numar_linii)
	numar_coloane = n;		// primeste din functie m (numar_coloane)
	numar_elemente = 0;		// initial avem 0 elemente nenule
	capacitate = 2;			// capacitate initiala care trebuie marita 

	Linie = new TElem[numar_linii + 1];			// vectorul Linie cu [numar_linii + 1] elemente
	for (int i = 0; i < numar_linii + 1; i++)
	{
		Linie[i] = 1;							// il initializam cu valoarea 1
	}
	Coloana = new TElem[capacitate];
	Valoare = new TElem[capacitate];
	for (int i = 0; i < capacitate; i++)
	{
		Coloana[i] = -1;
		Valoare[i] = -1;
	}
}

void redimensionare(TElem*& vector, int numar_elemente, int capacitate) {

	// aloc un spatiu de capacitate dubla
	TElem* vector_nou = new TElem[capacitate * 2];

	// copiez vechile valori in noua zona
	for (int i = 0; i < numar_elemente; i++)
	{
		vector_nou[i] = vector[i];
	}

	// dublez capacitatea
	//capacitate = capacitate * 2;

	// eliberez vechea zona
	delete[] vector;

	// vectorul indica spre noua zona
	vector = vector_nou;
}


int Matrice::nrLinii() const {
	return numar_linii;
}


int Matrice::nrColoane() const {
	return numar_coloane;
}

// returnare element de pe o linie si o coloana
// se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
// indicii se considera incepand de la 0
TElem Matrice::element(int i, int j) const {

	// tratez exceptia initiala (pozitie invalida)
	// pentru a avea o pozitie invalida, (i,j) trebuie sa fie ori negativi, ori mai mari decat
	// [numar_linii - 1] (-1 deoarece indexarea se face de la 0)
	if ((i > numar_linii - 1 || i < 0) || (j > numar_coloane - 1 || j < 0))
	{
		throw exception();
	}

	// tratez cazul cand nu avem elemente pe o linie
	if (Linie[i + 1] - Linie[i] == 0)
	{
		return 0;
	}

	// gasirea elementului
	for (int indice = Linie[i]; indice < Linie[i + 1]; indice++)
	{
		if (Coloana[indice - 1] == j)		// cand l-am gasit
		{
			return Valoare [indice - 1];		// returnez valoarea
		}
	}

	return 0;
}


// modificare element de pe o linie si o coloana si returnarea vechii valori
// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
TElem Matrice::modifica(int i, int j, TElem e) {

	// tratez exceptia initiala (pozitie invalida)
	// pentru a avea o pozitie invalida, (i,j) trebuie sa fie ori negativi, ori mai mari decat
	// [numar_linii - 1] (-1 deoarece indexarea se face de la 0)
	if ((i > numar_linii - 1 || i < 0) || (j > numar_coloane - 1 || j < 0))
	{
		throw exception();
	}

	// Avem 3 cazuri de tratat: adaugare element nenul, modificare element nenul, si stergere element nenul
	// 1.	Adaugare: elementul curent este 0, elementul e este nenul
	// 2.	Modificare: elementul curent este nenul, elementul e este nenul
	// 3.	Stergere: elementul curent este nenul, elementul e este 0

	// initializam doua variabile reprezentand:
	// - elementul curent existent la Linie[i] si Coloana[j]
	int element_curent = element(i, j);
	// - valoarea de dinainte de modificare
	int valoare_veche = 0;

	// 1.	Adaugare
	if (element_curent == 0 && e != 0) {
		numar_elemente++;		// creste numarul total de elemente cu 1
		// pentru a nu initialia capacitatea cu un numar prea mare, apelez functia redimensionare pentru a aloca memorie suplimentara
		if (numar_elemente >= capacitate) {
			redimensionare(Coloana, numar_elemente, capacitate);
			redimensionare(Valoare, numar_elemente, capacitate);
			capacitate = capacitate * 2;
		}

		// permutam spre dreapta elementele din vectorii Coloana si Valoare
		int permutare = numar_elemente - 1;
		int parcurgere = Linie[i] - 1;

		// parcurgem vectorii Linie si Coloana pana in locul in care trebuie adaugat elementul e
		while (parcurgere < (Linie[i+1] - 1) && Coloana[parcurgere] < j)
		{
			parcurgere = parcurgere + 1;
		}
		parcurgere = parcurgere + 1;
		// permutam spre dreapta pana ajungem in locul in care vrem sa adaugam elementul e
		while (permutare >= parcurgere)
		{
			Coloana[permutare] = Coloana[permutare - 1];
			Valoare[permutare] = Valoare[permutare - 1];
			permutare = permutare - 1;
		}

		// marcam in vectorul Linie adaugarea unui element
		for (int indice = i + 1; indice < nrLinii() + 1; indice++)
		{
			Linie[indice] = Linie[indice] + 1;
		}

		// actualizam vectorii Coloana si Validare
		Coloana[parcurgere - 1] = j;
		Valoare[parcurgere - 1] = e;
		return 0;
	}

	// 2.	Modificare
	else if (element_curent != 0 && e != 0) {
		for (int indice = Linie[i]; indice < Linie[i + 1]; indice++)	// parcurgem vectorul Linie
		{
			if (Coloana[indice - 1] == j)		// Gasesc in vectorul Coloana coloana ce corespunde
			{
				valoare_veche = Valoare[indice - 1];		// salvez valoarea veche
				Valoare[indice - 1] = e;		// stochez noua valoare
				return valoare_veche;		// returnez valoarea veche
			}
		}
	}
	// 3.	Stergere
	else if (element_curent != 0 && e == 0) {
		for (int indice = Linie[i]; indice < Linie[i + 1]; indice++)
			if (Coloana[indice - 1] == j)
			{
				valoare_veche = Valoare[indice - 1];		// salvez valoarea veche

				// permutam spre stanga pana ajungem in locul in care vrem sa scoatem elementul e
				for (int indice2 = indice - 1; indice2 < numar_elemente - 1; indice2++)
				{
					Coloana[indice2] = Coloana[indice2 + 1];
					Valoare[indice2] = Valoare[indice2 + 1];
				}
				break;		// iesim din for deoarece am gasit elementul
			}
		for (int indice = i + 1; indice < nrLinii() + 1; indice++)
		{
			Linie[indice]--;		// micsorez vectorul Linie
		}
		numar_elemente--;
		return valoare_veche;		// returnez valoarea veche
	}
	else
		return 0;
}
