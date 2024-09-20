#include <iostream>
#include <fstream>
#include <usuario.hpp>
#include <departamento.hpp>
using namespace std;

Departamento::Departamento(const string nombre) {
    nombre = _nombre; 
    cout << "Departamento " << nombre << " creado.\n";
}

Departamento::~Departamento() {
    << "Departamento " << nombre << " destruido.\n";
}

Departamento::getNombre() const { return nombre; }