#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "usuario.cpp"

using namespace std;
class propietario_Apartamento : public Usuario {
private:
    string nombre;
    string apellido;
    string nombreUsuario;
    string contraseña;
public:
    propietario_Apartamento(string _nombre, string _apellido):Usuario(_nombre, _apellido){
        setRol_Usuario("Propietario");
        nombre = _nombre;
        apellido = _apellido;
        
        generarNombreUsuario(); 
        generarContraseña(); 
        ofstream file("D:/Smart-Apartments-PE/data/propietarios.txt", ios::app);
        if (file.is_open()) {
        file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << "\n";
        file.close();
        } else {
            cout << "No se pudo abrir el archivo para escritura." << endl;
        }
    }

    void mostrarDatos() const{
        cout << "Propietario de Apartamento: " << nombre << endl;
    }

    string getNombre() {return nombre;}
    string getApellido() {return apellido;}
    string getNombreUsuario() const { return nombreUsuario; }
    string getContraseña() const { return contraseña; }

};
