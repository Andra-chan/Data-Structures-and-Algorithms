#pragma once

#include "LO.h"

class Iterator{
	friend class LO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lo;

	/* aici e reprezentarea  specifica a iteratorului */
	PNod curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElement element() const;

		// muta elementul curent referit de iterator k pasi inainte
		// face iteratorul nevalid daca exista mai putin de k elemente ramase in lista
		// arunca exceptie daca iteratorul este nevalid sau in cazul in care k este 0 sau negativ
		void avanseazaKPasi(int k);
};
