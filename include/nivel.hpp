#ifndef NIVEL_H
#define NIVEL_H
#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include "usuario.hpp"
#include <vector>
#include "departamento.hpp"

class Nivel {
private:
    int numero;
    vector<Departamento> departamentos;  
public:
    Nivel(int _numero, int _Num_Departamentos); 
    ~Nivel();
    int getNumero();
    const vector<Departamento>& getDepartamentos();
};
#endif