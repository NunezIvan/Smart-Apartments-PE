#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "administrador.cpp" 
#include "usuario_Apartamento.cpp" 
#include "menu.cpp"
#include "menuAdministrador.cpp"
using namespace std;

void inicio_SesionPropietario() {
    printtitle();
    int dni_ingresado;  
    string nombre_ingresado, contrasena_ingresada;
    gotoxy(33,14);
    cout <<"▂▃▄▅▆▇█▓▒░INICIO DE SESION - PROPIETARIO░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(44,16);
    cout << "Ingrese su DNI: ";  
    cin >> dni_ingresado;
    limpiarBuffer();
    gotoxy(44,17);
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    gotoxy(44,18);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("data/propietarios.txt");
    if (!archivo.is_open()) {
        gotoxy(44,19);
        cout << "Error al abrir el archivo de propietarios.";
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni_str, nombre_archivo, contrasena_archivo, nmro_apart_str, nivel_str, edificioNombre;
        getline(ss, dni_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');
        getline(ss, nmro_apart_str, ';');
        getline(ss, nivel_str, ';');
        getline(ss, edificioNombre);

        int dni_archivo;
        dni_archivo = stoi(dni_str);

        if (dni_archivo == dni_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            printtitle();
            gotoxy(33,14);
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Propietario.";
            gotoxy(33,15);
            cout << "Edificio: " << edificioNombre << ", Nivel: " << nivel_str << ", Apartamento: " << nmro_apart_str;
            gotoxy(48,17);
            cout<<"Presione una tecla para continuar.........";
            cin.get();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        gotoxy(40,19);
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos.";
        cin.get();
        system("cls");
    }

    archivo.close();
}

void inicio_SesionAdministrador() {
    printtitle();
    int dni_ingresado;  
    string nombre_ingresado, contrasena_ingresada;
    gotoxy(35,14);
    cout <<"▂▃▄▅▆▇█▓▒░INICIO DE SESION - ADMINISTRADOR░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(44,16);
    cout << "Ingrese su DNI: "; 
    cin >> dni_ingresado;
    limpiarBuffer();
    gotoxy(44,17);
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    gotoxy(44,18);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("data/administradores.txt");
    if (!archivo.is_open()) {
        gotoxy(44,19);
        cout << "Error al abrir el archivo de administradores." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni_str, nombre_archivo, contrasena_archivo;
        getline(ss, dni_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int dni_archivo;
        dni_archivo = stoi(dni_str);


        if (dni_archivo == dni_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            printtitle();
            gotoxy(33,14);
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Administrador.";
            gotoxy(33,16);
            cout<<"Presione una tecla para continuar..............";
            cin.get();
            menuAdministrador(nombre_ingresado);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        gotoxy(40,19);
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos.";
        cin.get();
        system("cls");
    }

    archivo.close();
}

void inicio_SesionMantenimiento() {
    printtitle();
    int dni_ingresado;
    string nombre_ingresado, contrasena_ingresada;
    gotoxy(35,14);
    cout <<"▂▃▄▅▆▇█▓▒░INICIO DE SESION - MANTENIMIENTO░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(44,16);
    cout << "Ingrese su DNI: "; 
    cin >> dni_ingresado;
    limpiarBuffer();
    gotoxy(44,17);
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, nombre_ingresado);
    gotoxy(44,18);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena_ingresada);

    ifstream archivo("data/mantenimiento.txt");
    if (!archivo.is_open()) {
        gotoxy(44,19);
        cout << "Error al abrir el archivo de mantenimiento." << endl;
        cin.get();
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni_str, nombre_archivo, contrasena_archivo;
        getline(ss, dni_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int dni_archivo;
        dni_archivo = stoi(dni_str);

        if (dni_archivo == dni_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            printtitle();
            gotoxy(33,14);
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Personal de Mantenimiento." << endl;
            gotoxy(33,16);
            cout<<"Presione una tecla para continuar......";
            cin.get();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        gotoxy(40,19);
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos.";
        cin.get();
        system("cls");
    }

    archivo.close();
}

void inicio_Sesion() {
    printtitle();
    int opcion;
    cin.ignore();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░TIPO DE USUARIO░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(48,16);
    cout << "1. Propietario";
    gotoxy(48,17);
    cout << "2. Administrador";
    gotoxy(48,18);
    cout << "3. Mantenimiento";
    gotoxy(35,19);
    cout << "Seleccione el tipo de usuario para iniciar sesión: ";
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
