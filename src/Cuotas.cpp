#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits> // Para numeric_limits

using namespace std;

// Declaración de estructuras y clases
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

// Declaración de las funciones
void calcularCuotaGeneral();
void calcularCuotaEspecifica(string& _mes, string& _edificios, int& _cantidadPersonas, float& _montoGen);
int calcularMontoGeneral(float& monto, string& mes, string& edificio);
void mostrarCuotasGenerales();
void mostrarCuotasEspecificas();
int busquedaContador(int& contador);
vector<string> split(const string& str, char delim);

// Definición de métodos de clase
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
    cout << "Lista de cuotas" << endl;
    while (temp != nullptr) {
        cout << temp->data.Cuota << " , " << temp->data.mes << " , " << temp->data.monto << " , " 
             << temp->data.edificio << " , " << temp->data.nivel << " , " << temp->data.apartamento 
             << " , " << (temp->data.nopagado ? "Si" : "No ") << endl;
        temp = temp->siguiente;
    }

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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
            encontrado = true;
            return;
        }
        temp = temp->siguiente;
    }
    if (!encontrado) {
        cout << "No se encontró la cuota" << endl;
    }

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void listaCuota::mostrarCuotasNoPagadas() {
    if (cabeza == nullptr) {
        cout << "No hay cuotas disponibles" << endl;
        return; 
    }

    nodoCuota* temp = cabeza; 
    bool hayCuotasnoPagadas = false; 

    cout << "Lista de cuotas a pagar: " << endl;
    while (temp != nullptr) {
        if (temp->data.nopagado) {
            cout << temp->data.Cuota << " , " << temp->data.mes << " , " << temp->data.monto << " , " 
                 << temp->data.edificio << " , " << temp->data.nivel << " , " << temp->data.apartamento 
                 << " , " << "Si" << endl;
            hayCuotasnoPagadas = true; 
        }
        temp = temp->siguiente;
    }
    if (!hayCuotasnoPagadas) {
        cout << "No hay cuotas no pagadas" << endl;
    }

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

listaCuota::~listaCuota() {
    nodoCuota* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    } 
}

// Definición de las funciones
void calcularCuotaGeneral(string mes, string edificio) {
    int cantidadPersonas; 
    float monto;
    ofstream archivo("Cuota_General.txt", ios::app);

    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    calcularMontoGeneral(monto, mes, edificio);
    busquedaContador(cantidadPersonas);
    calcularCuotaEspecifica(mes, edificio, cantidadPersonas, monto);
    archivo << "Cuota" << ';' << edificio << ';' << mes << ';' << monto << ';' << cantidadPersonas << endl;

    archivo.close();

    // Mostrar mensaje y esperar
    cout << "Cuota Calculada correctamente" << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void calcularCuotaEspecifica(string& _mes, string& _edificios, int& _cantidadPersonas, float& _montoGen) {
    listaCuota lista;
    float montoRepartido = _montoGen / _cantidadPersonas; 
    cuotas cuota;
    ifstream archivo("propietarios.txt", ios::in);
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
    lista.guardadoArchivo("cuotas_Personales.txt");
    archivo.close();

    // Mostrar mensaje y esperar
    cout << "Cuotas específicas calculadas y guardadas correctamente" << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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
    ifstream archivo("egresos.txt", ios::in);
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

int busquedaContador(int& contador) {
    ifstream archivo("propietarios.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "Error, archivo no cargado" << endl;
        cout << "Cerrando programa";
        exit(1);
    }
    contador = 0;
    string inquilino;
    while (getline(archivo, inquilino)) {
        if (!inquilino.empty() && inquilino.find_first_not_of(";") != string::npos) {
            contador++;
        }
    }
    archivo.close();
    return contador;
}

void mostrarCuotasGenerales() {
    ifstream archivo("Cuota_General.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    cout << "Datos cuota general" << endl;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string cuota, edificio, mes, monto;

        getline(ss, cuota, ';');
        getline(ss, edificio, ';');
        getline(ss, mes, ';');
        getline(ss, monto, ';');

        cout << "Cuota: " << cuota << endl;
        cout << "Edificio: " << edificio << endl;
        cout << "Mes: " << mes << endl;
        cout << "Monto: " << monto << endl;
    }
    archivo.close();

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarCuotasEspecificas() {
    cuotas cuota;
    listaCuota lista;

    ifstream archivo("cuotas_Personales.txt", ios::in);
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

    // Limpiar el buffer y esperar a que el usuario presione Enter
    cout << "Presione cualquier tecla para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
