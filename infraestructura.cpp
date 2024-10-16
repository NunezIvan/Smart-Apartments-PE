#pragma once
#include <iostream>
#undef byte
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "usuario_Apartamento.cpp" 
#include "administrador.cpp" 
using namespace std;

int NRO_DEPARTAMENTOS_NIVEL = 4;
int NRO_NIVEL_EDIFICIO = 5;
int NRO_EDIFICIOS = 2;

struct Departamento {
    string propietario;
    string nmbr_edificio;
    int nmro_apartamento;
    int nro_nivel;

    Departamento(int _nmro_apartamento, int _nro_nivel, string _nmbr_edificio, string _propietario): nmro_apartamento(_nmro_apartamento), nro_nivel(_nro_nivel), nmbr_edificio(_nmbr_edificio), propietario(_propietario) {
        ifstream archivo("data/departamentos.txt");

        if (!archivo.is_open()) {
            cout << "El archivo no existe." << endl;
        }

        string linea;
        int lineCount = 0;

        while (getline(archivo, linea)) {
            if (!linea.empty()) {  
                lineCount++;
            }
        }

        archivo.close();

        if (lineCount < NRO_DEPARTAMENTOS_NIVEL*NRO_NIVEL_EDIFICIO*NRO_EDIFICIOS) {
            ofstream file("data/departamentos.txt", ios::app);
            if (file.is_open()) {
                file << propietario << ";" << nmro_apartamento << ";" << nro_nivel << ";" << nmbr_edificio << "\n";
                file.close();
            } else {
                cout << "No se pudo abrir el archivo para escritura." << endl;
            }
        } else {
            return;
        }
    }


};

struct DepartamentoNodo {
    Departamento data;
    DepartamentoNodo* siguiente;

    DepartamentoNodo(const Departamento& dept) : data(dept), siguiente(nullptr) {}
};

class DepartamentoLista {
public:
    DepartamentoNodo* cabeza;
    DepartamentoNodo* cola;

    DepartamentoLista() : cabeza(nullptr), cola(nullptr) {}

    void insertarAlFinal(const Departamento& dept) {
        DepartamentoNodo* nuevo = new DepartamentoNodo(dept);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }

    }
    DepartamentoNodo* verificarPropietario(int numero_departamento, int nro_nivel, string _nmbr_edificio) const {
        DepartamentoNodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->data.nmro_apartamento == numero_departamento && actual->data.nro_nivel==nro_nivel && actual->data.nmbr_edificio == _nmbr_edificio && actual->data.propietario == "Sin_Propietario") {
                return actual; 
            }
            actual = actual->siguiente;
        }
        return nullptr; 
    }

    DepartamentoNodo* buscar(int numero_apartamento) const {
        DepartamentoNodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->data.nmro_apartamento == numero_apartamento) {
                return actual; 
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
};

struct Nivel {
    int numero;
    DepartamentoLista departamentos;

    Nivel(int _numero, int cantidad_departamentos, string nmbr_Edificio) : numero(_numero) {
        for (int i = 1; i <= cantidad_departamentos; i++) {
            Departamento dept(i, _numero,nmbr_Edificio,"Sin_Propietario");
            departamentos.insertarAlFinal(dept);
        }
    }
};

struct NivelNodo {
    Nivel data;
    NivelNodo* siguiente;

    NivelNodo(const Nivel& nivel) : data(nivel), siguiente(nullptr) {}
};

class NivelLista {
public:
    NivelNodo* cabeza;

    NivelLista() : cabeza(nullptr) {}

    void insertarAlFinal(const Nivel& nivel) {
        NivelNodo* nuevo = new NivelNodo(nivel);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            NivelNodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    NivelNodo* buscar(int numero_nivel) const {
        NivelNodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->data.numero == numero_nivel) {
                return actual; 
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

};

struct Edificio {
    string nombre;
    NivelLista niveles;
    int cantidad_niveles;
    int departamentos_por_nivel;

    Edificio(string _nombre, int _cantidad_niveles, int _departamentos_por_nivel)
        : nombre(_nombre), cantidad_niveles(_cantidad_niveles), departamentos_por_nivel(_departamentos_por_nivel) {
        for (int i = 1; i <= cantidad_niveles; i++) {
            Nivel nivel(i, _departamentos_por_nivel,_nombre);
            niveles.insertarAlFinal(nivel);
        }
    }

    Departamento* obtenerDepartamento(int nivel, int numero_departamento) {
        NivelNodo* nivelNode;

        if (nivel < 1 || nivel > cantidad_niveles) {
            return nullptr;
        }

        DepartamentoNodo* deptoNode;

        if (numero_departamento < 1 || numero_departamento > departamentos_por_nivel) {
            return nullptr;
        }

        return &(deptoNode->data);
    }
};

struct EdificioNodo {
    Edificio data;
    EdificioNodo* siguiente;
    EdificioNodo(const Edificio& edificio) : data(edificio), siguiente(nullptr) {}
};

class EdificioLista {
public:
    EdificioNodo* cabeza;

    EdificioLista() : cabeza(nullptr) {}

    void insertarAlFinal(const Edificio& edificio) {
        EdificioNodo* nuevo = new EdificioNodo(edificio);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            EdificioNodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    EdificioNodo* buscar(const string& nombre_edificio) const {
        EdificioNodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->data.nombre == nombre_edificio) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

};
