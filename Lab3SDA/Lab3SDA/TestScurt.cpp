#include <assert.h>

#include "LO.h"
#include "Iterator.h"

#include <exception>
using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator itCauta = lo.cauta(1);
    assert(itCauta.valid());
    assert(itCauta.element() == 1);
    itCauta.urmator();
    assert(!itCauta.valid());
    itCauta.prim();
    assert(itCauta.valid());
    Iterator itPrim = lo.prim();
    assert(itPrim.valid());
    assert(itPrim.element() == 1);
    assert(lo.sterge(itCauta) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());
}

void testAvanseazaKPasi() {
	LO lo = LO(relatie1);
	assert(lo.dim() == 0);
	assert(lo.vida());
	lo.adauga(1);
	assert(lo.dim() == 1);
	assert(!lo.vida());

	Iterator it = lo.prim();
	it.avanseazaKPasi(10);
	assert(!it.valid());

	Iterator it2 = lo.prim();
	try {
		it.avanseazaKPasi(0);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	try {
		it.avanseazaKPasi(-10);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	lo.adauga(2);
	lo.adauga(3);
	lo.adauga(4);
	lo.adauga(5);
	assert(lo.dim() == 5);
	Iterator it3 = lo.prim();
	it3.avanseazaKPasi(3);
	assert(it3.element() == 4);
	assert(it3.valid());
}


