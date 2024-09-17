#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
#include <fstream>
#include <usuario.hpp>
#include <administrador.hpp>


class administrador_Cond : public Usuario {
public:
    administrador_Cond(string _nom_Usuario, string _contr_Usuario);
};

#endif