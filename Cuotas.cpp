#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "menu.cpp"

using namespace std;

struct cuotas {
    string Cuota;
    string mes;
    float monto;
    string edificio;
    string nivel;
    string apartamento;
    bool nopagado;
};

struct nodoCuota {
    cuotas data;
    nodoCuota* siguiente;

    nodoCuota(const cuotas& datos) : data(datos), siguiente(nullptr) {}
};

class listaCuota {
    private:
        nodoCuota* cabeza;

    public:
        listaCuota() : cabeza(nullptr) {}

        void agregarFinal(cuotas data);
        void guardadoArchivo(const string& nombreArchivo);
        void mostrarCuotas();
        void verCuotasPersonales(string& edificio, string& nivel, string& apartamento);
        void compararCuotas(string& _mes, string& edificio, string& nivel, string& apartamento, bool& encontrado, float& monto);
        void mostrarCuotasNoPagadas();
        ~listaCuota();
};

void mostrarCuotasGenerales(string mes, string edificio);
void calcularCuotaEspecifica(string& _mes, string& _edificios, int& _cantidadPersonas, float& _montoGen);
int calcularMontoGeneral(float& monto, string& mes, string& edificio);
void mostrarCuotasEspecificas();
void tamanoInquilinos(int& contador, string edificio);
vector<string> split(const string& str, char delim);

