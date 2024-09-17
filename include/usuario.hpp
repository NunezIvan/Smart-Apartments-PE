#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Usuario{
    private:
        string nom_Usuario, contr_Usuario, rol_Usuario;
        int id_Usuario;
    public:
        Usuario(string _nom_Usuario, string _contr_Usuario);
        string getNom_Usuario() const;
        string getContr_Usuario() const;
        int getId_Usuario() const;
        void setRol_Usuario(string _rol_Usuario);
        void setId_Usuario(int _id_Usuario);  // Aquí está el setter que faltaba
};

#endif