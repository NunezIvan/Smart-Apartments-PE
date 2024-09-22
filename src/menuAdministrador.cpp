#pragma once 
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "edificio.cpp"
#include "propietarios.cpp"
#include "administrador.cpp"
using namespace std;

string nombre_propietario, apellido_propietario;

void manejarPropietarios(administrador_Cond& admin) {
    int opcion;

    Edificio edificio1("Edificio A", 5, 4);
    Edificio edificio2("Edificio B", 3, 3);
    vector<Edificio> edificios = {edificio1, edificio2}; 

    Propietarios listaPropietarios;

    cout << "Ingrese el nombre del propietario: ";
    cin >> nombre_propietario;
    cout << "Ingrese el apellido del propietario: ";
    cin >> apellido_propietario;


    admin.registrarPropietario(listaPropietarios.listaPropietarios, nombre_propietario, apellido_propietario);

    cout << "Edificios disponibles: " << endl;
    for (int i = 0; i < edificios.size(); i++) {
        cout << i + 1 << ". " << edificios[i].nombre << endl;
    }

    int edificioSeleccionado;
    cout << "Seleccione el edificio (1-" << edificios.size() << "): ";
    cin >> edificioSeleccionado;
    Edificio& edificio = edificios[edificioSeleccionado - 1];  

    cout << "Departamentos en el " << edificio.nombre << ":\n";
    edificio.mostrarDepartamentos();

    int nivel, numero_departamento;
    cout << "Seleccione el nivel: ";
    cin >> nivel;
    cout << "Seleccione el número de departamento: ";
    cin >> numero_departamento;

    propietario_Apartamento& propietario = listaPropietarios.obtenerPropietario(0); 
    admin.asignarDepartamento(edificio, nivel, numero_departamento, propietario);

    // Mostrar el estado actual del edificio
    cout << "\nEstado actual del " << edificio.nombre << ":\n";
    edificio.mostrarDepartamentos();

    system("pause");
    system("cls");  
}

void mostrarMenuAdministrador(administrador_Cond& admin) {
    int opcion;
    do {
        cout << "=====================================" << endl;
        cout << " BIENVENIDO AL MENU DE ADMINISTRADOR " << endl;
        cout << "=====================================" << endl;
        cout << "\n";
        cout << "         1. Manejar Propietarios     " << endl;
        cout << "         2. Salir                    " << endl;
        cout << "\n" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                manejarPropietarios(admin);  
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
        }
    } while (opcion != 2);
}
