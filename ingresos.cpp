#pragma once
#include <iostream>
#include "Cuotas.cpp"
#include "menu.cpp"
#include <limits>
using namespace std;

void pagoCuota(string _mes, string edificio){
    cuotas cuota;
    listaCuota lista;
    ifstream archivo("data/cuotas_Personales.txt", ios::in);
    if(archivo.fail()){
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        system("pause");
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


    printtitle();
    gotoxy(40,14);
    cout <<"▂▃▄▅▆▇█▓▒░REGISTRO DE INGRESO░▒▓█▇▆▅▄▃▂" << endl;
    string nivel, apartamento;
    float monto;
    bool encontrado = false;
    gotoxy(48,16);
    cout << "Introducir nivel: ";
    cin >> nivel;
    gotoxy(48,17);
    cout << "Introducir apartamento: ";
    cin >> apartamento;
    lista.compararCuotas(_mes, edificio, nivel, apartamento, encontrado, monto);

    int menu;
    string tipo;

    if (encontrado == true) {
        ofstream archivo("data/ingreso.txt", ios::app);
        if (archivo.fail()) {
            cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
            exit(1);
        }

        do {

            printtitle();
            gotoxy(40,14);
            cout <<"▂▃▄▅▆▇█▓▒░TIPO DE PAGO░▒▓█▇▆▅▄▃▂";
            gotoxy(48,16);
            cout << "Ingresar tipo de pago: ";
            gotoxy(48,17);
            cout << " 1.- TRANSFERENCIA BANCARIA" ;
            gotoxy(48,18);
            cout << " 2.- PAGO POR YAPE " ;
            gotoxy(48,19);
            cout << " 3.- PAGO POR EFECTIVO";
            gotoxy(48,20);
            cout << " 4.- DEPOSITO POR BCP";
            gotoxy(48,21);
            cout << " 5.- PAGO VIA WEB";
            gotoxy(48,22);
            cout << " 0.- Salir";
            gotoxy(48,24);
            cout << " Elija una opcion: ";

            cin >> menu;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (menu) {
                case 1: {
                    tipo = "Transferencia Bancaria";
                    break;
                }
                case 2: {
                    tipo = "por Yape";
                    break;
                }
                case 3: {
                    tipo = "en Efectivo";
                    break;
                }
                case 4: {
                    tipo = "en BCP";
                    break;
                }
                case 5: {
                    tipo = "Via Web";
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

        gotoxy(48,26);
        cout << "Pago registrado correctamente" << endl;
        gotoxy(48,27);
        cout << "Presione cualquier tecla para continuar..." << endl;
        cin.get();
    }
}

void mostrarIngresos() {
    ifstream archivo("data/ingreso.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error, no se pudo cargar el archivo, cerrando programa" << endl;
        exit(1);
    }

    string mes, edificio, nivel, apartamento, monto, tipo;
    string linea;

    printtitle1();  
    gotoxy(40, 11);
    cout << "▂▃▄▅▆▇█▓▒░ TABLA DE INGRESOS ░▒▓█▇▆▅▄▃▂" << endl;

    // Encabezados de la tabla
    gotoxy(17, 13);
    cout << "---------------------------------------------------------------------------------------";
    gotoxy(17, 14);
    cout << left << "| " << setw(8) << "Mes" << " | "
         << setw(10) << "Edificio" << " | "
         << setw(8) << "Nivel" << " | "
         << setw(12) << "Apartamento" << " | "
         << setw(10) << "Monto" << " | "
         << setw(20) << "Tipo de Pago" << " |";
    gotoxy(17, 15);
    cout << "---------------------------------------------------------------------------------------";

    
    int row = 16;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, mes, ';');
        getline(ss, edificio, ';');
        getline(ss, nivel, ';');
        getline(ss, apartamento, ';');
        getline(ss, monto, ';');
        getline(ss, tipo, ';');

        gotoxy(17, row);
        cout << left << "| " << setw(8) << mes << " | "
             << setw(10) << edificio << " | "
             << setw(8) << nivel << " | "
             << setw(12) << apartamento << " | "
             << "s/" << setw(8) << fixed << setprecision(2) << stof(monto) << " | "
             << setw(20) << tipo << " |";
        gotoxy(17, row + 1);
        cout << "---------------------------------------------------------------------------------------";

        row += 2;  
    }

    archivo.close();
    gotoxy(35, row + 2); 
    system("pause");
}
