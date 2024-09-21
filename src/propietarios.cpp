#pragma once
#include<iostream>
#include <vector>
#include "usuario_Apartamento.cpp"
using namespace std;

class Propietarios {

public:
    vector<propietario_Apartamento> listaPropietarios;
    void agregarPropietario(propietario_Apartamento propietario) {
        listaPropietarios.push_back(propietario);
        cout << "Propietario " << propietario.getNombre() << " agregado a la lista." << endl;
    }

    void mostrarPropietarios() const {
        for (const auto& propietario : listaPropietarios) {
            propietario.mostrarDatos();
        }
    }

    propietario_Apartamento& obtenerPropietario(int index) {
        return listaPropietarios[index];
    }
};
