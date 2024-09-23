#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "menuAdministrador.cpp"

using namespace std;


void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para el inicio de sesión de Propietario
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
        string id_str, num_Edificio_str, nivel_Edificio_str, num_Apartamento_str;
        getline(ss, id_str, ';');
        string nombre_archivo, contrasena_archivo;
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');
        getline(ss, num_Edificio_str, ';');
        getline(ss, nivel_Edificio_str, ';');
        getline(ss, num_Apartamento_str);

        int id_archivo = stoi(id_str);
        int num_Edificio = stoi(num_Edificio_str);
        int nivel_Edificio = stoi(nivel_Edificio_str);
        int num_Apartamento = stoi(num_Apartamento_str);

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

    ifstream archivo("administradores.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de administradores." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str;
        string nombre_archivo, contrasena_archivo;

        getline(ss, id_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int id_archivo = stoi(id_str);

        if (id_archivo == id_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Administrador." << endl;
            encontrado = true;
            manejarPropietarios(); // Función para manejar propietarios después de iniciar sesión
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
        string id_str;
        string nombre_archivo, contrasena_archivo;

        getline(ss, id_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int id_archivo = stoi(id_str);

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
