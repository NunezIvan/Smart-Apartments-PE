#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "menuAdministrador.cpp" 
#include "administrador.cpp" 
#include "usuario_Apartamento.cpp" 
#include "Cuotas.cpp"
#include "ingresos.cpp"

using namespace std;

extern EdificioLista edificios;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menuUsuario(string edificioNombre, string nivel_str, string nmro_apart_str){
    int menu;
    cuotas cuota;
    listaCuota lista;

    ifstream archivo("cuotas_Personales.txt", ios::in);
    if(archivo.fail()){
        cout<<"Error, no se pudo cargar el archivo, cerrando programa"<<endl;
        exit(1);
    }

    string montostr;
    string linea;
    while(getline(archivo, linea)){

        string nopagadostr;
        stringstream ss(linea);
        getline(ss,cuota.Cuota,';');
        getline(ss,cuota.mes,';');
        getline(ss,montostr,';');
        getline(ss,cuota.edificio,';');
        getline(ss,cuota.nivel,';');
        getline(ss,cuota.apartamento,';');
        getline(ss,nopagadostr,';');

        cuota.monto= stof(montostr);

        cuota.nopagado = (nopagadostr == "true");

        lista.agregarFinal(cuota);
    }
    archivo.close();

    do{
    cout<<"1. Ver cuotas sin pagar"<<endl; 
    cout<<"0. Salir"<<endl;
    cin>>menu; 
    switch(menu){
        case 1: {
            lista.verCuotasPersonales(edificioNombre,nivel_str,nmro_apart_str);
            break;
        }
        case 0:{
            cout<<"Adios"<<endl;
            return;
        }
        default :{
            cout<<"Entrada invalida"<<endl;
        }
    }

    }while(menu<0 && menu>1); 
}

void inicio_SesionPropietario() {
    int dni_ingresado;  
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Propietario" << endl;
    cout << "Ingrese su DNI: ";  
    cin >> dni_ingresado;
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
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Propietario." << endl;
            cout << "Edificio: " << edificioNombre << ", Nivel: " << nivel_str << ", Apartamento: " << nmro_apart_str << endl;
            encontrado = true;
            menuUsuario(edificioNombre,nivel_str,nmro_apart_str);
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

void inicio_SesionAdministrador() {
    int dni_ingresado;  
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Administrador" << endl;
    cout << "Ingrese su DNI: "; 
    cin >> dni_ingresado;
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
        string dni_str, nombre_archivo, contrasena_archivo;
        getline(ss, dni_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int dni_archivo;
        try {
            dni_archivo = stoi(dni_str);
        }
        catch (const invalid_argument& e) {
            cout << "DNI inválido en la línea: " << linea << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "DNI fuera de rango en la línea: " << linea << endl;
            continue;
        }

        if (dni_archivo == dni_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Administrador." << endl;
            encontrado = true;
            menuAdministrador(); 
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

void inicio_SesionMantenimiento() {
    int dni_ingresado;
    string nombre_ingresado, contrasena_ingresada;

    cout << "Inicio de Sesión - Mantenimiento" << endl;
    cout << "Ingrese su DNI: "; 
    cin >> dni_ingresado;
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
        string dni_str, nombre_archivo, contrasena_archivo;
        getline(ss, dni_str, ';');
        getline(ss, nombre_archivo, ';');
        getline(ss, contrasena_archivo, ';');

        int dni_archivo;
        try {
            dni_archivo = stoi(dni_str);
        }
        catch (const invalid_argument& e) {
            cout << "DNI inválido en la línea: " << linea << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "DNI fuera de rango en la línea: " << linea << endl;
            continue;
        }

        if (dni_archivo == dni_ingresado && nombre_archivo == nombre_ingresado && contrasena_archivo == contrasena_ingresada) {
            cout << "Bienvenido, " << nombre_ingresado << "! Has iniciado sesión como Personal de Mantenimiento." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: DNI, nombre de usuario o contraseña incorrectos." << endl;
    }

    archivo.close();
}

void inicio_Sesion() {
    int opcion;
    cin.ignore();
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
