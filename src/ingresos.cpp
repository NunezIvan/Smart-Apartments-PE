#pragma once
#include <iostream>
#include "Cuotas.cpp"
#include <limits>
using namespace std;

void pagoCuota(string _mes, string edificio){
    cuotas cuota;
    listaCuota lista;
    ifstream archivo("cuotas_Personales.txt", ios::in);
    if(archivo.fail()){
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }
    string linea;
    string montostr;
    while(getline(archivo, linea)){

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
    lista.mostrarCuotasNoPagadas();

    system("pause");

    string nivel, apartamento;
    float monto;
    bool encontrado = false;

    cout << "Introducir nivel: " << endl;
    cin >> nivel;
    cout << "Introducir apartamento: " << endl;
    cin >> apartamento;
    lista.compararCuotas(_mes, edificio, nivel, apartamento, encontrado, monto);

    int menu;
    string tipo;

    if (encontrado == true) {
        ofstream archivo("ingreso.txt", ios::app);
        if (archivo.fail()) {
            cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
            exit(1);
        }

        do {
            cout << "Ingresar tipo de pago: " << endl;
            cout << endl;
            cout << " 1.- TRANSFERENCIA BANCARIA" << endl;
            cout << " 2.- PAGO POR YAPE " << endl;
            cout << " 3.- PAGO POR EFECTIVO" << endl;
            cout << " 4.- DEPOSITO POR BCP" << endl;
            cout << " 5.- PAGO VIA WEB" << endl;
            cout << " 0.- Salir" << endl;
            cout << " Elija una opcion: ";

            cin >> menu; 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (menu) {
                case 1: {
                    tipo = "TRANSFERENCIA BANCARIA";
                    break;
                }
                case 2: {
                    tipo = "PAGO POR YAPE";
                    break;
                }
                case 3: {
                    tipo = "PAGO POR EFECTIVO";
                    break;
                }
                case 4: {
                    tipo = "DEPOSITO POR BCP"; 
                    break;
                }
                case 5: {
                    tipo = "VIA WEB"; 
                    break;
                }
                case 0: {
                    tipo = "Saliendo...";
                    return;
                }
                default: {
                    cout << "Valor equivocado, chao" << endl;
                    return;
                }
            }
        } while (menu < 0 || menu > 5);

        archivo << _mes << ';' << edificio << ';' << nivel << ';' << apartamento << ';' << monto << ';' << tipo << endl;
        archivo.close();

        cout << "Pago registrado correctamente" << endl;
        cout << "Presione cualquier tecla para continuar..." << endl;
        cin.get();
    }
}

void mostrarIngresos() {
    ifstream archivo("ingreso.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }
    string mes, edificio, nivel, apartamento, monto, tipo;
    string linea;
    cout << "TABLA DE INGRESOS" << endl;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, mes, ';');
        getline(ss, edificio, ';');
        getline(ss, nivel, ';');
        getline(ss, apartamento, ';');
        getline(ss, monto, ';');
        getline(ss, tipo, ';');
        cout << mes << " , " << edificio << " , " << nivel << " , " << apartamento << " , " << monto << " , " << tipo << endl;
    }
    archivo.close();

    system("pause");
}
