#pragma once

#include <vector>

#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;

using namespace std;

class Dictionar {
	friend class IteratorDictionar;

	private:
	/* aici e reprezentarea */
		// vector dinamic de elemente
		int capacitate;
		int dimensiune;

		// vectori de elemente
		TElem* element;

		// vector de legaturi
		int* leg_urm;

		// primul elem
		int prim;

		// primul elem liber
		int prim_liber;

		// redimensionare
		void redim();

		// functii pentru lista inlantuita
		int aloca();
		void dealoca(int i);
		void initSpatiuLiber();

		int creeazaNod(TElem e);

	public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;

	// functionalitate laborator
	int adaugaInexistente(Dictionar& d);

	// destructorul dictionarului	
	~Dictionar();

};


