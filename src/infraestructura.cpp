#pragma once
#include <iostream>
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

    Departamento() : nmro_apartamento(0), nro_nivel(0), nmbr_edificio(""), propietario("") {}

    Departamento(int _nmro_apartamento, int _nro_nivel, string _nmbr_edificio, string _propietario = "")
        : nmro_apartamento(_nmro_apartamento), nro_nivel(_nro_nivel), nmbr_edificio(_nmbr_edificio), propietario(_propietario) {}

    string get_Propietario() const {
        return propietario;
    }

    bool tienePropietario() const {
        return propietario.empty();
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
    DepartamentoNodo* tail;

    DepartamentoLista() : cabeza(nullptr), tail(nullptr) {}

    ~DepartamentoLista() {
        clear();
    }

    void insertarAlFinal(const Departamento& dept) {
        DepartamentoNodo* nuevo = new DepartamentoNodo(dept);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            tail = nuevo;
        }
        else {
            tail->siguiente = nuevo;
            tail = nuevo;
        }
    }

    DepartamentoNodo* buscar(int numero_departamento) const {
        DepartamentoNodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->data.nmro_apartamento == numero_departamento) {
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
        tail = nullptr;
    }
};

struct Nivel {
    int numero;
    DepartamentoLista departamentos;

    Nivel(int _numero, int cantidad_departamentos) : numero(_numero) {
        for (int i = 1; i <= cantidad_departamentos; ++i) {
            Departamento dept(i, _numero, "");
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

    ~NivelLista() {
        clear();
    }

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

    void clear() {
        NivelNodo* actual = cabeza;
        while (actual != nullptr) {
            NivelNodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
    }
};

struct Edificio {
    string nombre;
    NivelLista niveles;
    int cantidad_niveles;
    int departamentos_por_nivel;

    Edificio(string _nombre, int _cantidad_niveles, int _departamentos_por_nivel)
        : nombre(_nombre), cantidad_niveles(_cantidad_niveles), departamentos_por_nivel(_departamentos_por_nivel) {
        for (int i = 1; i <= cantidad_niveles; ++i) {
            Nivel nivel(i, departamentos_por_nivel);
            niveles.insertarAlFinal(nivel);
        }
    }

    ~Edificio() {
        niveles.clear();
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
            return nullptr;  // Departamento fuera de rango
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

    ~EdificioLista() {
        clear();
    }

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

        // Mostrar los edificios disponibles
        cout << "Seleccione un edificio para ver los departamentos:\n";
        string edificios[100];  // Asumimos que no habrá más de 100 edificios
        int cantidadEdificios = 0;

        // Recorrer los edificios y almacenarlos en el array 'edificios'
        while (actual != nullptr) {
            bool yaExiste = false;
            for (int i = 0; i < cantidadEdificios; ++i) {
                if (edificios[i] == actual->data.nmbr_edificio) {
                    yaExiste = true;
                    break;
                }
            }

            if (!yaExiste) {
                edificios[cantidadEdificios] = actual->data.nmbr_edificio;
                ++cantidadEdificios;
            }
            actual = actual->siguiente;
        }

        // Imprimir las opciones del menú
        for (int i = 0; i < cantidadEdificios; ++i) {
            cout << i + 1 << ". " << edificios[i] << "\n";
        }

        int seleccion;
        cout << "Seleccione el número de edificio: ";
        cin >> seleccion;

        if (seleccion < 1 || seleccion > cantidadEdificios) {
            cout << "Selección no válida." << endl;
            return;
        }

        string edificioSeleccionado = edificios[seleccion - 1];

        // Ahora mostrar los niveles y departamentos del edificio seleccionado
        cout << "\nMostrando departamentos del edificio: " << edificioSeleccionado << "\n";

        // Recorrer los niveles dentro del edificio seleccionado
        for (int nivel = 1; nivel <= 5; ++nivel) {
            bool hayDepartamentosEnNivel = false;
            actual = departamentosCargados.cabeza;

            while (actual != nullptr) {
                // Mostrar solo los departamentos que pertenecen al edificio y nivel actual
                if (actual->data.nmbr_edificio == edificioSeleccionado && actual->data.nro_nivel == nivel) {
                    if (!hayDepartamentosEnNivel) {
                        cout << "\tNivel: " << nivel << "\n";
                        hayDepartamentosEnNivel = true;
                    }

                    // Reemplazar guiones bajos por espacios en el nombre del propietario
                    string propietario_modificado = actual->data.propietario;
                    for (size_t i = 0; i < propietario_modificado.length(); ++i) {
                        if (propietario_modificado[i] == '_') {
                            propietario_modificado[i] = ' ';
                        }
                    }

                    // Imprimir la información del departamento
                    cout << "\t\tDepartamento: " << actual->data.nmro_apartamento
                        << ", Propietario: " << (propietario_modificado.empty() ? "sin propietario" : propietario_modificado) << "\n";
                }
                actual = actual->siguiente;
            }

            if (!hayDepartamentosEnNivel) {
                cout << "\t(No hay departamentos en el nivel " << nivel << ")\n";
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
