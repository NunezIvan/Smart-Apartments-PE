#ifndef EDIFICIO_H
#define EDIFICIO_H
#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include <usuario.hpp>

class Edificio {
private:
    string nombre;
    vector<Nivel> niveles;

public:
    Edificio(const string _nombre, int _Num_Niveles, int _Num_Departamentos_Por_Nivel){
        nombre = _nombre;
        for (int i = 0; i < numNiveles; ++i) {
            niveles.push_back(Nivel(i + 1, _Num_Departamentos_Por_Nivel));
        }
    }

    ~Edificio() {
        cout << "Edificio " << nombre << " destruido.\n";
    }

    string getNombre() const { return nombre; }
    const vector<Nivel>& getNiveles() const { return niveles; }
};


#endif