void listaCuota::agregarFinal(cuotas data) {
    nodoCuota* nuevoNodo = new nodoCuota(data);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        nodoCuota* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

#include <iomanip> // Para manejar la precisión del monto

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void Cambio_Estado(string mes, float monto, string edificio, string nivel, string apartamento) {
    ifstream archivo("data/cuotas_Personales.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }

    // Convertimos monto a string con formato adecuado (2 decimales)
    stringstream monto_ss;
    monto_ss << fixed << setprecision(2) << monto;
    string monto_Str = monto_ss.str();

    vector<string> lineas;
    string linea;

    // Leer las líneas del archivo y modificar la correspondiente
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string cuotaArchivo, mesArchivo, montoArchivo, edificioArchivo, nivelArchivo, apartamentoArchivo, pagadoArchivo;

        // Leer los campos separados por ';'
        getline(ss, cuotaArchivo, ';');
        getline(ss, mesArchivo, ';');
        getline(ss, montoArchivo, ';');
        getline(ss, edificioArchivo, ';');
        getline(ss, nivelArchivo, ';');
        getline(ss, apartamentoArchivo, ';');
        getline(ss, pagadoArchivo, ';');

        // Comparar si coinciden los valores
        if (mesArchivo == mes && montoArchivo == monto_Str && edificioArchivo == edificio && nivelArchivo == nivel && apartamentoArchivo == apartamento) {
            // Modificar el estado de pago a 'false' si actualmente es 'true'
            if (pagadoArchivo == "true") {
                pagadoArchivo = "false";
            }
            linea = cuotaArchivo + ";" + mesArchivo + ";" + montoArchivo + ";" + edificioArchivo + ";" + nivelArchivo + ";" + apartamentoArchivo + ";" + pagadoArchivo;
        }

        lineas.push_back(linea); // Guardamos la línea original o modificada
    }

    archivo.close();

    // Abrimos el archivo de salida para sobrescribirlo
    ofstream archivo1("data/cuotas_Personales.txt", ios::out);
    if (archivo1.fail()) {
        cout << "Error al abrir archivo para escritura" << endl;
        exit(1);
    }

    // Escribir todas las líneas en el archivo, incluidas las modificadas
    for (const string& lineaEscrita : lineas) {
        archivo1 << lineaEscrita << endl;
    }

    archivo1.close();
}


void listaCuota::guardadoArchivo(const string& nombreArchivo) {
   ofstream archivo(nombreArchivo);


    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    nodoCuota* temp = cabeza;
    while (temp != nullptr) {
        archivo << temp->data.Cuota << ';' << temp->data.mes << ';' << temp->data.monto << ';'
                << temp->data.edificio << ';' << temp->data.nivel << ';'
                << temp->data.apartamento << ';' << (temp->data.nopagado ? "true" : "false") << endl;

        temp = temp->siguiente;
    }
    archivo.close();
}

void listaCuota::mostrarCuotas() {
    if (cabeza == nullptr) {
        cout << "No hay cuotas disponibles" << endl;
        return;
    }

    nodoCuota* temp = cabeza;

    printtitle1();  // Llama a la función para imprimir el título
    gotoxy(40, 11);
    cout << "▂▃▄▅▆▇█▓▒░ LISTA DE CUOTAS ░▒▓█▇▆▅▄▃▂" << endl;

    // Encabezados de la tabla
    gotoxy(14, 13);
    cout << "-------------------------------------------------------------------------------------------";
    gotoxy(14, 14);
    cout << left << "| " << setw(10) << "Cuota" << " | " 
         << setw(8) << "Mes" << " | " 
         << setw(12) << "Monto" << " | " 
         << setw(10) << "Edificio" << " | " 
         << setw(8) << "Nivel" << " | " 
         << setw(12) << "Apartamento" << " | " 
         << setw(10) << "No Pagado" << "|";
    gotoxy(14, 15);
    cout << "-------------------------------------------------------------------------------------------";

    // Recorrido de las cuotas
    int row = 16; // Empezamos a imprimir desde la fila 16
    while (temp != nullptr) {
        gotoxy(14, row);
        cout << left << "| " 
             << setw(10) << temp->data.Cuota << " | " 
             << setw(8) << temp->data.mes << " | " 
             << "s/" << setw(10) << fixed << setprecision(2) << temp->data.monto << " | " 
             << setw(10) << temp->data.edificio << " | " 
             << setw(8) << temp->data.nivel << " | " 
             << setw(12) << temp->data.apartamento << " | " 
             << setw(10) << (temp->data.nopagado ? "Sí" : "No") << " |";
        gotoxy(14, row + 1);
        cout << "-------------------------------------------------------------------------------------------";

        // Incrementamos la fila para cada cuota
        row += 2;
        temp = temp->siguiente;
    }

    gotoxy(35, row + 2); // Posicionamos el cursor al final
}


void listaCuota::verCuotasPersonales(string& edificio, string& nivel, string& apartamento) {
    if (cabeza == nullptr) {
        cout << "No hay cuotas disponibles" << endl;
        return;
    }

    nodoCuota* temp = cabeza;
    while (temp != nullptr) {
        if (temp->data.edificio == edificio && temp->data.nivel == nivel && temp->data.apartamento == apartamento && temp->data.nopagado == true) {
            cout << temp->data.Cuota << endl;
            cout << temp->data.mes << endl;
            cout << temp->data.monto << endl;
            cout << "----------------------" << endl;
        }
        temp = temp->siguiente;
    }

    system("pause");
}

void listaCuota::compararCuotas(string& _mes, string& edificio, string& nivel, string& apartamento, bool& encontrado, float& monto) {
    if (cabeza == nullptr) {
        cout << "No hay cuotas disponibles" << endl;
        return;
    }

    nodoCuota* temp = cabeza;
    while (temp != nullptr) {
        if (temp->data.mes == _mes && temp->data.edificio == edificio && temp->data.nivel == nivel && temp->data.apartamento == apartamento) {
            temp->data.nopagado = false;
            monto = temp->data.monto;
            Cambio_Estado(temp->data.mes,temp->data.monto,temp->data.edificio, temp->data.nivel,temp->data.apartamento);
            encontrado = true;
            return;
        }
        temp = temp->siguiente;
    }
    if (!encontrado) {
        cout << "No se encontró la cuota" << endl;
    }

    system("pause");
}

void listaCuota::mostrarCuotasNoPagadas() {
    if (cabeza == nullptr) {
        cout << "No hay cuotas disponibles" << endl;
        return;
    }

    nodoCuota* temp = cabeza;
    bool hayCuotasNoPagadas = false;

    printtitle1();  // Llama a la función para imprimir el título
    gotoxy(40, 11);
    cout << "▂▃▄▅▆▇█▓▒░ LISTA DE CUOTAS NO PAGADAS ░▒▓█▇▆▅▄▃▂" << endl;

    // Encabezados de la tabla
    gotoxy(14, 13);
    cout << "-------------------------------------------------------------------------------------------";
    gotoxy(14, 14);
    cout << left << "| " << setw(10) << "Cuota" << " | " 
         << setw(8) << "Mes" << " | " 
         << setw(12) << "Monto" << " | " 
         << setw(10) << "Edificio" << " | " 
         << setw(8) << "Nivel" << " | " 
         << setw(12) << "Apartamento" << " | " 
         << setw(10) << "No Pagado" << " |";
    gotoxy(14, 15);
    cout << "-------------------------------------------------------------------------------------------";

    int row = 16; 
    while (temp != nullptr) {
        if (temp->data.nopagado) { 
            gotoxy(14, row);
            cout << left << "| " 
                 << setw(10) << temp->data.Cuota << " | " 
                 << setw(8) << temp->data.mes << " | " 
                 << "s/" << setw(10) << fixed << setprecision(2) << temp->data.monto << " | " 
                 << setw(10) << temp->data.edificio << " | " 
                 << setw(8) << temp->data.nivel << " | " 
                 << setw(12) << temp->data.apartamento << " | " 
                 << setw(10) << (temp->data.nopagado ? "Sí" : "No") << " |";
            gotoxy(14, row + 1);
            cout << "-------------------------------------------------------------------------------------------";
            row += 2;  
            hayCuotasNoPagadas = true;
        }
        temp = temp->siguiente;
    }

    if (!hayCuotasNoPagadas) {
        gotoxy(35, row); // Posicionamos el mensaje en la siguiente línea
        cout << "No hay cuotas no pagadas" << endl;
    }

    gotoxy(35, row + 2); // Posicionamos el cursor al final
    system("pause");
}


listaCuota::~listaCuota() {
    nodoCuota* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void mostrarCuotasGenerales(string mes, string edificio) { //OLA
    int cantidadPersonas;
    float monto;

    calcularMontoGeneral(monto, mes, edificio);
    tamanoInquilinos(cantidadPersonas,edificio);
    calcularCuotaEspecifica(mes, edificio, cantidadPersonas, monto);

    printtitle();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░CUOTA GENERAL░▒▓█▇▆▅▄▃▂" << endl;
    gotoxy(48,16);
    cout << "Edificio: " << edificio << endl;
    gotoxy(48,17);
    cout << "Mes: " << mes << endl;
    gotoxy(48,18);
    cout << "Monto: " << monto << endl;

    gotoxy(48,20);
    system("pause");
}

void calcularCuotaEspecifica(string& _mes, string& _edificios, int& _cantidadPersonas, float& _montoGen) {
    listaCuota lista;
    float montoRepartido = _montoGen / _cantidadPersonas;
    cuotas cuota;
    ifstream archivo("data/propietarios.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    string linea;
    while (getline(archivo, linea)) {
        vector<string> cadena = split(linea, ';');
        if (cadena[5] == _edificios) {
            cuota.Cuota = "cuota";
            cuota.mes = _mes;
            cuota.monto = montoRepartido;
            cuota.edificio = _edificios;
            cuota.nivel = cadena[4];
            cuota.apartamento = cadena[3];
            cuota.nopagado = true;
            lista.agregarFinal(cuota);
        }
    }
    lista.guardadoArchivo("data/cuotas_Personales.txt");
    archivo.close();

}

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int calcularMontoGeneral(float& monto, string& mes, string& edificio) {
    float monto2 = 0.0f;
    string linea;
    string _tipo;
    ifstream archivo("data/egresos.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    while (getline(archivo, linea)) {
        vector<string> cadena = split(linea, ';');
        _tipo = cadena[0];

        if (_tipo == "Limpieza" && cadena[3] == mes && cadena[6] == edificio) {
            monto2 += stof(cadena[5]);
        } else if (cadena[1] == mes && cadena[4] == edificio) {
            monto2 += stof(cadena[3]);
        }
    }

    monto = monto2;
    archivo.close();
    return 0;
}

void tamanoInquilinos(int& tamano, string edificio){
    string linea;
    tamano = 0;
    ifstream archivo("data/propietarios.txt");
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    while(getline(archivo,linea)){
        vector<string> cadena = split(linea, ';');
        if(cadena[5] ==  edificio){
            tamano ++;
        }
    }
    archivo.close();
}

void mostrarCuotasEspecificas() {
    cuotas cuota;
    listaCuota lista;

    ifstream archivo("data/cuotas_Personales.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    string linea;
    while (getline(archivo, linea)) {
        string montostr;
        string nopagadostr;
        stringstream ss(linea);

        getline(ss, cuota.Cuota, ';');
        getline(ss, cuota.mes, ';');
        getline(ss, montostr, ';');
        getline(ss, cuota.edificio, ';');
        getline(ss, cuota.nivel, ';');
        getline(ss, cuota.apartamento, ';');
        getline(ss, nopagadostr, ';');

        cuota.monto = stof(montostr);
        cuota.nopagado = (nopagadostr == "true");

        lista.agregarFinal(cuota);
    }

    archivo.close();
    lista.mostrarCuotas();
    cout <<endl;
    system("pause");
}
