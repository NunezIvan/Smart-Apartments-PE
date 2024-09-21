#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Departamento {
public:
    int numero;
    string propietario;

    Departamento(int _numero, string _propietario){
        numero = _numero;
        propietario = _propietario;
    }

    void mostrar() {
        cout << "Departamento " << numero << ", Propietario: " << propietario << endl;
    }

    int getNumero(){return numero;}
    string getPropietario(){return propietario;}
};

class Nivel {
public:
    int numero;
    vector<Departamento> departamentos;

    Nivel(int _numero, int cantidad_departamentos) {
        numero = _numero;
        for (int i = 1; i <= cantidad_departamentos; i++) {
            departamentos.push_back(Departamento(i, "Sin propietario"));
        }
    }
};

class Edificio {
public:
    string nombre;
    vector<Nivel> niveles;

    Edificio(string _nombre, int cantidad_niveles, int departamentos_por_nivel){
        nombre = _nombre;
        for (int i = 1; i <= cantidad_niveles; i++) {
            niveles.push_back(Nivel(i, departamentos_por_nivel));
        }
    }

    void mostrarDepartamentos() {
        for (const auto& nivel : niveles) {
            cout << "Nivel " << nivel.numero << ":\n";
            for (const auto& dep : nivel.departamentos) {
                cout << "  - Departamento " << dep.numero << ": " << dep.propietario << endl;
            }
        }
    }

    Departamento& obtenerDepartamento(int nivel, int numero_departamento) {
        return niveles[nivel - 1].departamentos[numero_departamento - 1];
    }
};
