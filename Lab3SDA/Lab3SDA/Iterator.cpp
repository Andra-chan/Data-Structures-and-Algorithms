#include <iostream>
#include "Iterator.h"
#include "LO.h"
#include <assert.h>
using namespace std;

Iterator::Iterator(const LO& lo) : lo(lo){
	this->curent = lo.primul;
}

void Iterator::prim(){
	this->curent = lo.primul;
}

void Iterator::urmator(){
	if (valid() == false)
		throw exception();
	this->curent = this->curent->urmator();
}

bool Iterator::valid() const{
	return (curent != nullptr);
}

TElement Iterator::element() const{
	if (valid() == false)
		throw exception();
	return curent->element();
}

// muta elementul curent referit de iterator k pasi inainte
// face iteratorul nevalid daca exista mai putin de k elemente ramase in lista
// arunca exceptie daca iteratorul este nevalid sau in cazul in care k este 0 sau negativ
void Iterator::avanseazaKPasi(int k) {
	// Complexitate totala: O(n)
	// Caz favorabil:  T(k) = 1 apartine O-(1)(theta)
	// Caz defavorabil: T(k) = k apartine O-(k)(theta)

	// exceptie daca k < 1
	if (k < 0 || k == 0) {
		throw exception();
	}
	//exceptie daca iteratorul este invalid
	else if (!this->valid()) {
		throw exception();
	}
	// facem iteratorul nevalid daca k este mai mare decat dimensiunea listei
	else if (k > this->lo.nrElems) {	// this->lo.dim()
		this->curent = nullptr;
	}

	// muta elementul curent referit de iterator k pasi inainte
	for (int i = 0; i < k;i++) {
		if (this->curent->urmator() == nullptr) {		// daca urmatorul element este 0, inseamna ca am ajuns la capatul listei 
			this->curent = nullptr;						// adica avem mai putin de k elemente ramase in lista
			break;
		}
		else {
			this->curent = this->curent->urmator();		// daca trece toate conditiile, mutam iteratorul de pe curent pe urmator de k ori
		}
	}
}

	// Pseudocod functia avanseazaKPasi
	// pre: k > 0, iterator curent valid, k < nrElems
	// post: iterator.curent = iterator.curent.urmator()  (muta iteratorul curent cu k pasi inainte) 
	// SAU
	// iterator.curent = 0 (face iteratorul nevalid daca k>nrElems sau daca avem mai putin de k elemente in lista)

	// {k este invalid(k<=0)}
	// exception()

	// {iteratorul este nevalid}
	// iterator.curent <- NIL

	// {k este mai mare decat nrElems(lo.dim())}
	// it.curent <- NIL
	
	// pentru i<-1,k executa
	// Daca (it.curent.urmator() = NIL) atunci
	// it.curent <- NIL
	// paraseste (break)
	// SfDaca
	// Altfel
	// it.curent <- it.curent.urmator()
	//SfAltfel
	//SfPentru

	





