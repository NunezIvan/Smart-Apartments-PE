#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Usuario {
private:
    string nombre;
    string apellido;
    string nom_Usuario;
    string contr_Usuario;
    int DNI;

public:
    Usuario(string _nombre, string _apellido, int DNI);
    string getNom_Usuario() const;
    string getContr_Usuario() const;
    int getDNI_Usuario() const;
    void generarNombreUsuario();
    void generarContrasena();
};

Usuario::Usuario(string _nombre, string _apellido, int _DNI) {
    nombre = _nombre;
    apellido = _apellido;
    DNI = _DNI;
}

int Usuario::getDNI_Usuario() const {
    return DNI;
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
