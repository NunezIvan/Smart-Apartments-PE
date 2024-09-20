#include <iostream>
#include <fstream>
#include <string>
#include <login.hpp>
#include <limits>

using namespace std;

// Función para limpiar el búfer de entrada
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

    // Abrimos el archivo de propietarios desde la carpeta data
    ifstream archivo("D:/Smart-Apartments-PE/data/propietarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de propietarios." << endl;
        return;
    }

    int id_archivo, num_Edificio, nivel_Edificio, num_Apartamento;
    string nombre_archivo, contrasena_archivo;
    bool encontrado = false;

    // Leemos línea por línea
    while (archivo >> id_archivo >> nombre_archivo >> contrasena_archivo >> num_Edificio >> nivel_Edificio >> num_Apartamento) {
        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Propietario." << endl;
            cout << "Edificio: " << num_Edificio << ", Nivel: " << nivel_Edificio << ", Apartamento: " << num_Apartamento << endl;
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

    // Abrimos el archivo de administradores desde la carpeta data
    ifstream archivo("D:/Smart-Apartments-PE/data/administradores.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de administradores." << endl;
        return;
    }

    int id_archivo;
    string nombre_archivo, contrasena_archivo;
    bool encontrado = false;

    // Leemos línea por línea
    while (archivo >> id_archivo >> nombre_archivo >> contrasena_archivo) {
        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Administrador." << endl;
            encontrado = true;
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

    // Abrimos el archivo de mantenimiento desde la carpeta data
    ifstream archivo("D:/Smart-Apartments-PE/data/mantenimiento.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de mantenimiento." << endl;
        return;
    }

    int id_archivo;
    string nombre_archivo, contrasena_archivo;
    bool encontrado = false;

    // Leemos línea por línea
    while (archivo >> id_archivo >> nombre_archivo >> contrasena_archivo) {
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


void inicio_Sesion() {
    int opcion;

    system("cls");
    cout << "Seleccione el tipo de usuario para iniciar sesión:" << endl;
    cout << "1. Propietario" << endl;
    cout << "2. Administrador" << endl;
    cout << "3. Mantenimiento" << endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    limpiarBuffer(); 

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
