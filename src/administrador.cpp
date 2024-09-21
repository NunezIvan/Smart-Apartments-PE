#pragma once
#include <iostream>
#include <fstream>
#include "edificio.cpp"
#include "propietarios.cpp"
#include "usuario_Apartamento.cpp"
using namespace std;

class administrador_Cond : public Usuario {
    private:
        Propietarios propietarios;
    public:
        
       administrador_Cond(string _nombre, string _apellido) : Usuario(_nombre, _apellido) {
        setRol_Usuario("Administrador");
        // Solo guardar si el administrador no ha sido creado antes
        if (!adminExiste(_nombre, _apellido)) {
            ofstream file("D:/Smart-Apartments-PE/data/administradores.txt", ios::app);
            if (file.is_open()) {
                file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << "\n";
                file.close();
                }   
            }
        }

    // Función para verificar si el admin ya está registrado
        bool adminExiste(string _nombre, string _apellido) {
            ifstream archivo("D:/Smart-Apartments-PE/data/administradores.txt");
            if (!archivo.is_open()) return false;
        
            string nombre_archivo, apellido_archivo;
            while (archivo >> nombre_archivo >> apellido_archivo) {
                if (nombre_archivo == _nombre && apellido_archivo == _apellido) {
                    return true;
                }
            }
            archivo.close();
            return false;
        }
        
        void registrarPropietario(vector<propietario_Apartamento>& propietarios, string nombre_propietario, string apellido_propietario) {
            propietarios.push_back(propietario_Apartamento(nombre_propietario, apellido_propietario));
            cout << "Propietario " << nombre_propietario << " registrado correctamente." << endl; 
            generarNombreUsuario();
            generarContraseña();  
            ofstream file("D:/Smart-Apartments-PE/data/propietarios.txt", ios::app);
            if (file.is_open()) {
                file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << "\n";
                file.close();
            }  
        } 

        void asignarDepartamento(Edificio& edificio, int nivel, int numero_departamento, propietario_Apartamento& propietario) {
            Departamento& dep = edificio.obtenerDepartamento(nivel, numero_departamento);
            dep.propietario = propietario.getNombre();
            cout << "Departamento " << numero_departamento << " en el nivel " << nivel 
             << " del " << edificio.nombre << " asignado a " << propietario.getNombre() << "." << endl;
        }

};


// administrador_Cond admin;

// void limpiarBuffer() {
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
// }


// void manejarPropietarios() {
//     int opcion;

//     system("cls");  // Limpiar la pantalla
//     cout << "Seleccione el tipo de usuario para iniciar sesión:" << endl;
//     cout << "1. Agregar Propietario" << endl;
//     cout << "2. Asignar propietario a departamento" << endl;
//     cout << "Ingrese su opción: ";
//     cin >> opcion;
//     limpiarBuffer(); 

//     switch (opcion) {
//         case 1: {
//             string nombrePropietario, apellidoPropietario;
//             cout << "Ingrese el nombre del nuevo propietario: ";
//             getline(cin, nombrePropietario);
//             cout << "Ingrese el apellido del nuevo propietario: ";
//             getline(cin, apellidoPropietario);

//             admin.agregarPropietario(nombrePropietario, apellidoPropietario);
//             cout << "Propietario agregado correctamente." << endl;
//             break;
//         }
//         case 2: {
//             string nombreEdificio;
//             int numNivel, numDepartamento, indicePropietario;

//             cout << "Ingrese el índice del propietario a asignar: ";
//             cin >> indicePropietario;
//             limpiarBuffer();

//             cout << "Ingrese el nombre del edificio (por ejemplo, 'a', 'b'): ";
//             getline(cin, nombreEdificio);
//             cout << "Ingrese el número de nivel: ";
//             cin >> numNivel;
//             cout << "Ingrese el número de departamento: ";
//             cin >> numDepartamento;

//             admin.asignarPropietarioADepartamento(nombreEdificio, numNivel, numDepartamento, indicePropietario);
//             break;
//         }
//         default:
//             cout << "Opción no válida." << endl;
//             break;
//     }
// }

// void menuAdministrador() {
//     fflush(stdin);
//     int opcion;
//     do {
//         cout << "=====================================" << endl;
//         cout << " BIENVENIDO AL MENU DE ADMINISTRADOR " << endl;
//         cout << "=====================================" << endl;
//         cout << "\n";
//         cout << "         1. Manejar Propietarios     " << endl;
//         cout << "         2. Salir                    " << endl;
//         cout << "\n" << endl;
//         cout << "Seleccione una opción: ";
//         cin >> opcion;
//         limpiarBuffer();  // Limpiar el búfer después de leer la opción
//         switch (opcion) {
//             case 1:
//                 manejarPropietarios();
//                 break;
//             case 2:
//                 cout << "Saliendo del programa..." << endl;
//                 break;
//             default:
//                 cout << "Opción no válida. Inténtelo de nuevo." << endl;
//                 break;
//         }
//     } while (opcion != 2);
// }





