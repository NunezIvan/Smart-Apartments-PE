#include <iostream>
#include <fstream>   
#include <stdlib.h>
#include "usuario.cpp"

class mantenimiento_Cond : public Usuario {
public:
    mantenimiento_Cond(string _nom_Usuario, string _contr_Usuario);
};

mantenimiento_Cond::mantenimiento_Cond(string _nom_Usuario, string _contr_Usuario):Usuario(_nom_Usuario, _contr_Usuario) {
    setRol_Usuario("Mantenimiento");
    ofstream file("mantenimiento.txt", ios::app);
    if (file.is_open()) {
        file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << "\n";
        file.close();
    }
}

