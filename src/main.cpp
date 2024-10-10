#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <locale>
#include "menu.cpp"
#include "login.cpp"
#include "administrador.cpp"

using namespace std;

void crearCarpeta_Data() {
    const char* carpeta = "data";
    struct stat info;

    if (stat(carpeta, &info) != 0) {
        if (mkdir(carpeta) == 0) {
            cout << "Carpeta '" << carpeta << "' creada exitosamente." << endl;
        } else {
            cerr << "Error al crear la carpeta '" << carpeta << "'." << endl;
        }
    } else {
        cout << "La carpeta '" << carpeta << "' ya existe." << endl;
    }
}

void crearArchivosDefecto() {
    crearCarpeta_Data(); // Asegurarse de que la carpeta "data" exista antes de crear los archivos.

    ofstream archivo1("data/propietarios.txt", ios::out | ios::app);
    if (archivo1.is_open()) {
        archivo1.close();
    }
    else {
        cout << "Error al crear 'propietarios.txt'.\n";
    }

    ofstream archivo2("data/administradores.txt", ios::out | ios::app);
    if (archivo2.is_open()) {
        archivo2.close();
    }
    else {
        cout << "Error al crear 'administradores.txt'.\n";
    }

    ofstream archivo3("data/mantenimiento.txt", ios::out | ios::app);
    if (archivo3.is_open()) {
        archivo3.close();
    }
    else {
        cout << "Error al crear 'mantenimiento.txt'.\n";
    }

    ofstream archivo4("data/departamentos.txt", ios::out | ios::app);
    if (archivo4.is_open()) {
        archivo4.close();
    }
    else {
        cout << "Error al crear 'departamentos.txt'.\n";
    }
}

void Administrador_por_defecto(){
    ifstream archivo("data/administradores.txt");
    if (!archivo.is_open()) {
        cout << "El archivo no existe." << endl;
    }
    string linea;
    int lineCount = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {  
            lineCount++;
        }
    }
    if(lineCount==0){
        administrador_Cond admin("ADMIN","1",72167843);
    }
}

void opciones_Inicio(){
    system("cls");
    int opc;
    bool continuar = true;
    while(continuar){
        printtitle();
        gotoxy(40,14);
        cout <<"▂▃▄▅▆▇█▓▒░MENU DE INICIO░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(48,16);
        cout <<"1. Inicio de sesion";
        gotoxy(48,17);
        cout <<"2. Salir";
        gotoxy(48,18);
        cout<<"Eliga una opcion: "; cin>>opc;
        switch (opc){
            case 1:
                inicio_Sesion();
                break;
            case 2:
                continuar = false;
                break;
            default:
                gotoxy(48,19);
                cout<<"Opcion incorrecta"<<endl;
                gotoxy(48,20);
                system("pause");
                break;
        }
    }
}

int main() {

    crearArchivosDefecto();
    Administrador_por_defecto();
    opciones_Inicio();
    cin.ignore();
    return 0;
}
