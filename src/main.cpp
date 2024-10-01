#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "login.cpp"

using namespace std;

// Función para crear archivos por defecto
void crearArchivosDefecto() {
    ofstream archivo1("propietarios.txt", ios::out | ios::app);
    if (archivo1.is_open()) {
        archivo1.close();
    }
    else {
        cout << "Error al crear 'propietarios.txt'.\n";
    }

    ofstream archivo2("administradores.txt", ios::out | ios::app);
    if (archivo2.is_open()) {
        archivo2.close();
    }
    else {
        cout << "Error al crear 'administradores.txt'.\n";
    }

    ofstream archivo3("mantenimiento.txt", ios::out | ios::app);
    if (archivo3.is_open()) {
        archivo3.close();
    }
    else {
        cout << "Error al crear 'mantenimiento.txt'.\n";
    }

    ofstream archivo4("departamentos.txt", ios::out | ios::app);
    if (archivo4.is_open()) {
        archivo4.close();
    }
    else {
        cout << "Error al crear 'departamentos.txt'.\n";
    }

}

// Función para crear un usuario administrador por defecto
void usuario_Defecto(){
    administrador_Cond admin("Ivan","Nunez",72167843);
}

int main() {

    crearArchivosDefecto();

    int opcion;
    do {
        cout << "=====================================" << endl;
        cout << "          BIENVENIDO AL SISTEMA     " << endl;
        cout << "=====================================" << endl;
        cout << "\n";
        cout << "         1. Iniciar Sesión           " << endl;
        cout << "         2. Salir                    " << endl;
        cout << "\n"<<endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                inicio_Sesion();
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
        }
    } while (opcion != 2);
    return 0;
}
