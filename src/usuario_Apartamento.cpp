#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "usuario.cpp"
using namespace std;

class usuario_Apartamento : public Usuario {
private:
    string nombre;
    string apellido;
    string nombreUsuario;
    string contrasena;
    int nmro_apart;
    int nivel;
    string nmbr_edificio;

public:
    usuario_Apartamento(string _nombre, string _apellido, int _nmro_apart, int _nivel, string nmbr_edificio, int _DNI,boolean tip)
        : Usuario(_nombre, _apellido, _DNI), nmro_apart(_nmro_apart), nivel(_nivel), nmbr_edificio(nmbr_edificio) {
        
        nombre = _nombre;
        apellido = _apellido;
        generarNombreUsuario(); 
        generarContrasena();    

        if(tip){
            ofstream file("data/propietarios.txt", ios::app);
            if (file.is_open()) {
                file << getDNI_Usuario() << ";" << getNom_Usuario() << ";" << getContr_Usuario() << ";"
                    << nmro_apart << ";" << nivel << ";" << nmbr_edificio << "\n";
                file.close();
            } else {
                cout << "No se pudo abrir el archivo para escritura." << endl;
            }
        }
    }
    
    usuario_Apartamento() : Usuario("", "", 0) {
        nombre = "";
        apellido = "";
        nmro_apart = 0;
        nivel = 0;
        nmbr_edificio = "";
    }

    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    int getApartamento() {return nmro_apart;}
    int getNivel() { return nivel;}
    string getNombreEdificio(){return nmbr_edificio;}


    void getDatosDelApartamento() {
        cout << "Nombre del propietario: " << nombre << endl;
        cout << "Apellido del propietario: " << apellido << endl;
        cout << "Nombre del edificio: " << nmbr_edificio << endl;
        cout << "Nivel del apartamento: " << nivel << endl;
        cout << "Nmro del apartamento: " << nmro_apart << endl;
    }
};
