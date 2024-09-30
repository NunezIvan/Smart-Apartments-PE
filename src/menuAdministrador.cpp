#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "infraestructura.cpp" 
#include "usuario_Apartamento.cpp"
#include "egresos.cpp"

using namespace std;

EdificioLista edificios;

DepartamentoLista cargarDepartamentos() {
    DepartamentoLista departamentosCargados;  // Lista de departamentos cargados

    ifstream archivo("departamentos.txt");
    if (!archivo.is_open()) {
        return departamentosCargados;  // Si no se puede abrir el archivo, retorna una lista vacía
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;  // Saltar líneas vacías

        stringstream ss(linea);
        string propietario, nmro_apart_str, nro_nivel_str, nmbr_edificio;

        // Obtener cada parte de la línea
        if (!getline(ss, propietario, ';') ||
            !getline(ss, nmro_apart_str, ';') ||
            !getline(ss, nro_nivel_str, ';') ||
            !getline(ss, nmbr_edificio)) {
            continue;  // Saltar si hay error en el formato
        }

        // Convertir strings a enteros con manejo de excepciones
        int nmro_apartamento;
        int nro_nivel;
        try {
            nmro_apartamento = stoi(nmro_apart_str);
            nro_nivel = stoi(nro_nivel_str);
        } catch (const invalid_argument&) { continue; }
        catch (const out_of_range&) { continue; }

        // Crear el departamento y agregarlo a la lista de departamentos
        Departamento nuevoDepartamento(nmro_apartamento, nro_nivel, nmbr_edificio, propietario);
        departamentosCargados.insertarAlFinal(nuevoDepartamento);  // Insertar en la lista enlazada
    }

    archivo.close();
    return departamentosCargados;  // Retornar la lista de departamentos cargados
}


void registrarPropietario() {
    string nombre, apellido, edificioNombre;
    int nro_nivel, nmro_apartamento;

    cout << "Ingrese el nombre del propietario: ";
    cin.ignore();  // Limpiar el buffer correctamente
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
        
        // Llamamos a la función obtenerDepartamento
        Departamento* depto = edificio.obtenerDepartamento(nro_nivel, nmro_apartamento);
        
        if (depto != nullptr) {  // Si el departamento existe
            if (!depto->tienePropietario()) {  // Verificar si el departamento está vacío
                string nombreUsuario = nombre + "_" + apellido;
                depto->propietario = nombreUsuario;
                cout << "Propietario registrado exitosamente.\n";

                // Crear el propietario y registrar en "propietarios.txt"
                usuario_Apartamento propietario(nombre, apellido, nmro_apartamento, nro_nivel, edificioNombre);

                // Registrar el departamento en "departamentos.txt"
                ofstream file("departamentos.txt", ios::app);
                if (file.is_open()) {
                    file << nombreUsuario << ";" << nmro_apartamento << ";" << nro_nivel << ";" << edificioNombre << "\n";
                    file.close();
                } else {
                    cout << "No se pudo abrir el archivo para escritura de departamentos." << endl;
                }
            } else {
                cout << "Error: Este departamento ya tiene propietario.\n";
            }
        } else {
            // Si el departamento no existe, mostrar un error
            cout << "Error: Departamento no encontrado o fuera de rango.\n";
        }
    } else {
        cout << "Error: Edificio no encontrado.\n";
    }
}



void mostrarEdificios(DepartamentoLista& departamentosCargados) {
    edificios.mostrarMenuEdificios(departamentosCargados);
}

void menuAdministrador() {
    Edificio edificio1("Edificio_1", 5, 4);
    edificios.insertarAlFinal(edificio1);
    Edificio edificio2("Edificio_2", 5, 4);
    edificios.insertarAlFinal(edificio2);

    DepartamentoLista departamentosCargados = cargarDepartamentos();

    int opcion;
    do {
        cout << "1. Mostrar información de los edificios\n";
        cout << "2. Registrar un nuevo propietario\n";
        cout << "3. Gestion de control de caja \n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarEdificios(departamentosCargados);
                break;
            case 2:
                registrarPropietario();
                break;
            case 3:
                gestionControlCaja();
                break;
            case 4:
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while(opcion != 3);
}
