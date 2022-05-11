#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	this->curent = this->dict.prim;
}


void IteratorDictionar::prim() {
	this->curent = this->dict.prim;
}


void IteratorDictionar::urmator() {
	if (curent == -1)
		throw exception();
	this->curent = this->dict.leg_urm[curent];
}


TElem IteratorDictionar::element() const{
	if (curent == -1)
		throw exception();
	TElem elem = this->dict.element[curent];
	return pair <TCheie, TValoare>(elem.first, elem.second);
}


bool IteratorDictionar::valid() const {
	if (curent == -1)
		return false;
	return true;
}

