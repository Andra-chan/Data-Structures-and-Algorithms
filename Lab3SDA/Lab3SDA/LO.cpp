#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

Nod::Nod(TElement e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

TElement Nod::element() {
	return e;
}

PNod Nod::urmator() {
	return urm;
}

LO::LO(Relatie r) {

	rel = r;
	this->primul = nullptr;
	//this->urm = nullptr;
}

// returnare dimensiune
// returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const {
	return nrElems;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
	if (primul == 0)
		return true;
	return false;
}

// prima pozitie din LO
Iterator LO::prim() const {

	Iterator it = Iterator(*this);
	it.curent = primul;
	return it;
}

// returnare element de pe pozitia curenta
// arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	if (poz.valid())
		return poz.element();
	throw exception();
}

// sterge element de pe o pozitie poz si returneaza elementul sters
// dupa stergere poz e pozitionat pe elementul de dupa cel sters
// arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	if (!poz.valid())
		throw exception();

	TElement val_precedenta = 0;

	// daca lista este valida nu fac nimic
	if (primul == NULL)
		return val_precedenta;

	// daca este primul element, atunci
	// il sterg si mut capul
	if (rel(poz.curent->e, primul->e))
	{
		val_precedenta = poz.element();
		PNod deSters = primul;
		primul = primul->urm;
		delete deSters;
		nrElems--;
		return val_precedenta;
	}
	else {
		// caut elementul de pe pozitia data
		PNod i = 0;	// pozitia curenta

		// parcurg lista pana la pozitia ceruta sau
		// pana la sfarsitul listei
		while (primul->urm != NULL && i < poz.curent - 1)
		{
			primul = primul->urm;
			i++;
		}

		// daca lista contine elementul
		if (i == poz.curent-1) {
			val_precedenta = poz.element();
			PNod predecesor = primul;

			// salez referinta la elementul de sters
			PNod deSters = predecesor->urm;

			// scurtcirtcuitam elementul
			predecesor->urm = predecesor->urm->urm;

			// si il sterg
			delete deSters;

			nrElems--;
			return val_precedenta;
		}
		else {
			PNod predecesor = NULL;

			val_precedenta = poz.element();

			PNod deSters = predecesor->urm;

			predecesor->urm = predecesor->urm->urm;

			delete deSters;

			nrElems--;
			return val_precedenta;
		}
	}
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const{
	Iterator it = Iterator(*this);
	// la inceput iteratorul este invalid
	it.curent = nullptr;
	// daca elementul sigur nu apare in lista (lista e vida, elementul e < primul - daca relatia e <=) 
	if ((primul == nullptr) || (!rel(primul->e, e)))
		return it;
	// cautam prima aparitie a elementului in lista
	PNod p = primul;
	// tinem cont ca elementele sunt in ordine, parcurgem cat timp elementul cautat e in relatie cu elementul listei   
	while ((p != nullptr) && (p->e != e) && (!rel(e, p->e))) {
		p = p->urm;
	}
	// am gasit elementul
	if ((p != nullptr) && (p->e == e)) {
		// setam iteratorul pe element
		it.curent = p;
	}
	return it;
}

// adaugare element in LO
void LO::adauga(TElement e) {

	// 1. Inserare la inceput
	PNod nou = new Nod(e, nullptr);
	// daca lista e vida, se adauga primul element
	if (primul == nullptr) {
		primul = nou;
		nrElems++;
		return;
	}
	else if (rel(e, primul->e)) {
		// elementul de adaugat e in relatie cu informatia utila a primului nod 
		// se adauga inainte de primul
		nou->urm = primul;
		primul = nou;
		nrElems++;
		return;
	}

	//  Inserare la sfarsit
	else {
		/*PNod nod = primul;
		while (nod->urm != NULL)
			nod = nod->urm;
		nod->urm = nou;
		return;*/

		// 2. Inserare dupa un element
		PNod p = primul;
		while (p->urm != nullptr) {		// cat timp nu ajungem la finalul listei
			if (rel(e, p->urmator()->element())) {		// daca sunt in relatie
				nou->urm = p->urmator();				// mutam dupa e actualul element urmator
				p->urm = nou;							// inseram dupa elementul curent
				nrElems++;								// crestem numarul de elemente
				return;
			}
			p = p->urmator();							// adaugam la finalul listei
		}
		p->urm = nou;									// adaugam la finalul listei		
		nrElems++;										// crestem numarul de elemente
	}	
}


// destructor
LO::~LO() {

	while (primul != nullptr)
	{
		PNod p = primul;
		primul = primul->urm;
		delete p;
	}
}