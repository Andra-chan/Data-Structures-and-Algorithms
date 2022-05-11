#include "Dictionar.h"
#include "IteratorDictionar.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

void Dictionar::redim() {
	TElem* new_elemente = new TElem[2 * this->capacitate];
	int* new_leg_urmator = new int[2 * this->capacitate];
	int* new_leg_precedent = new int[2 * this->capacitate];

	for (int i = 0; i < this->capacitate; i++) {
		new_elemente[i] = this->element[i];
		new_leg_urmator[i] = this->leg_urm[i];
	}

	delete[] element;
	delete[] leg_urm;

	this->element = new_elemente;
	this->leg_urm = new_leg_urmator;

	// lista spatiului liber
	for (int i = this->capacitate; i <= 2 * this->capacitate - 1; i++) {
		this->leg_urm[i] = i + 1;
	}

	this->leg_urm[2 * this->capacitate - 1] = -1;

	this->prim_liber = this->capacitate;

	this->capacitate = 2 * this->capacitate;
}

int Dictionar::aloca() {
	int i = this->prim_liber;
	this->prim_liber = this->leg_urm[prim_liber];
	this->dimensiune++;
	return i;
}

void Dictionar::dealoca(int i) {
    this->leg_urm[i] = this->prim_liber;
    this->prim_liber = i;
	this->dimensiune--;
}

void Dictionar::initSpatiuLiber() {
	for (int i = dimensiune;i < capacitate;i++) {
		this->leg_urm[i] = i + 1;
	}
	this->leg_urm[capacitate-1] = -1;
	this->prim_liber = 1;
}

int Dictionar::creeazaNod(TElem e) {
	if (this->prim_liber == 0) {
		redim();
		initSpatiuLiber();
	}
	int i = aloca();
	this->element[i] = e;
	this->leg_urm[i] = -1;
	return i;
}

Dictionar::Dictionar() {
	this->capacitate = 10;
	this->dimensiune = 0;

	this->prim = -1;
	this->prim_liber = 0;

	this->element = new TElem[this->capacitate];
	this->leg_urm = new int[this->capacitate];
	initSpatiuLiber();
}

Dictionar::~Dictionar() {
	delete[] element;
	delete[] leg_urm;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	TElem elem;
	elem.first = c, elem.second = v;

	// adaugam la inceput
	if (dimensiune == 0) {
		int i = creeazaNod(elem);
		prim = i;
	}

	// adaugam in rest, daca gasim deja o cheie egala cu c, inlocuim si returnam valoarea precedenta
	else {
		int i = prim;
		//creeazaNod(elem);
		while (i != -1) {
			if (element[i].first == c) {
				TValoare val_precedenta = element[i].second;
				element[i].second = v;
				return val_precedenta;
			}
			i = leg_urm[i];
		}
		element[i] = elem;
		creeazaNod(elem);
	}
	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	int curent = prim;
	while (curent != -1) {
		if (element[curent].first == c)
			return element[curent].second;
		curent = leg_urm[curent];
	}
	return NULL_TVALOARE;
}

// stergem o cheie si returneaza valoarea asociata
TValoare Dictionar::sterge(TCheie c){
	int i = prim;
	while (i != -1) {
		if (element[i].first == c) {
			dealoca(i);
			return element[i].second;
		}
		i = leg_urm[i];
	}
	return NULL_TVALOARE;
}

// returneaza dimensiune
int Dictionar::dim() const {
	return this->dimensiune;
}

// verifica daca este vid
bool Dictionar::vid() const{
	if (this->dimensiune == 0) {
		return true;
	}
	return false;
}

IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}

/*
 * pseudocod
 * Subalgoritm adaugaInexistente(Dictionar& d)
 *
 *  pre: Dictionar(LSI) d
 *  post: nr_inexistente - numarul de perechi adaugate
 *
 *  nr_inexistente <- 0
 *
 *  curent <- d.prim
 *  CatTimp curent != -1 executa
 *      elem <- d.element[curent]
 *      exista <- false
 *      cauta(d, elem.first, valori)
 *      Pentru i = 0, size(valori) executa
 *          Daca valori[i] = elem.second atunci
 *              exista <- true
 *              break
 *          SfDaca
 *      SfPentru
 *      Daca exista = false atunci
 *          nr_inexistente += 1
 *          adauga(d, elem.first, elem.second)
 *      SfDaca
 *      curent = d.leg_urmator[curent];
 * SfCatTimp
 * returneaza nr_inexistente
 */

 /*
  * n - numarul perechi din dictionarul curent
  * m - numarul de perechi din noul dictionar
  *
  * Caz defavorabil: Q(n*m)
  * Caz favorabil: Q(n*m)
  * Caz mediu: Q(n*m)
  * Total: Q(n*m)
  */
int Dictionar::adaugaInexistente(Dictionar& d) {
	int nr_inexistente = 0;
	bool exista;

	int curent = d.prim;
	while (curent != -1) {
		auto elem = d.element[curent];
		exista = false;
		TValoare valoare = this->cauta(elem.first);
		if (valoare == elem.second) {
			exista = true;
			break;
		}
		if (exista == false) {
			nr_inexistente++;
			this->adauga(elem.first, elem.second);
		}
		curent = d.leg_urm[curent];
	}
	return nr_inexistente;
}

