#ifndef USUARIO_APARTAMENTO_H
#define USUARIO_APARTAMENTO_H

#include <iostream>
#include <fstream>   // Asegúrate de incluir fstream aquí
#include <stdlib.h>
#include <usuario.hpp>
using namespace std;
class propietario_Apartamento : public Usuario {
private:
    int nivel_Edificio, num_Apartamento, num_Edificio;

public:
    propietario_Apartamento(string _nom_Usuario, string _contr_Usuario, int _num_Edificio, int _nivel_Edificio, int _num_Apartamento);
    int getnum_Edificio() const;
    int getnum_Apartamento() const;
    int getNivel_Edificio() const;
};

#endif