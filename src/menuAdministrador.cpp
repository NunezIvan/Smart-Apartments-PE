#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "infraestructura.cpp" 
#include "usuario_Apartamento.cpp"
#include "egresos.cpp"
#include "menu.cpp"

using namespace std;


EdificioLista generar_Infraestructura(){
    EdificioLista edificios;
    Edificio edificio1("Edificio_1", NRO_NIVEL_EDIFICIO,NRO_DEPARTAMENTOS_NIVEL);
    edificios.insertarAlFinal(edificio1);
    Edificio edificio2("Edificio_2", NRO_NIVEL_EDIFICIO,NRO_DEPARTAMENTOS_NIVEL);
    edificios.insertarAlFinal(edificio2);
    return edificios;
}

EdificioLista edificios = generar_Infraestructura();

DepartamentoLista cargarDepartamentos() {
    DepartamentoLista departamentosCargados;  

    ifstream archivo("data/departamentos.txt");
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
    ifstream archivo_original("data/departamentos.txt");
    ofstream archivo_temporal("data/departamentos_Temporal.txt", ios::app);

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
        if (remove("data/departamentos.txt") != 0) {
            cout << "Error al eliminar el archivo original" << endl;
        } else if (rename("data/departamentos_Temporal.txt", "data/departamentos.txt") != 0) {
            cout << "Error al renombrar el archivo temporal" << endl;
        }
    } else {
        remove("data/departamentos_Temporal.txt");
    }
}

void registrarPropietario() {
    system("cls");
    DepartamentoLista depas = cargarDepartamentos();
    printtitle();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░REGISTRO DE PROPIETARIO░▒▓█▇▆▅▄▃▂" << endl;
    string nombre, apellido, edificioNombre;
    int nro_nivel, nmro_apartamento,DNI;
    gotoxy(45,16);
    cout << "Ingrese el DNI del propietario: ";
    cin >> DNI;
    gotoxy(45,17);
    cout << "Ingrese el nombre del propietario: ";
    cin.ignore();  
    getline(cin, nombre);
    gotoxy(45,18);
    cout << "Ingrese el apellido del propietario: ";
    getline(cin, apellido);
    gotoxy(45,19);
    cout << "Ingrese el nombre del edificio: ";
    cin >> edificioNombre;
    gotoxy(45,20);
    cout << "Ingrese el número de nivel: ";
    cin >> nro_nivel;
    gotoxy(45,21);
    cout << "Ingrese el número de apartamento: ";
    cin >> nmro_apartamento;

    EdificioNodo* edificioNode = edificios.buscar(edificioNombre);
    if (edificioNode != nullptr) {
        Edificio& edificio = edificioNode->data;
        NivelNodo* NivelNode = edificio.niveles.buscar(nro_nivel);
        if(NivelNode !=nullptr){
            Nivel& nivel = NivelNode->data;
            DepartamentoNodo* departamentoNode = nivel.departamentos.buscar(nmro_apartamento);
            if(departamentoNode!=nullptr){
                if(depas.verificarPropietario(nmro_apartamento,nro_nivel,edificioNombre) != nullptr){
                    string nombreUsuario = nombre + "_" + apellido;
                    gotoxy(48,22);
                    cout << "Propietario registrado exitosamente.\n";
                    usuario_Apartamento propietario(nombre, apellido, nmro_apartamento, nro_nivel, edificioNombre,DNI);
                    modificarArchivoPropietario(nombreUsuario,edificioNombre,nmro_apartamento,nro_nivel);
                    cin.ignore();
                }else{
                    gotoxy(48,22);
                    cout << "Error: Este departamento ya tiene propietario.\n";
                    cin.ignore();
                }
            }else{
                gotoxy(48,22);
                cout<<"Error: Departamento no encontrado.";
                cin.ignore();
            }
        }else{
            gotoxy(48,22);
            cout<< "Error: Nivel no encontrado. ";
            cin.ignore();
        }
    } else {
        gotoxy(48,22);
        cout << "Error: Edificio no encontrado.\n";
        cin.ignore();
    }
    cin.get();
}

