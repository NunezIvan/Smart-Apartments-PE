#ifndef NIVEL_H
#define NIVEL_H
#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include <usuario.hpp>

class Nivel {
private:
    int numero;
    vector<Departamento> departamentos;  
public:
    Nivel(int _numero, int _Num_Departamentos); 
    ~Nivel();
    int getNumero() const
    const vector<Departamento>& getDepartamentos() const
}
#endif