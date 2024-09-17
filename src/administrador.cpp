#include <iostream>
#include <fstream>
#include <usuario.hpp>
#include <administrador.hpp>
using namespace std;

administrador_Cond::administrador_Cond(string _nom_Usuario, string _contr_Usuario):Usuario(_nom_Usuario, _contr_Usuario) {
    setRol_Usuario("Administrador");
    // Escribir los datos del administrador en el archivo de texto
    ofstream file("administradores.txt", ios::app);
    if (file.is_open()) {
        file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << "\n";
        file.close();
    }
}

