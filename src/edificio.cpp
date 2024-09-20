#include <iostream>
#include <fstream>
#include <edificio.hpp>
#include <nivel.hpp>
#include <departamento.hpp>
using namespace std;

Edificio::Edificio(const string _nombre, int _Num_Niveles, int _Num_Departamentos_Por_Nivel){
    nombre = _nombre;
    for (int i = 0; i < _Num_Niveles; ++i) {
            niveles.push_back(Nivel(i + 1, _Num_Departamentos_Por_Nivel));
    }
}

Edificio::~Edificio() {
        cout << "Edificio " << nombre << " destruido.\n";
    }

Edificio::getNombre() const { return nombre; }
Edificio::getNiveles() const { return niveles; }
