#pragma once
#include <iostream>
#include <fstream>
#include "usuario.cpp"
using namespace std;

class administrador_Cond : public Usuario {
private:
    string nombre;
    string apellido;
    string nombreUsuario;
    string contrasena;
public:
    administrador_Cond(string _nombre, string _apellido, int DNI) : Usuario(_nombre, _apellido, DNI) {
        nombre = _nombre;
        apellido = _apellido;
        generarNombreUsuario(); 
        generarContrasena(); 

        // Guardar los datos del administrador en un archivo
        ofstream file("administradores.txt", ios::app);
        if (file.is_open()) {
            file << getDNI_Usuario() << ";" << getNom_Usuario() << ";" << getContr_Usuario() << "\n";
            file.close();
        } else {
            cout << "No se pudo abrir el archivo para escritura." << endl;
        }
    }
};