void mostrarMenuEdificios(DepartamentoLista& departamentosCargados) {
    system("cls");
    printtitle();
    DepartamentoNodo* actual = departamentosCargados.cabeza;

    if (actual == nullptr) {
        gotoxy(40, 14);
        cout << "No hay departamentos cargados." << endl;
        return;
    }

    gotoxy(40, 14);
    cout << "▂▃▄▅▆▇█▒▐▓SELECCION DE EDIFICIOS▓▐█▇▆▅▄▃▂" << endl;
    gotoxy(40, 16);
    cout << "1. Edificio_1";
    gotoxy(40, 17);
    cout << "2. Edificio_2";

    int seleccion;
    gotoxy(40, 18);
    cout << "Seleccione el número de edificio: ";
    cin >> seleccion;

    string edificioSeleccionado;
    switch (seleccion) {
        case 1:
            edificioSeleccionado = "Edificio_1";
            break;
        case 2:
            edificioSeleccionado = "Edificio_2";
            break;
        default:
            cout << "Selección no válida." << endl;
            return;
    }

    system("cls");
    printtitle1();
    gotoxy(40, 11);
    cout << "▂▃▄▅▆▇█▒▐▓" << edificioSeleccionado << "▓▐█▇▆▅▄▃▂" << endl;

    int xPositionBase1 = 8; 
    int xPositionBase2 = 42; 
    int xPositionBase3 = 76;
    int yPositionBase = 13; 

    for (int nivel = 1; nivel <= NRO_NIVEL_EDIFICIO; ++nivel) {
        int xPosition;
        if (nivel == 1 || nivel == 2) {
            xPosition = xPositionBase1;  
        } else if (nivel == 3 || nivel == 4) {
            xPosition = xPositionBase2; 
        } else {
            xPosition = xPositionBase3; 
        }
        int yPosition = yPositionBase + ((nivel == 2 || nivel == 4) ? 6 : 0);

        gotoxy(xPosition, yPosition);
        cout << "Nivel " << nivel << ":";

        DepartamentoNodo* cabezaOrdenada = nullptr;

        actual = departamentosCargados.cabeza;
        while (actual != nullptr) {
            if (actual->data.nmbr_edificio == edificioSeleccionado && actual->data.nro_nivel == nivel) {
                DepartamentoNodo* nuevoNodo = new DepartamentoNodo(actual->data);
                if (!cabezaOrdenada || cabezaOrdenada->data.nmro_apartamento > nuevoNodo->data.nmro_apartamento) {
                    nuevoNodo->siguiente = cabezaOrdenada;
                    cabezaOrdenada = nuevoNodo;
                } else {
                    DepartamentoNodo* actualOrdenado = cabezaOrdenada;
                    while (actualOrdenado->siguiente && actualOrdenado->siguiente->data.nmro_apartamento < nuevoNodo->data.nmro_apartamento) {
                        actualOrdenado = actualOrdenado->siguiente;
                    }
                    nuevoNodo->siguiente = actualOrdenado->siguiente;
                    actualOrdenado->siguiente = nuevoNodo;
                }
            }
            actual = actual->siguiente;
        }

        actual = cabezaOrdenada;
        int deptCount = 1; 
        while (actual != nullptr) {
            gotoxy(xPosition, yPosition + deptCount);
            cout << actual->data.nmro_apartamento << ". Propietario: "
                 << (actual->data.propietario == "Sin_propietario" ? "Libre" : actual->data.propietario);
            deptCount++;
            DepartamentoNodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }

        if (!cabezaOrdenada) {
            gotoxy(xPosition, yPosition + 1);
            cout << "(No hay departamentos en este nivel)";
        }
    }

    cin.get();
}

