#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
	int vverif[5];
	int iverif;
	TElem e;

	Multime m1;
	assert(m1.adauga(5) == true);
	assert(m1.adauga(1) == true);
	assert(m1.adauga(10) == true);
	IteratorMultime im1 = m1.iterator();
	im1.prim();
	iverif = 0;
	e = im1.element();
	vverif[iverif++] = e;
	im1.urmator();
	while (im1.valid()) {
		assert(rel(e, im1.element()));
		e = im1.element();
		vverif[iverif++] = e;
		im1.urmator();
	}
	assert((vverif[0] == 1) && (vverif[1] == 5) && (vverif[2] == 10));


	Multime m;
	//return;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(1) == false);
	assert(m.adauga(10) == false);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);

	IteratorMultime im = m.iterator();
	iverif = 0;
	im.prim();
	e = im.element();
	vverif[iverif++] = e;
	im.urmator();
	while (im.valid()) {
		assert(rel(e, im.element()));
		e = im.element();
		vverif[iverif++] = e;
		im.urmator();
	}
	assert((vverif[3] == 10) && (vverif[2] == 7) && (vverif[1] == 5) && (vverif[0] == -3));

}

void testReuniune() {

	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(1) == false);
	assert(m.adauga(10) == false);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 5);

	Multime m2;
	for (int i = 0; i <= 3; i++) {
		m2.adauga(i);
	}
	for (int i = 5; i > 3; i--) {
		m2.adauga(i);
	}

	assert(m2.dim() == 6);
	// trebuie sa adauge 4 elemente, m.dim() = 5 actual
	m.reuniune(m2);
	// trebuie m.dim() sa fie 9
	assert(m.dim() == 9);

	m2.adauga(50);
	// mai adaugam un element ca sa ne asiguram
	m.reuniune(m2);
	assert(m.dim() == 10);

	// adaug un element deja existent in m
	m2.adauga(10);
	m.reuniune(m2);
	// dimensiunea nu ar trebui sa se schimbe
	assert(m.dim() == 10);
}
