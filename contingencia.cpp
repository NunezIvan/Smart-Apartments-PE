#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "menu.cpp"

using namespace std;

struct Nodo{
   bool pagado = false;
   string edificio;
   string mes;
   string nivel;
   string num_dpto;
   string tipo_pago;
   double valor_contigencia;
   Nodo* prev;  
   Nodo* next;  
};




void calcularContingencias(const string& mes, const string& edificio) {
   ifstream archivo("data/propietarios.txt", ios::in);
   if (archivo.fail()) {
      cout << "Error, no se pudo cargar el archivo de propietarios." << endl;
      exit(1);
   }

   
   ifstream archivoContingencia("data/contingencia.txt", ios::in);
   vector<string> contingenciasExistentes;
   string linea;

   if (archivoContingencia.is_open()) {
      while (getline(archivoContingencia, linea)) {
         contingenciasExistentes.push_back(linea);
      }
      archivoContingencia.close();
   }

   ofstream salida("data/contingencia.txt", ios::out | ios::app);
   if (salida.fail()) {
      cout << "Error, no se pudo crear o abrir el archivo de contingencia." << endl;
      exit(1);
   }

   while (getline(archivo, linea)) {
      stringstream ss(linea);
      string nivel, num_dpto, _edificio;

      getline(ss, nivel, ';'); 
      getline(ss, num_dpto, ';');
      getline(ss, _edificio, ';');
      getline(ss, nivel, ';'); 
      getline(ss, num_dpto, ';'); 
      getline(ss, _edificio, ';'); 

      
      string nuevaContingencia = "false;" + _edificio + ";" + mes + ";" + nivel + ";" + num_dpto + ";30";

      
      if (find(contingenciasExistentes.begin(), contingenciasExistentes.end(), nuevaContingencia) == contingenciasExistentes.end()) {

         salida << nuevaContingencia << endl;
      }
   }

   archivo.close();
   salida.close();
}

void agregar(Nodo*& cabeza) {
   ifstream archivo("data/contingencia.txt", ios::in);
   if (!archivo.is_open()) {
      gotoxy(35, 5);
      cout << "Error al abrir el archivo de contingencias." << endl;
      return;
   }

   string linea;
   while (getline(archivo, linea)) {
      stringstream ss(linea);
      string _edificio, _valor, _pagado, _mes, _nivel, _num_dpto, _tipo_pago;
      Nodo* nuevo_nodo = new Nodo();  

     
      getline(ss, _pagado, ';');
      nuevo_nodo->pagado = (_pagado == "true");
      getline(ss, nuevo_nodo->edificio, ';');
      getline(ss, nuevo_nodo->mes, ';');
      getline(ss, nuevo_nodo->nivel, ';');
      getline(ss, nuevo_nodo->num_dpto, ';');
      getline(ss, _valor, ';');
      stringstream ss_valor(_valor);
      ss_valor >> nuevo_nodo->valor_contigencia;

      
      if (!nuevo_nodo->pagado) {
         printtitle1();
         gotoxy(35, 10);
         cout << "La contingencia de " << nuevo_nodo->edificio << " " << nuevo_nodo->mes 
              << " Dpto " << nuevo_nodo->nivel << "0" << nuevo_nodo->num_dpto 
              << " ha sido pagada (S/N)? ";
         char respuesta;
         cin >> respuesta;

        
         if (respuesta == 'S' || respuesta == 's') {
            int menu;
            string tipo;
            do {
               
               gotoxy(40, 12);
               cout << "Ingresar tipo de pago: " << endl;
               gotoxy(40, 13); cout << " 1.- TRANSFERENCIA BANCARIA" << endl;
               gotoxy(40, 14); cout << " 2.- PAGO POR YAPE " << endl;
               gotoxy(40, 15); cout << " 3.- PAGO POR EFECTIVO" << endl;
               gotoxy(40, 16); cout << " 4.- DEPOSITO POR BCP" << endl;
               gotoxy(40, 17); cout << " 5.- PAGO VIA WEB" << endl;
               gotoxy(40, 18); cout << " 0.- Salir" << endl;
               gotoxy(40, 19); cout << " Elija una opción: ";

               cin >> menu;

               
               switch (menu) {
                  case 1: tipo = "Transferencia Bancaria"; break;
                  case 2: tipo = "por Yape"; break;
                  case 3: tipo = "en Efectivo"; break;
                  case 4: tipo = "en BCP"; break;
                  case 5: tipo = "Via Web"; break;
                  case 0: 
                     gotoxy(40, 21); 
                     cout << "Saliendo..." << endl;
                     return;
                  default: 
                     gotoxy(40, 22); 
                     cout << "Opción equivocada, intente nuevamente." << endl;
                     return;
               }
            } while (menu < 1 || menu > 5);

            
            nuevo_nodo->tipo_pago = tipo;
            nuevo_nodo->pagado = true;
         }
      }

      
      if (nuevo_nodo->pagado == true) {
         if (cabeza == nullptr) {
           
            cabeza = nuevo_nodo;
            nuevo_nodo->prev = nullptr;
            nuevo_nodo->next = nullptr;
         } else {
            
            Nodo* temp = cabeza;
            while (temp->next != nullptr) {
               temp = temp->next;
            }
            temp->next = nuevo_nodo;
            nuevo_nodo->prev = temp;
            nuevo_nodo->next = nullptr;
         }
      } else {
         delete nuevo_nodo;  
      }
   }
   archivo.close();
}


string acortarTexto(const string& texto, int longitudMaxima) {
    if (texto.length() > longitudMaxima) {
        return texto.substr(0, longitudMaxima - 1) + ".";  
    }
    return texto; 
}

void mostrarLista(Nodo* cabeza) {
    if (cabeza == nullptr) {
        gotoxy(40, 10);
        cout << "La lista está vacía." << endl;
        return;
    }

   
    printtitle1();  

    
    gotoxy(5, 10);
    cout << "┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━┓";
    gotoxy(5, 11);
    cout << "┃ " << left << setw(15) << "Pagado" 
         << "┃ " << setw(14) << "Edificio" 
         << "┃ " << setw(7) << "Mes" 
         << "┃ " << setw(7) << "Nivel" 
         << "┃ " << setw(11) << "Num Dpto" 
         << "┃ " << setw(18) << "Tipo de Pago" 
         << "┃ " << setw(22) << "Valor Contingencia" << "┃";
    gotoxy(5, 12);
    cout << "┠━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━╇━━━━━━━━╇━━━━━━━━╇━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━┨";

    Nodo* temp = cabeza; 
    int y = 13;  

    
    while (temp != nullptr) {
        gotoxy(5, y);
        cout << "┃ " << left << setw(16) << (temp->pagado ? "Sí" : "No")  
             << "┃ " << setw(14) << temp->edificio 
             << "┃ " << setw(7) << temp->mes 
             << "┃ " << setw(7) << temp->nivel 
             << "┃ " << setw(11) << temp->num_dpto 
             
             << "┃ " << setw(18) << acortarTexto(temp->tipo_pago, 17) 
             << "┃ " << setw(22) << fixed << setprecision(2) << temp->valor_contigencia << "┃";

        y += 1;  
        temp = temp->next; 
    }

   
    gotoxy(5, y);
    cout << "┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━┛";

    gotoxy(5, y + 2); 
    system("pause");  
}

void mostrarContingencia(string temp_mes, string temp_edificio) {
    Nodo* lista = nullptr;
    calcularContingencias(temp_mes, temp_edificio);
    agregar(lista);  
    mostrarLista(lista);
}
