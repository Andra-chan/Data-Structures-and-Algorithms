#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class Nod_lista;

typedef Nod_lista* PNod_lista;

class Nod_lista {

    friend class MDO;

private:

    TElem e;

    PNod_lista next;

    PNod_lista next_ordine;

public:

    Nod_lista() = default;

    Nod_lista(TElem e, PNod_lista urm, PNod_lista next_ord);

    TCheie get_cheie();

    TValoare get_valoare();

    PNod_lista urmator();

    PNod_lista urmator_ordine();

};

class MDO {
    friend class IteratorMDO;
private:

    PNod_lista* dictionar;

    int m;  // dispesie prin diviziune cu m = dimensiunea td

    int dimensiune;

    Relatie r;

    void redimensionare();

    void redispersare(TElem* vec, int lung);

    void restabileste_ordine(PNod_lista curent, PNod_lista precedent);

    PNod_lista minim;

public:

    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MDO
    int dim() const;

    //verifica daca MultiDictionarul Ordonat e vid
    bool vid() const;

    // se returneaza iterator pe MDO
    // iteratorul va returna perechile in ordine in raport cu relatia de ordine
    IteratorMDO iterator() const;

    // destructorul
    ~MDO();

    vector<TValoare> colectiaValorilor() const;

};
