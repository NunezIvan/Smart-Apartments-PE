#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "infraestructura.cpp" 
#include "usuario_Apartamento.cpp"
#include "egresos.cpp"
#include "menu.cpp"

using namespace std;

struct propietarioNodo {
    usuario_Apartamento dato;
    propietarioNodo* sgte;
};

void push(propietarioNodo*& pila, usuario_Apartamento propietario) {
    propietarioNodo* nuevo = new propietarioNodo();
    nuevo->dato = propietario;
    nuevo->sgte = pila;
    pila = nuevo;
}

usuario_Apartamento pop(propietarioNodo*& pila) {
    if (pila == nullptr) {
        cout << "Se guardaron los cambios" << endl;
        return usuario_Apartamento("", "", 0, 0, "", 0, false); // Objeto vacío
    } else {
        usuario_Apartamento propietario = pila->dato;
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
                    usuario_Apartamento propietario(nombre, apellido, nmro_apartamento, nro_nivel, edificioNombre,DNI,true);
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

void registrarAdmin(){
    system("cls");
    printtitle();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░REGISTRO DE ADMINISTRADOR░▒▓█▇▆▅▄▃▂" << endl;
    string nombre, apellido, edificioNombre;
    int DNI;
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
    administrador_Cond admin_nuevo(nombre,apellido,DNI);
    gotoxy(45,20);
    cout<<"ADMINISTRADOR AGREGADO CORRECTAMENTE";
    cin.ignore();
}

void cambiarContrasena() {
    system("cls");
    printtitle();
    gotoxy(40, 14);
    cout << "▂▃▄▅▆▇█▓▒░CAMBIAR CONTRASENA░▒▓█▇▆▅▄▃▂" << endl;
    
    string dni_usuario, contrasena_actual, nueva_contrasena;
    gotoxy(45, 16);
    cout << "Ingrese su DNI: ";
    cin >> dni_usuario;
    
    gotoxy(45, 17);
    cout << "Ingrese su contrasena actual: ";
    cin >> contrasena_actual;
    
    ifstream archivo_lectura("data/administradores.txt");
    ofstream archivo_temporal("data/administradores_temp.txt", ios::app);
    
    if (!archivo_lectura.is_open() || !archivo_temporal.is_open()) {
        gotoxy(45, 19);
        cout << "No se pudo acceder al archivo de administradores." << endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    string linea;
    bool contrasena_modificada = false;
    while (getline(archivo_lectura, linea)) {
        if (linea.empty()) continue;
        
        stringstream ss(linea);
        string dni_archivo, nombre_archivo, contrasena_archivo;
        
        if (!getline(ss, dni_archivo, ';') ||
            !getline(ss, nombre_archivo, ';') ||
            !getline(ss, contrasena_archivo)) {
            archivo_temporal << linea << endl;
            continue;
        }
        

        if (dni_usuario == dni_archivo && contrasena_actual == contrasena_archivo) {
            gotoxy(45, 18);
            cout << "Ingrese la nueva contrasena: ";
            cin >> nueva_contrasena;
            archivo_temporal << dni_archivo << ";" << nombre_archivo << ";" << nueva_contrasena << endl;
            contrasena_modificada = true;
        } else {
            archivo_temporal << linea << endl;
        }
    }
    
    archivo_lectura.close();
    archivo_temporal.close();
    
    if (contrasena_modificada) {
        if (remove("data/administradores.txt") != 0) {
            gotoxy(45, 20);
            cout << "Error al eliminar el archivo original." << endl;
        } else if (rename("data/administradores_temp.txt", "data/administradores.txt") != 0) {
            gotoxy(45, 20);
            cout << "Error al renombrar el archivo temporal." << endl;
        } else {
            gotoxy(45, 20);
            cout << "Contrasena cambiada exitosamente." << endl;
        }
    } else {
        remove("data/administradores_temp.txt");
        gotoxy(45, 20);
        cout << "DNI o contrasena incorrecta." << endl;
    }
    
    cin.ignore();
    cin.get();
}

void buscarPropietarioPorDNI() {
    char opcion;
    do {
        system("cls");
        int dniBuscado;
        gotoxy(35, 8);
        cout << "╔═══════════════════════════════════════════════════╗" << endl;
        gotoxy(35, 9);
        cout << "║              BUSCAR PROPIETARIO POR DNI           ║" << endl;
        gotoxy(35, 10);
        cout << "╚═══════════════════════════════════════════════════╝" << endl;
        
        gotoxy(35, 12);
        cout << "Ingrese el DNI del propietario: ";
        cin >> dniBuscado;
        cin.ignore();  

        ifstream archivo("data/propietarios.txt");
        if (!archivo.is_open()) {
            gotoxy(35, 14);
            cout << "Error al abrir el archivo de propietarios.\n";
            return;
        }

        string linea;
        bool encontrado = false;

        gotoxy(35, 16);
        cout << "╔═══════════════════════════════════════════════════╗" << endl;
        gotoxy(35, 17);
        cout << "║              DETALLES DEL PROPIETARIO             ║" << endl;
        gotoxy(35, 18);
        cout << "╚═══════════════════════════════════════════════════╝" << endl;

        int fila = 20; 

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string dni_str, nombre, contrasena, nro_nivel_str, nmro_apart_str, nmbr_edificio;

            if (!getline(ss, dni_str, ';') ||
                !getline(ss, nombre, ';') ||
                !getline(ss, contrasena, ';') ||
                !getline(ss, nmro_apart_str, ';') ||
                !getline(ss, nro_nivel_str, ';') ||
                !getline(ss, nmbr_edificio)) {
                continue;
            }

            int dni;
            try {
                dni = stoi(dni_str);
            } catch (const invalid_argument&) { continue; }

            if (dni == dniBuscado) {
                gotoxy(35, fila);
                cout << "DNI: " << dni_str 
                     << " | Nombre: " << nombre << endl;

                gotoxy(35, fila + 1);
                cout << "Apartamento: " << nmro_apart_str 
                     << " | Nivel: " << nro_nivel_str << endl;

                gotoxy(35, fila + 2);
                cout << "Edificio: " << nmbr_edificio << endl;

                fila += 4; 
                encontrado = true;
            }
        }

        if (!encontrado) {
            gotoxy(40, fila);
            cout << "No se encontró un propietario con el DNI: " << dniBuscado << endl;
        } else {
            gotoxy(35, fila + 1);
            cout << "╚═══════════════════════════════════════════════════╝" << endl;
        }

        archivo.close();

       
        gotoxy(35, fila + 3);
        cout << "¿Desea buscar otro propietario? (s/n): ";
        cin >> opcion;
        cin.ignore(); 

    } while (opcion == 's' || opcion == 'S'); 
    cin.get(); 
}

void CambioPropietario() {
    ifstream archivo("data/propietarios.txt", ios::in);
    ofstream temporal("data/propietarios_temp.txt", ios::out);
    propietarioNodo* pila = nullptr;
    bool encontrado = false;
    string DNI_buscar, DNI_aux, linea, nombre, apellido, nombre_edificio_aux;
    int num_apartamento = 0, num_nivel = 0;

    if (!archivo.is_open() || !temporal.is_open()) {
        cout << "Fallo al abrir los archivos" << endl;
        return;
    }
    system("cls");
    printtitle();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░CAMBIO DE PROPIETARIO░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(40, 16);
    cout << "Ingrese el DNI del propietario que desea cambiar: ";
    cin >> DNI_buscar;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni_str, nombreUsuario, contrasena, nmro_apart_str, nivel_str, edificio;
        getline(ss, dni_str, ';');
        getline(ss, nombreUsuario, ';');
        getline(ss, contrasena, ';');
        getline(ss, nmro_apart_str, ';');
        getline(ss, nivel_str, ';');
        getline(ss, edificio, ';');

        int dni = stoi(dni_str);
        int nmro_apart = stoi(nmro_apart_str);
        int nivel = stoi(nivel_str);

        if (dni_str == DNI_buscar) {
            encontrado = true;
            gotoxy(40, 18);
            cout << "PERSONA ENCONTRADA" << endl;
            gotoxy(40, 19);
            cout << "-----------------------" << endl;
            gotoxy(40, 20);
            cout << "DNI: " << dni_str << endl;
            gotoxy(40, 21);
            cout << "Usuario: " << nombreUsuario << endl;
            gotoxy(40, 22);
            cout << "Edificio: " << edificio << endl;
            gotoxy(40, 23);
            cout << "Nivel: " << nivel << endl;
            gotoxy(40, 24);
            cout << "Apartamento: " << nmro_apart << endl;
            gotoxy(40, 25);
            cout << "-----------------------" << endl;
            gotoxy(40,27);
            system("pause");

            printtitle();
            gotoxy(40,14);
            cout <<"▂▃▄▅▆▇█▓▒░CAMBIO DE PROPIETARIO░▒▓█▇▆▅▄▃▂" << endl;
            gotoxy(40, 16);
            cout << "Ingrese el DNI del nuevo propietario: ";
            cin >> DNI_aux;
            gotoxy(40, 17);
            cout << "Ingrese el nombre del nuevo propietario: ";
            cin >> nombre;
            gotoxy(40, 18);
            cout << "Ingrese el apellido del nuevo propietario: ";
            cin >> apellido;

            usuario_Apartamento nuevoPropietario(nombre, apellido, nmro_apart, nivel, edificio, stoi(DNI_aux), false);
            push(pila, nuevoPropietario);
            nombre_edificio_aux = edificio;
            num_apartamento = nmro_apart;
            num_nivel = nivel;

            gotoxy(40,20);
            cout << "Propietario cambiado con exito" << endl;
            gotoxy(40,22);
            system("pause");
        } else {
            usuario_Apartamento propietario(nombreUsuario, nombreUsuario, nmro_apart, nivel, edificio, dni, false);
            push(pila, propietario);
        }
    }
    archivo.close();
    if (!encontrado) {
        gotoxy(40, 18);
        cout << "No se encontró un propietario con el DNI: " << DNI_buscar << endl;
        remove("data/propietarios_temp.txt");
    } else {
        while (pila != nullptr) {
            usuario_Apartamento propietario_aux = pop(pila);
            temporal << propietario_aux.getDNI_Usuario() << ";" << propietario_aux.getNom_Usuario() << ";" 
                     << propietario_aux.getContr_Usuario() << ";" << propietario_aux.getApartamento() 
                     << ";" << propietario_aux.getNivel() << ";" << propietario_aux.getNombreEdificio() << endl;
        }
        temporal.close();
        remove("data/propietarios.txt");
        rename("data/propietarios_temp.txt", "data/propietarios.txt");
        modificarArchivoPropietario(nombre + "_" + apellido, nombre_edificio_aux, num_apartamento, num_nivel);
    }
}

void menuAdministrador(string nombre_Admin) {
    system("cls");
    int opcion;
    if(nombre_Admin == "ADMIN_MASTER"){
        do {
            DepartamentoLista departamentosCargados = cargarDepartamentos();
            printtitle();
            gotoxy(40,14);
            cout <<"▂▃▄▅▆▇█▓▒░MENU DE ADMINISTRADOR░▒▓█▇▆▅▄▃▂" << endl;
            gotoxy(41,16);
            cout<<  "1. Registrar Administrador";
            gotoxy(41,17);
            cout << "2. Mostrar información de los edificios";
            gotoxy(41,18);
            cout << "3. Registrar un nuevo propietario";
            gotoxy(41,19);
            cout << "4. Buscar propietario";
            gotoxy(41,20);
            cout << "5. Cambiar propietario";
            gotoxy(41,21);
            cout << "6. Gestion de control de caja";
            gotoxy(41,22);
            cout << "7. Cambiar contraseña";
            gotoxy(41,23);
            cout << "8. Salir";
            gotoxy(41,24);
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch(opcion) {
                case 1:
                    registrarAdmin();
                    break;
                case 2:
                    mostrarMenuEdificios(departamentosCargados);
                    cin.ignore();
                    break;
                case 3:
                    registrarPropietario();
                    break;
                case 4:
                    buscarPropietarioPorDNI();
                    break;
                case 5:
                    CambioPropietario();
                    break;
                case 6:
                    menuElegirEdificio();
                    break;
                case 7:
                    cambiarContrasena();
                    break;
                case 8:
                    break;
                default:
                    gotoxy(48,26);
                    cout << "Opción no válida.\n";
                    cin.get();
                    break;
            }
        } while(opcion != 8);
    }else{
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
            cout << "4. Buscar propietario";
            gotoxy(41,20);
            cout << "5. Cambiar propietario";
            gotoxy(41,21);
            cout << "6. Cambiar contraseña";
            gotoxy(41,22);
            cout << "7. Salir";
            gotoxy(41,23);
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
                    menuElegirEdificio();
                    break;
                case 4:
                    buscarPropietarioPorDNI();
                    break;
                case 5:
                    CambioPropietario();
                    break;
                case 6:
                    cambiarContrasena();
                    break;
                case 7:
                    break;
                default:
                    gotoxy(48,25);
                    cout << "Opción no válida.\n";
                    cin.get();
                    break;
            }
        } while(opcion != 7);
    }
}