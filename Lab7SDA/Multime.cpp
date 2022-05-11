#include "Multime.h"
#include "IteratorMultime.h"

#include <queue>
#include <iostream>
#include <vector>

using namespace std;

Nod::Nod(TElem elem, PNod stanga, PNod dreapta) {
    this->elem = elem;
    this->stanga = stanga;
    this->dreapta = dreapta;
}

TElem Nod::element() {
    return elem;
}
PNod Nod::nod_stanga() {
    return stanga;
}
PNod Nod::nod_dreapta() {
    return dreapta;
}

// o posibila relatie
bool rel(TElem e1, TElem e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

Multime::Multime() {
    this->radacina = nullptr;
}
// Determina nodul minim
PNod Multime::nod_minim(PNod nod) {
    while (nod->nod_stanga() != nullptr) {
        nod = nod->stanga;
    }
    return nod;
}

// adaugare recursiva(nu o folosesc)
PNod Multime::adauga_recursiv(PNod pointer, TElem elem)
{
    // daca avem multimea goala, doar cream radacina 
    if (pointer == nullptr) {
        pointer = new Nod(elem, nullptr, nullptr);
        return pointer;
    }
    // daca elementul pe care dorim sa il adaugam este < elem curent, adaugam in stanga
    else {
        if (elem < pointer->elem)
            pointer->stanga = adauga_recursiv(pointer->stanga, elem);
    // daca elementul pe care dorim sa il adaugam este > elem curent, adaugam in dreapta
        else pointer->dreapta = adauga_recursiv(pointer->dreapta, elem);
    }
    return pointer;
}
/* Avem 3 cazuri: 
*   1. nodul nu are copii
*   2. nodul are 2 copii
*   3. nodul are un copil
* */
PNod Multime::sterge_recursiv(PNod pointer, TElem elem) {
    // 1. nodul nu are copii
    if (pointer == nullptr)
        return pointer;
    else {
        // am gasit elementul
        if (elem == pointer->elem) {
            // 2. nodul are 2 copii
            if (pointer->stanga != nullptr && pointer->dreapta != nullptr) { 
                // determinam nodul minim din dreapta
                PNod minDreapta = nod_minim(pointer->dreapta);
                // schimbam valoarea nodului ce trebuie sters cu minimul
                pointer->elem = minDreapta->elem;
                // stergem recursiv duplicatul ce s-a creeat
                pointer->dreapta = sterge_recursiv(pointer->dreapta, pointer->elem);
            }
            else {  // 3. nodul are un copil
                PNod sters = pointer;
                PNod returnat;
                // avem doar dreapta
                if (pointer->stanga == nullptr) {
                    returnat = pointer->dreapta;
                }
                //  avem doar stanga
                else {
                    returnat = pointer->stanga;
                }
                delete sters;
                return returnat;
            }

        }   // daca nu am gasit elementul la nodul actual
        // ne ducem pe partea stanga
        else if (rel(elem, pointer->elem)) {
            pointer->stanga = sterge_recursiv(pointer->stanga, elem);
            return pointer;
        }
        // ne ducem pe partea dreapta
        else {
            pointer->dreapta = sterge_recursiv(pointer->dreapta, elem);
            return pointer;
        }
    }
}

PNod Multime::cauta_recursiv(PNod pointer, TElem elem) const{
    // suntem deja la nodul respectiv
    if (pointer == nullptr || pointer->elem == elem)
        return pointer;
    // cautam in stanga
    if (rel(elem, pointer->elem)) {
        return cauta_recursiv(pointer->stanga, elem);
    }
    // // cautam in dreapta
    return cauta_recursiv(pointer->dreapta, elem);
}

// Adaugare iterativa(recursiv nu trecea testele)
bool Multime::adauga(TElem elem) {
    // adaugam direct nodul nou daca arborele este gol
    PNod nou = new Nod(elem, nullptr, nullptr);
    if (radacina == nullptr) {
        radacina = nou;
        return true;
    }
    else {
        PNod curent = radacina;
        PNod parinte = nullptr;

        while (1) {
            parinte = curent;
            // incepem cu radacina, daca exista deja elementul nu mai adaugam si stergem nodul
            if (elem == parinte->elem) {
                delete nou;
                return false;
            }

            if (rel(elem, parinte->elem)) { // incercam adaugarea in stanga conform relatiei
                curent = curent->stanga;

                if (curent == nullptr) {
                    parinte->stanga = nou;
                    return true;
                }
            }
            else { // incercam adaugarea in dreapta conform relatiei
                curent = curent->dreapta;

                if (curent == nullptr) {
                    parinte->dreapta = nou;
                    return true;
                }
            }
        }
    }
}

/* Avem 2 cazuri:
*   - cautam elementul si nu il gasim, inseamna ca nu avem ce sa stergem
*   - cautam elementul si il gasim, deci stergem recursiv incepand cu radacina
 */
bool Multime::sterge(TElem elem) {
    if (cauta(elem)) {
        radacina = sterge_recursiv(radacina, elem);
        return true;
    }
    else {
        return false;
    }
}

// apelam cautarea recursiva 
bool Multime::cauta(TElem elem) const {
    if (cauta_recursiv(radacina, elem) == nullptr) {
        return false;
    }
    return true;
}

// Crestem dimensiunea cu ajutorul iteratorului, iteram toata multimea(asemanator cu testele)
int Multime::dim() const {
    int dimensiune = 0;
    IteratorMultime it = iterator();
    while (it.valid()) {
        dimensiune++;
        it.urmator();
    }
    return dimensiune;
}

// Radacina este initializata cu 0, daca nu se modifica inseamna ca avem multime vida
bool Multime::vida() const {
    if (radacina == nullptr)
        return true;
    return false;
}

// nu o mai folosesc
void Multime::distrug_recursiv(PNod pointer) {
    if (pointer != nullptr) {
        distrug_recursiv(pointer->nod_stanga());
        distrug_recursiv(pointer->nod_dreapta());
        delete pointer;
    }
}

// Implementam o coada care sa stearga tot arborele
Multime::~Multime() {
    queue<PNod> q;
    if (radacina) {
        q.push(radacina);
    }
    while (!q.empty()) {
        PNod point = q.front();
        q.pop();
        if (point->stanga != nullptr) {
            q.push(point->stanga);
        }
        if (point->dreapta != nullptr) {
            q.push(point->dreapta);
        }
        delete point;
    }
}

IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

/* Complexitate: 
* n = dimensiunea multimii b
* 
* Caz defavorabil : Q(n)
* Caz favorabil : Q(n)
* Caz mediu : Q(n)
* Total : Q(n)
*/

void Multime::reuniune(const Multime& b) {
    IteratorMultime iterator = b.iterator();
    while (iterator.valid()) {
        adauga(iterator.element());
        iterator.urmator();
    }
}

/* Pseudocod:
* Subalgoritm reuniune(Multime& b)
* 
* pre: multime b, multime a preexistenta
* post: in multimea a s-au adaugat elementele din multimea b
* 
*   iterator <- b->iterator()
*   CatTimp iterator->valid() executa
*       adauga(iterator->element())
*       iterator->urmator()
*   SfCatTimp
* SfSubalgoritm
*/


