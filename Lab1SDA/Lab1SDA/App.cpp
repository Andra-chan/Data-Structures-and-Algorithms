#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;

// 4. TAD Matrice - reprezentare sub forma unei matrice rare, reprezentare condensata pe linii.
int main() {

	cout << "Initializare teste..." << endl;

	testAll();
	testAllExtins();

	cout << "Testele au trecut cu succes!" << endl;
}
