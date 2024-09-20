#include <iostream>
#include <fstream>
#include <departamento.hpp>
#include <nivel.hpp>
using namespace std;

Nivel::Nivel(int _numero, int _Num_Departamentos) {
    numero = _numero;
    for (int i = 0; i < _Num_Departamentos; ++i) {
        departamentos.push_back(Departamento("Depto " + to_string(i + 1)));
    }
    cout << "Nivel " << numero << " creado con " << numDepartamentos << " departamentos.\n";
}

Nivel::~Nivel() {
    cout << "Nivel " << numero << " destruido.\n";
}

Nivel::getNumero() const { return numero; }
Nivel::getDepartamentos() const { return departamentos; }
