#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "infraestructura.cpp" 
#include "usuario_Apartamento.cpp"
#include "egresos.cpp"

using namespace std;

EdificioLista crearEdificiosListaporDefecto(){
    EdificioLista edificios;
    Edificio edificio1("Edificio_1", 5, 4);
    edificios.insertarAlFinal(edificio1);
    Edificio edificio2("Edificio_2", 5, 4);
    edificios.insertarAlFinal(edificio2);
    return edificios;
}

EdificioLista edificios = crearEdificiosListaporDefecto();

DepartamentoLista cargarDepartamentos() {
    DepartamentoLista departamentosCargados;  

    ifstream archivo("departamentos.txt");
    if (!archivo.is_open()) {
        return departamentosCargados; 
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;  

        stringstream ss(linea);
        string propietario, nmro_apart_str, nro_nivel_str, nmbr_edificio;

        if (!getline(ss, propietario, ';') ||
            !getline(ss, nmro_apart_str, ';') ||
            !getline(ss, nro_nivel_str, ';') ||
            !getline(ss, nmbr_edificio)) {
            continue;  
        }

        int nmro_apartamento;
        int nro_nivel;
        try {
            nmro_apartamento = stoi(nmro_apart_str);
            nro_nivel = stoi(nro_nivel_str);
        } catch (const invalid_argument&) { continue; }
        catch (const out_of_range&) { continue; }

        Departamento nuevoDepartamento(nmro_apartamento, nro_nivel, nmbr_edificio, propietario);
        departamentosCargados.insertarAlFinal(nuevoDepartamento); 
    }

    archivo.close();
    return departamentosCargados;
}

void modificarArchivoPropietario(string nombre_Usuario, string edificioNombre, int nmro_apartamento, int nro_nivel) {
    ifstream archivo_original("departamentos.txt");
    ofstream archivo_temporal("departamentos_Temporal.txt", ios::app);

    if (!archivo_original.is_open() || !archivo_temporal.is_open()) {
        cout << "No se puede abrir uno de los archivos" << endl;  
        return;
    }

    string linea;
    bool modificado = false;

    while (getline(archivo_original, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string propietario, nmro_apart_str, nro_nivel_str, nmbr_edificio;

        if (!getline(ss, propietario, ';') ||
            !getline(ss, nmro_apart_str, ';') ||
            !getline(ss, nro_nivel_str, ';') ||
            !getline(ss, nmbr_edificio)) {
            archivo_temporal << linea << endl;
            continue;
        }

        int nmro_apartamento_arch;
        int nro_nivel_arch;
        try {
            nmro_apartamento_arch = stoi(nmro_apart_str);
            nro_nivel_arch = stoi(nro_nivel_str);
        } catch (const invalid_argument&) { 
            archivo_temporal << linea << endl; 
            continue;
        } catch (const out_of_range&) {
            archivo_temporal << linea << endl;
            continue;
        }

        if (nmro_apartamento == nmro_apartamento_arch && nro_nivel == nro_nivel_arch && nmbr_edificio == edificioNombre) {
            archivo_temporal << nombre_Usuario << ";" << nmro_apartamento << ";" << nro_nivel << ";" << nmbr_edificio << endl;
            modificado = true;
        } else {
            archivo_temporal << linea << endl;
        }
    }

    archivo_original.close();
    archivo_temporal.close();

    if (modificado) {
        if (remove("departamentos.txt") != 0) {
            cout << "Error al eliminar el archivo original" << endl;
        } else if (rename("departamentos_Temporal.txt", "departamentos.txt") != 0) {
            cout << "Error al renombrar el archivo temporal" << endl;
        }
    } else {
        remove("departamentos_Temporal.txt");
    }
}


void registrarPropietario() {
    system("cls");
    string nombre, apellido, edificioNombre;
    int nro_nivel, nmro_apartamento,DNI;

    cout << "Ingrese el DNI del propietario: ";
    cin >> DNI;
    cout << "Ingrese el nombre del propietario: ";
    cin.ignore();  
    getline(cin, nombre);
    cout << "Ingrese el apellido del propietario: ";
    getline(cin, apellido);
    cout << "Ingrese el nombre del edificio: ";
    cin >> edificioNombre;
    cout << "Ingrese el número de nivel: ";
    cin >> nro_nivel;
    cout << "Ingrese el número de apartamento: ";
    cin >> nmro_apartamento;

    EdificioNodo* edificioNode = edificios.buscar(edificioNombre);
    if (edificioNode != nullptr) {
        Edificio& edificio = edificioNode->data;
        
        DepartamentoLista depas = cargarDepartamentos();
        if (depas.verificarPropietario(nmro_apartamento,nro_nivel,edificioNombre) != nullptr) {  // Verificar si el departamento está vacío
            string nombreUsuario = nombre + "_" + apellido;
            cout << "Propietario registrado exitosamente.\n";

            usuario_Apartamento propietario(nombre, apellido, nmro_apartamento, nro_nivel, edificioNombre,DNI);

            modificarArchivoPropietario(nombreUsuario,edificioNombre,nmro_apartamento,nro_nivel);
            
        } else {
            cout << "Error: Este departamento ya tiene propietario.\n";
            cin.ignore();
        }
    } else {
        cout << "Error: Edificio no encontrado.\n";
        cin.ignore();
    }
    system("pause");
}

void mostrarEdificios(DepartamentoLista& departamentosCargados) {
    edificios.mostrarMenuEdificios(departamentosCargados);
}

void menuAdministrador() {
    
    cin.ignore();
    DepartamentoLista departamentosCargados = cargarDepartamentos();
    int opcion;
    do {
        system("cls");
        cout << "=====================================" << endl;
        cout << " BIENVENIDO AL MENU DE ADMINISTRADOR     " << endl;
        cout << "=====================================" << endl;
        cout << "1. Mostrar información de los edificios\n";
        cout << "2. Registrar un nuevo propietario\n";
        cout << "3. Gestion de control de caja \n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarEdificios(departamentosCargados);
                cin.ignore();
                break;
            case 2:
                registrarPropietario();
                break;
            case 3:
                menuElegirEdificio ();
                break;
            case 4:
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while(opcion != 4);
}
