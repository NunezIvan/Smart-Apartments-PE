#ifndef MANTENIMIENTO_H
#define MANTENIMIENTO_H
#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include <usuario.hpp>

class mantenimiento_Cond : public Usuario {
public:
    mantenimiento_Cond(string _nom_Usuario, string _contr_Usuario);
};

#endif