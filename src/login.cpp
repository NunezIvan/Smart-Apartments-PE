#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "menuAdministrador.cpp" // Incluir menuAdministrador.cpp
#include "administrador.cpp" // Incluir administrador.cpp
#include "usuario_Apartamento.cpp" // Incluir propietario_Apartamento.cpp

using namespace std;

// Declarar 'edificios' como externo
extern EdificioLista edificios;

// Función para limpiar el buffer
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para el inicio de sesión de Propietario
void inicio_SesionPropietario() {
    int id_ingresado;
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Propietario" << endl;
    cout << "Ingrese su ID: ";
    cin >> id_ingresado;
    limpiarBuffer();
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("propietarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de propietarios." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str, nombre_archivo, contrasena_archivo, nmro_apart_str, nivel_str, edificioNombre;
        getline(ss, id_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');
        getline(ss, nmro_apart_str, ';');
        getline(ss, nivel_str, ';');
        getline(ss, edificioNombre);

        int id_archivo;
        try {
            id_archivo = stoi(id_str);
        }
        catch (const invalid_argument& e) {
            cout << "ID inválido en la línea: " << linea << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "ID fuera de rango en la línea: " << linea << endl;
            continue;
        }

        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Propietario." << endl;
            cout << "Edificio: " << edificioNombre << ", Nivel: " << nivel_str << ", Apartamento: " << nmro_apart_str << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: ID, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

// Función para el inicio de sesión de Administrador
void inicio_SesionAdministrador() {
    int id_ingresado;
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Administrador" << endl;
    cout << "Ingrese su ID: ";
    cin >> id_ingresado;
    limpiarBuffer();
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("administradores.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de administradores." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str, nombre_archivo, contrasena_archivo;
        getline(ss, id_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int id_archivo;
        try {
            id_archivo = stoi(id_str);
        }
        catch (const invalid_argument& e) {
            cout << "ID inválido en la línea: " << linea << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "ID fuera de rango en la línea: " << linea << endl;
            continue;
        }

        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Administrador." << endl;
            encontrado = true;
            menuAdministrador(); // Función para manejar propietarios después de iniciar sesión
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: ID, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

// Función para el inicio de sesión de Mantenimiento
void inicio_SesionMantenimiento() {
    int id_ingresado;
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Mantenimiento" << endl;
    cout << "Ingrese su ID: ";
    cin >> id_ingresado;
    limpiarBuffer();
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("mantenimiento.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de mantenimiento." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str, nombre_archivo, contrasena_archivo;
        getline(ss, id_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int id_archivo;
        try {
            id_archivo = stoi(id_str);
        }
        catch (const invalid_argument& e) {
            cout << "ID inválido en la línea: " << linea << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "ID fuera de rango en la línea: " << linea << endl;
            continue;
        }

        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Personal de Mantenimiento." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: ID, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

// Función para iniciar sesión
void inicio_Sesion() {
    int opcion;

    // Limpiar la pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Seleccione el tipo de usuario para iniciar sesión:" << endl;
    cout << "1. Propietario" << endl;
    cout << "2. Administrador" << endl;
    cout << "3. Mantenimiento" << endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    limpiarBuffer();  // Limpiar el búfer después de leer la opción

    switch (opcion) {
        case 1:
            inicio_SesionPropietario();
            break;
        case 2:
            inicio_SesionAdministrador();
            break;
        case 3:
            inicio_SesionMantenimiento();
            break;
        default:
            cout << "Opción no válida." << endl;
    }
}
