#include "IteratorMultime.h"
#include "Multime.h"

#include <stack>

using namespace std;


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	PNod curent = m.radacina;
	while (curent != nullptr)
	{
		stiva.push(curent);
		curent = curent->nod_stanga();
	}
}


void IteratorMultime::prim() {
	while (!stiva.empty()) {
		stiva.pop();
	}
	PNod curent = multime.radacina;
	while (curent != nullptr) {
		stiva.push(curent);
		curent = curent->nod_stanga();
	}
}

void IteratorMultime::urmator() {
	if (!valid())
		throw exception();
	PNod curent = stiva.top()->nod_dreapta();
	stiva.pop();
	while (curent != nullptr){
		stiva.push(curent);
		curent = curent->nod_stanga();
	}
}

TElem IteratorMultime::element() const {
	if (!valid())
		throw exception();
	return stiva.top()->element();
}

bool IteratorMultime::valid() const {
	return !(stiva.empty());
}
