#include <locale.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <vector>
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
    crearCarpeta_Data(); 

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
        administrador_Cond admin("ADMIN","MASTER",72167843);
    }
}

void recuperarAdmin(){
    printtitle();
    int dni;
    string nombreUsuario, password1, password2;
    gotoxy(33,14);
    cout <<"▂▃▄▅▆▇█▓▒░RECUPERACION-ADMINISTRADOR_MASTER░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(44,16);
    cout << "Ingrese su DNI: ";  
    cin >> dni;
    gotoxy(44,17);
    cout << "Ingrese su Nombre de Usuario: ";
    cin >> nombreUsuario;
    ifstream archivo("data/administradores.txt");
    if(!archivo.is_open()){
        gotoxy(44,19);
        cout << "Error al abrir el archivo de administradores.";
        return;
    }
    int dniArchivo;
    string nombreArchivo, contrasenaArchivo;
    bool encontrado = false;
    vector<string> contenidoArchivo;
    string linea;
    
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string dniStr, nombreStr, contrasenaStr;
        
        getline(ss, dniStr, ';');
        getline(ss, nombreStr, ';');
        getline(ss, contrasenaStr, ';');
        
        dniArchivo = stoi(dniStr);
        nombreArchivo = nombreStr;
        contrasenaArchivo = contrasenaStr;
        
        if(dniArchivo == dni && nombreArchivo == nombreUsuario){
            encontrado = true;
            
            gotoxy(44,20);
            cout << "Ingrese su nueva contraseña: ";
            cin >> password1;
            
            gotoxy(44,21);
            cout << "Confirme su nueva contraseña: ";
            cin >> password2;
            
            if(password1 == password2){
                string nuevaLinea = dniStr + ";" + nombreStr + ";" + password1;
                contenidoArchivo.push_back(nuevaLinea);
                gotoxy(44,23);
                cout << "Contraseña actualizada exitosamente.";
            } else {
                gotoxy(44,23);
                cout << "Las contraseñas no coinciden.";
                return;
            }
        } else {
            contenidoArchivo.push_back(linea);
        }
    }
    
    archivo.close();
    
    if(!encontrado){
        gotoxy(44,22);
        cout << "DNI o Nombre de Usuario incorrectos.";
        return;
    }

    ofstream archivoOut("data/administradores.txt", ios::trunc);
    for(const auto& linea : contenidoArchivo){
        archivoOut << linea << "\n";
    }
    archivoOut.close();

    cin.ignore();
    cin.get();
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
            case 0:
                recuperarAdmin();
                break;
            default:
                gotoxy(48,19);
                cout<<"Opcion incorrecta"<<endl;
                gotoxy(48,20);
                cin.ignore();
                cin.get();
                break;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    crearArchivosDefecto();
    Administrador_por_defecto();
    opciones_Inicio();
    cin.ignore();
    return 0;
}