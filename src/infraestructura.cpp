#pragma once
#include <iostream>
#undef byte
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "usuario_Apartamento.cpp" 
#include "administrador.cpp" 


using namespace std;

struct Departamento {
    string propietario;
    string nmbr_edificio;
    int nmro_apartamento;
    int nro_nivel;

    Departamento(int _nmro_apartamento, int _nro_nivel, string _nmbr_edificio, string _propietario): nmro_apartamento(_nmro_apartamento), nro_nivel(_nro_nivel), nmbr_edificio(_nmbr_edificio), propietario(_propietario) {
        ifstream archivo("departamentos.txt");

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

        if (lineCount < 40) {
            ofstream file("departamentos.txt", ios::app);
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


    string get_Propietario() const {
        return propietario;
    }

    bool tienePropietario() const {
        if(propietario == "Sin_Propietario"){
            return false;
        }
        else{
            return true;
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
                return actual;  // Retornar el nodo si coincide el número de departamento
            }
            actual = actual->siguiente;
        }
        return nullptr;  // Si no se encuentra, retornar nullptr
    }

    void clear() {
        DepartamentoNodo* actual = cabeza;
        while (actual != nullptr) {
            DepartamentoNodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
        cola = nullptr;
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
                return actual;  // Retornar el nodo si coincide el número del nivel
            }
            actual = actual->siguiente;
        }
        return nullptr;  // Si no se encuentra, retornar nullptr
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
        // Buscar el nivel especificado
        NivelNodo* nivelNode;

        // Verificar que el número de nivel esté dentro del rango esperado
        if (nivel < 1 || nivel > cantidad_niveles) {
            return nullptr;
        }

        // Buscar el departamento en el nivel especificado
        DepartamentoNodo* deptoNode;

        // Verificar que el número de departamento esté dentro del rango esperado
        if (numero_departamento < 1 || numero_departamento > departamentos_por_nivel) {
            return nullptr;
        }

        // Retornar el puntero al departamento encontrado
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
                return actual;  // Retornar el nodo si coincide el nombre del edificio
            }
            actual = actual->siguiente;
        }
        return nullptr;  // Si no se encuentra, retornar nullptr
    }

    void mostrarMenuEdificios(DepartamentoLista& departamentosCargados) {
        DepartamentoNodo* actual = departamentosCargados.cabeza;

        if (actual == nullptr) {
            cout << "No hay departamentos cargados." << endl;
            return;
        }

        cout << "Seleccione un edificio para ver los departamentos:\n";
        cout << "1. Edificio_1\n";
        cout << "2. Edificio_2\n";

        int seleccion;
        cout << "Seleccione el número de edificio: ";
        cin >> seleccion;

        string edificioSeleccionado;
        switch (seleccion) {
            case 1:
                edificioSeleccionado = "Edificio_1";
                break;
            case 2:
                edificioSeleccionado = "Edificio_2";
                break;
            default:
                cout << "Selección no válida." << endl;
                return;
        }

        cout << "\nMostrando departamentos del edificio: " << edificioSeleccionado << "\n";

        // Recorrer y mostrar cada nivel
        for (int nivel = 1; nivel <= 5; ++nivel) {
            cout << "\tNivel " << nivel << ":\n";

            // Lista temporal para guardar los departamentos ordenados del nivel actual
            DepartamentoNodo* cabezaOrdenada = nullptr;

            // Extraer departamentos que corresponden a este edificio y nivel
            actual = departamentosCargados.cabeza;
            while (actual != nullptr) {
                if (actual->data.nmbr_edificio == edificioSeleccionado && actual->data.nro_nivel == nivel) {
                    // Crear un nuevo nodo para insertar en la lista ordenada
                    DepartamentoNodo* nuevoNodo = new DepartamentoNodo(actual->data);
                    // Insertar en la lista manteniendo el orden por número de departamento
                    if (!cabezaOrdenada || cabezaOrdenada->data.nmro_apartamento > nuevoNodo->data.nmro_apartamento) {
                        nuevoNodo->siguiente = cabezaOrdenada;
                        cabezaOrdenada = nuevoNodo;
                    } else {
                        DepartamentoNodo* actualOrdenado = cabezaOrdenada;
                        while (actualOrdenado->siguiente && actualOrdenado->siguiente->data.nmro_apartamento < nuevoNodo->data.nmro_apartamento) {
                            actualOrdenado = actualOrdenado->siguiente;
                        }
                        nuevoNodo->siguiente = actualOrdenado->siguiente;
                        actualOrdenado->siguiente = nuevoNodo;
                    }
                }
                actual = actual->siguiente;
            }

            // Imprimir los departamentos ordenados
            actual = cabezaOrdenada;
            while (actual != nullptr) {
                cout << "\t\t" << actual->data.nmro_apartamento << ". Propietario: "
                    << (actual->data.propietario.empty() ? "Sin propietario" : actual->data.propietario) << endl;
                DepartamentoNodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }

            if (!cabezaOrdenada) {
                cout << "\t(No hay departamentos en este nivel)\n";
            }
        }
    }

    void clear() {
        EdificioNodo* actual = cabeza;
        while (actual != nullptr) {
            EdificioNodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
    }
};
