#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H
#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include <usuario.hpp>

class Departamento {
private:
    string nombre;
public:
    Departamento(const string nombre);      
    ~Departamento() 
    string getNombre() const;
};

#endif