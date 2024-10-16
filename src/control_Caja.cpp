#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "menu.cpp"
#include "egresos.cpp"
//#include "Cuotas.cpp"
//#include "ingresos.cpp"

using namespace std;



void menuMeses(const string& edificio) { // Ponerla en un archivo general (Control_Caja)
    string temp_edificio = edificio;
    char opcion;
    do {
        system("CLS");
        printtitle1();
        gotoxy(40, 11); cout <<"▂▃▄▅▆▇█▓▒░GESTION DE CONTROL DE CAJA░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(40, 13); cout << " Control de caja del mes:";
        gotoxy(40, 14); cout << "  A) ENERO";
        gotoxy(40, 15); cout << "  B) FEBRERO";
        gotoxy(40, 16); cout << "  C) MARZO";
        gotoxy(40, 17); cout << "  D) ABRIL";
        gotoxy(40, 18); cout << "  E) MAYO";
        gotoxy(40, 19); cout << "  F) JUNIO";
        gotoxy(40, 20); cout << "  G) JULIO";
        gotoxy(40, 21); cout << "  H) AGOSTO";
        gotoxy(40, 22); cout << "  I) SEPTIEMBRE";
        gotoxy(40, 23); cout << "  J) OCTUBRE";
        gotoxy(40, 24); cout << "  K) NOVIEMBRE";
        gotoxy(40, 25); cout << "  L) DICIEMBRE";
        gotoxy(40, 26); cout << "  0.- Salir";
        gotoxy(40, 28); cout << " Ingrese una opcion: ";

        cin >> opcion;
        fflush(stdin);

        switch (opcion) {
            case '0':
                return;
                break;
            case 'a':
            case 'A': {
                system("CLS");
                menuControlDeCaja("Enero", temp_edificio);
                break;
            }
            case 'b':
            case 'B': {
                system("CLS");
                menuControlDeCaja("Febrero", temp_edificio);
                break;
            }
            case 'c':
            case 'C': {
                system("CLS");
                menuControlDeCaja("Marzo", temp_edificio);
                break;
            }
            case 'd':
            case 'D': {
                system("CLS");
                menuControlDeCaja("Abril", temp_edificio);
                break;
            }
            case 'e':
            case 'E': {
                system("CLS");
                menuControlDeCaja("Mayo", temp_edificio);
                break;
            }
            case 'f':
            case 'F': {
                system("CLS");
                menuControlDeCaja("Junio", temp_edificio);
                break;
            }
            case 'g':
            case 'G': {
                system("CLS");
                menuControlDeCaja("Julio", temp_edificio);
                break;
            }
            case 'h':
            case 'H': {
                system("CLS");
                menuControlDeCaja("Agosto", temp_edificio);
                break;
            }
            case 'i':
            case 'I': {
                system("CLS");
                menuControlDeCaja("Septiembre", temp_edificio);
                break;
            }
            case 'j':
            case 'J': {
                system("CLS");
                menuControlDeCaja("Octubre", temp_edificio);
                break;
            }
            case 'k':
            case 'K': {
                system("CLS");
                menuControlDeCaja("Noviembre", temp_edificio);
                break;
            }
            case 'l':
            case 'L': {
                system("CLS");
                menuControlDeCaja("Diciembre", temp_edificio);
                break;
            }
            default:
                gotoxy(35, 30); cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
        gotoxy(35, 32);
        system("pause");
    } while (opcion != '0');
}

void menuElegirEdificio() { // Ponerla en un archivo general (Control_Caja)
    char r = ' ';
    do {
        system("CLS");
        printtitle();
        gotoxy(40,14);
        cout <<"▂▃▄▅▆▇█▓▒░ELEGIR EDIFICIO░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(40, 16); cout << " 1.- EDIFICIO 1";
        gotoxy(40, 17); cout << " 2.- EDIFICIO 2";
        gotoxy(40, 18); cout << " 0.- Salir";
        gotoxy(40, 19); cout << " Elija una opcion: ";
        cin >> r;

        switch (r) {
            case '0':
                return;
                break;

            case '1':
                system("CLS");
                menuMeses("Edificio_1");
                break;

            case '2':
                system("CLS");
                menuMeses("Edificio_2");
                break;

            default:
                gotoxy(40, 20); cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
        gotoxy(40, 21);
        system("pause");
    } while (r != '0');
}