void buscarPropietarioPorDNI() {
    char opcion;
    int fila;
    
    do {
        system("cls");
        int dniBuscado;
        gotoxy(40, 8);
        cout << "╔═══════════════════════════════════════════════════╗" << endl;
        gotoxy(40, 9);
        cout << "║              BUSCAR PROPIETARIO POR DNI           ║" << endl;
        gotoxy(40, 10);
        cout << "╚═══════════════════════════════════════════════════╝" << endl;
        
        gotoxy(45, 12);
        cout << "Ingrese el DNI del propietario: ";
        cin >> dniBuscado;
        cin.ignore();  

        ifstream archivo("data/propietarios.txt");
        if (!archivo.is_open()) {
            gotoxy(45, 14);
            cout << "Error al abrir el archivo de propietarios.\n";
            return;
        }

        string linea;
        bool encontrado = false;

        gotoxy(40, 16);
        cout << "╔═══════════════════════════════════════════════════╗" << endl;
        gotoxy(40, 17);
        cout << "║              DETALLES DEL PROPIETARIO             ║" << endl;
        gotoxy(40, 18);
        cout << "╚═══════════════════════════════════════════════════╝" << endl;

        int fila = 20; 

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string dni_str, nombre, contrasena, nro_nivel_str, nmro_apart_str, nmbr_edificio;

            if (!getline(ss, dni_str, ';') ||
                !getline(ss, nombre, ';') ||
                !getline(ss, contrasena, ';') ||
                !getline(ss, nro_nivel_str, ';') ||
                !getline(ss, nmro_apart_str, ';') ||
                !getline(ss, nmbr_edificio)) {
                continue;
            }

            int dni;
            try {
                dni = stoi(dni_str);
            } catch (const invalid_argument&) { continue; }

            if (dni == dniBuscado) {
                gotoxy(45, fila);
                cout << "DNI: " << dni_str 
                     << " | Nombre: " << nombre << endl;

                gotoxy(45, fila + 1);
                cout << "Apartamento: " << nmro_apart_str 
                     << " | Nivel: " << nro_nivel_str << endl;

                gotoxy(45, fila + 2);
                cout << "Edificio: " << nmbr_edificio << endl;

                fila += 4; 
                encontrado = true;
            }
        }

        if (!encontrado) {
            gotoxy(45, fila);
            cout << "No se encontró un propietario con el DNI: " << dniBuscado << endl;
        } else {
            gotoxy(40, fila + 1);
            cout << "╚═══════════════════════════════════════════════════╝" << endl;
        }

        archivo.close();

       
        gotoxy(45, fila + 3);
        cout << "¿Desea buscar otro propietario? (s/n): ";
        cin >> opcion;
        cin.ignore(); 

    } while (opcion == 's' || opcion == 'S'); 

    gotoxy(45, fila + 5);
    cin.get(); 
}


void menuAdministrador() {
    system("cls");
    int opcion;
    do {
        DepartamentoLista departamentosCargados = cargarDepartamentos();
        printtitle();
        gotoxy(40,14);
        cout <<"▂▃▄▅▆▇█▓▒░MENU DE ADMINISTRADOR░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(41,16);
        cout << "1. Mostrar información de los edificios";
        gotoxy(41,17);
        cout << "2. Registrar un nuevo propietario";
        gotoxy(41,18);
        cout << "3. Buscar propietario";
        gotoxy(41,19);
        cout << "4. Gestion de control de caja";
        gotoxy(41,20);
        cout << "0. Salir";
        gotoxy(41,21);
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarMenuEdificios(departamentosCargados);
                cin.ignore();
                break;
            case 2:
                registrarPropietario();
                break;
            case 3:
                buscarPropietarioPorDNI();
                break;
            case 4:
                menuElegirEdificio ();
                break;
            case 0:
                break;
            default:
                gotoxy(48,21);
                cout << "Opción no válida.\n";
                cin.get();
                break;
        }
    } while(opcion != 0);
}
