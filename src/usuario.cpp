#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Usuario{
    private:
        string nombre, apellido, nom_Usuario, contr_Usuario;
        int id_Usuario;
    public:
        Usuario(string _nombre, string _apellido);
        string getNom_Usuario() const;
        string getContr_Usuario() const;
        int getId_Usuario() const;
        void setId_Usuario(int _id_Usuario);
        void generarNombreUsuario();
        void generarContrasena();
};

int generate_ID() {
    srand(time(0));
    return rand() % 900000000 + 100000000;
}

Usuario::Usuario(string _nombre, string _apellido) {
    nombre = _nombre;
    apellido = _apellido;
    id_Usuario = generate_ID(); 
}

int Usuario::getId_Usuario() const {
    return id_Usuario;
}

void Usuario::setId_Usuario(int _id_Usuario) {
    id_Usuario = _id_Usuario;
}

void Usuario::generarNombreUsuario() {
        nom_Usuario = nombre + "_" + apellido;
}

void Usuario::generarContrasena() {
        contr_Usuario = "123456"; 
}

string Usuario::getNom_Usuario() const {
    return nom_Usuario;
}

string Usuario::getContr_Usuario() const {
    return contr_Usuario;
}


