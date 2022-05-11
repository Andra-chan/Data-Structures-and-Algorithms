#pragma once

#define NULL_TELEM -1
typedef int TElem;
typedef bool(*Relatie)(TElem, TElem);

class IteratorMultime;

class Nod; 

typedef Nod* PNod;

class Nod {
	friend class Multime;
private:
	TElem elem;
	PNod stanga;
	PNod dreapta;

public:
	Nod(TElem elem, PNod stanga, PNod dreapta);

	TElem element();
	PNod nod_stanga();
	PNod nod_dreapta();
};

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
		PNod radacina;

		PNod adauga_recursiv(PNod pointer, TElem elem); // nefolosita
		PNod sterge_recursiv(PNod pointer, TElem elem);
		PNod cauta_recursiv(PNod pointer, TElem elem) const;
		PNod nod_minim(PNod nod);
		void distrug_recursiv(PNod pointer); // nefolosita

    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();

		// functionalitate noua
		void reuniune(const Multime& b);
};




