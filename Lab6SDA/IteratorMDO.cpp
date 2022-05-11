#include "IteratorMDO.h"
#include "MDO.h"

// Complexitatea este Theta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {

    //this->pozCurenta = 0;
    this->curent = d.minim;
    //deplasare();
}

// Complexitatea este Theta(1)
void IteratorMDO::prim() {

    this->curent = dict.minim;
}

// Complexitatea este Theta(1)
void IteratorMDO::urmator() {

    if (this->valid() == false)

        throw exception();

    this->curent = this->curent->urmator_ordine();

}

// Complexitatea este Theta(1)
bool IteratorMDO::valid() const {

    if (this->curent != nullptr)

        return true;

    return false;
}

// Complexitatea este Theta(1)
TElem IteratorMDO::element() const {

    if (valid() == false)

        throw exception();

    return std::make_pair(this->curent->get_cheie(), this->curent->get_valoare());
}
