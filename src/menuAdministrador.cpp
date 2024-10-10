#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "infraestructura.cpp" 
#include "usuario_Apartamento.cpp"
#include "egresos.cpp"
#include "menu.cpp"

using namespace std;
struct Propietario{
    string DNI;
    string nombre_Usuario;
    string contraseña;
    string apartamento;
    string nivel;
    string nombre_edificio;
};

struct propietarioNodo{
    Propietario dato;
    propietarioNodo* sgte;
};

void push(propietarioNodo*& pila, Propietario propietario){
    propietarioNodo* nuevo = new propietarioNodo();
    nuevo->dato = propietario;
    nuevo->sgte = pila;
    pila = nuevo;
}

Propietario pop(propietarioNodo*& pila){
    if(pila==nullptr){
        cout<<"Se guardaron los cambios"<<endl;
        return {};
    }else{
        Propietario propietario = pila->dato;
        propietarioNodo* aux = pila;
        pila = pila->sgte;
        delete aux;
        return propietario;
    }
}

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

void CambioPropietario() {
    ifstream archivo("data/propietarios.txt", ios::in);
    ofstream temporal("data/propietarios_temp.txt", ios::app);
    propietarioNodo* pila = nullptr;
    Propietario propietario;
    bool encontrado = false;
    string DNI_buscar, DNI_aux, linea, aux_nombre_Usuario, nombre, apellido, nombre_edificio_aux;
    int num_apartamento = 0, num_nivel = 0;

    if (!archivo.is_open() || !temporal.is_open()) {
        cout << "Fallo al abrir los archivos" << endl;
        return;
    }
    system("cls");
    printtitle();
    gotoxy(40,14);
    cout << "Ingrese el DNI del propietario que desea cambiar: ";
    cin >> DNI_buscar;

    while (getline(archivo, linea)) { 
        stringstream ss(linea);
        getline(ss, propietario.DNI, ';');
        getline(ss, propietario.nombre_Usuario, ';');
        getline(ss, propietario.contraseña, ';');
        getline(ss, propietario.apartamento, ';');
        getline(ss, propietario.nivel, ';');
        getline(ss, propietario.nombre_edificio, ';');

        if (propietario.DNI == DNI_buscar) {
            encontrado = true;
            gotoxy(40,14);
            cout << "PERSONA ENCONTRADA" << endl;
            gotoxy(40,15);
            cout << "-----------------------" << endl;
            gotoxy(40,16);
            cout << "DNI: " << propietario.DNI << endl;
            gotoxy(40,17);
            cout << "Usuario: " << propietario.nombre_Usuario << endl;
            gotoxy(40,18);
            cout << "Edificio: " << propietario.nombre_edificio << endl;
            gotoxy(40,19);
            cout << "Nivel: " << propietario.nivel << endl;
            gotoxy(40,20);
            cout << "Apartamento: " << propietario.apartamento << endl;
            gotoxy(40,21);
            cout << "-----------------------" << endl;

            gotoxy(40,25);
            cout << "Ingrese el DNI del nuevo propietario: ";
            cin >> DNI_aux;
            gotoxy(40,26);
            cout << "Ingrese el nombre del nuevo propietario: ";
            cin >> nombre;
            gotoxy(40,26);
            cout << "Ingrese el apellido del nuevo propietario: ";
            cin >> apellido;

            
            aux_nombre_Usuario = nombre + "_" + apellido;
            propietario.DNI = DNI_aux;
            propietario.nombre_Usuario = aux_nombre_Usuario;
            
            nombre_edificio_aux = propietario.nombre_edificio;
            num_apartamento = stoi(propietario.apartamento);
            num_nivel = stoi(propietario.nivel);
            gotoxy(40,27);
            cout << "Propietario modificado con éxito" << endl;
        } 
        
        push(pila, propietario);

    }
    archivo.close();

    if (!encontrado) {
        gotoxy(40,15);
        cout << "No se encontró un propietario con el DNI: " << DNI_buscar << endl;
        remove("data/propietarios_temp.txt");
    } else {
        while(pila!=nullptr){
            Propietario propietario_aux = pop(pila);
            temporal << propietario_aux.DNI << ";" << propietario_aux.nombre_Usuario << ";" << propietario_aux.contraseña << ";" << propietario_aux.apartamento << ";" << propietario_aux.nivel << ";" << propietario_aux.nombre_edificio << endl;
        }
        temporal.close();
        remove("data/propietarios.txt");
        rename("data/propietarios_temp.txt", "data/propietarios.txt");
        modificarArchivoPropietario(aux_nombre_Usuario, nombre_edificio_aux, num_apartamento, num_nivel);
    }
}

void buscarPropietario(){
    ifstream archivo("data/propietarios.txt", ios::in);
    string DNI, nombre_Usuario, contraseña, apartamento, nivel, nombre_edificio, DNI_buscar, linea;
    bool busqueda = false;
    if(!archivo.is_open()){
        cout << "Fallo al abrir el archivo" << endl;
        return;
    }

    system("cls");
    printtitle();
    gotoxy(40,13);
    cout << "Ingrese el DNI del propietario que desea buscar: ";
    cin >> DNI_buscar;
    while (getline(archivo, linea)){
        stringstream ss(linea);
        getline(ss, DNI, ';');
        getline(ss, nombre_Usuario, ';');
        getline(ss, contraseña, ';');
        getline(ss, apartamento, ';');
        getline(ss, nivel, ';');
        getline(ss, nombre_edificio, ';');

        if(DNI == DNI_buscar){
            busqueda = true;
            gotoxy(40,14);
            cout << "PERSONA ENCONTRADA" << endl;
            gotoxy(40,15);
            cout << "-----------------------" << endl;
            gotoxy(40,16);
            cout << "DNI: " << DNI << endl;
            gotoxy(40,17);
            cout << "Usuario: " << nombre_Usuario << endl;
            gotoxy(40,18);
            cout << "Edificio: " << nombre_edificio << endl;
            gotoxy(40,19);
            cout << "Nivel: " << nivel << endl;
            gotoxy(40,20);
            cout << "Apartamento: " << apartamento << endl;
            gotoxy(40,21);
            cout << "-----------------------" << endl;
        }
    }
    if(!busqueda){
        gotoxy(40,14);
        cout << "No se ha encontrado un propietario con el DNI: " << DNI_buscar;
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
        cout << "3. Gestion de control de caja";
        gotoxy(41,19);
        cout << "4. Modificar Propietarios";
        gotoxy(41,20);
        cout << "5. Buscar Propietario por DNI";
        gotoxy(41,21);
        cout << "6. Salir";
        gotoxy(41,22);
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
                menuElegirEdificio ();
                break;
            case 4:
                CambioPropietario();
                break;
            case 5:
                buscarPropietario();
                break;
            case 6:
                break;
            default:
                gotoxy(48,21);
                cout << "Opción no válida.\n";
                cin.get();
                break;
        }
    } while(opcion != 6);
}
