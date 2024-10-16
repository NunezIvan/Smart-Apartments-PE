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

using namespace std;


struct Nodo{
   bool pagado = false;
   string edificio;
   string mes;
   string nivel;
   string num_dpto;
   string tipo_pago;
   double valor_contigencia;
   Nodo *sgt;
};

void calcularContingencias(const string& mes, const string& edificio) {
   ifstream archivo("propietarios.txt", ios::in);
   if (archivo.fail()) {
      cout << "Error, no se pudo cargar el archivo de propietarios." << endl;
      exit(1);
   }

   // Leer el archivo de contingencia actual para evitar duplicados
   ifstream archivoContingencia("contingencia.txt", ios::in);
   vector<string> contingenciasExistentes;
   string linea;

   if (archivoContingencia.is_open()) {
      while (getline(archivoContingencia, linea)) {
         contingenciasExistentes.push_back(linea);
      }
      archivoContingencia.close();
   }

   ofstream salida("contingencia.txt", ios::out | ios::app);
   if (salida.fail()) {
      cout << "Error, no se pudo crear o abrir el archivo de contingencia." << endl;
      exit(1);
   }

   while (getline(archivo, linea)) {
      stringstream ss(linea);
      string nivel, num_dpto, _edificio;

      getline(ss, nivel, ';'); // Saltar los datos que no se necesitan
      getline(ss, num_dpto, ';');
      getline(ss, _edificio, ';');
      getline(ss, nivel, ';'); // Leer el nivel
      getline(ss, num_dpto, ';'); // Leer el número de departamento
      getline(ss, _edificio, ';'); // Leer el edificio

      // Crear la línea de contingencia para comparar y almacenar
      string nuevaContingencia = "false;" + _edificio + ";" + mes + ";" + nivel + ";" + num_dpto + ";30";

      // Verificar si la contingencia ya existe en el archivo
      if (find(contingenciasExistentes.begin(), contingenciasExistentes.end(), nuevaContingencia) == contingenciasExistentes.end()) {
         // Si no existe, la escribimos en el archivo
         salida << nuevaContingencia << endl;
      }
   }

   archivo.close();
   salida.close();
}


void agregar(Nodo* &pila) {
   ifstream archivo("contingencia.txt", ios::in);
   if (!archivo.is_open()) {
      cout << "Error al abrir el archivo de contingencias." << endl;
      return;
   }
   string linea;

   while (getline(archivo, linea)) {
      stringstream ss(linea);
      string _edificio, _valor, _pagado, _mes, _nivel, _num_dpto, _tipo_pago;
      Nodo *nuevo_nodo = new Nodo();

      getline(ss, _pagado, ';');
      nuevo_nodo->pagado = (_pagado == "true");
      getline(ss, nuevo_nodo->edificio, ';');
      getline(ss, nuevo_nodo->mes, ';');
      getline(ss, nuevo_nodo->nivel, ';');
      getline(ss, nuevo_nodo->num_dpto, ';');
      getline(ss, _valor, ';');
      stringstream ss_valor(_valor);
      ss_valor >> nuevo_nodo->valor_contigencia;

      // Solo preguntar si no ha sido pagado
      if (!nuevo_nodo->pagado) {
         char respuesta;
         cout << "La contingencia de " << nuevo_nodo->edificio << " " << nuevo_nodo->mes << " Dpto " << nuevo_nodo->nivel << "0" << nuevo_nodo->num_dpto << " ha sido pagada (S/N)? ";
         cin >> respuesta;

         // Si la respuesta es "S", procesar el pago
         if (respuesta == 'S' || respuesta == 's') {
            int menu;
            string tipo;
            do {
               cout << "Ingresar tipo de pago: " << endl;
               cout << " 1.- TRANSFERENCIA BANCARIA" << endl;
               cout << " 2.- PAGO POR YAPE " << endl;
               cout << " 3.- PAGO POR EFECTIVO" << endl;
               cout << " 4.- DEPOSITO POR BCP" << endl;
               cout << " 5.- PAGO VIA WEB" << endl;
               cout << " 0.- Salir" << endl;
               cout << " Elija una opcion: ";

               cin >> menu;

               switch (menu) {
                  case 1: tipo = "Transferencia Bancaria"; break;
                  case 2: tipo = "por Yape"; break;
                  case 3: tipo = "en Efectivo"; break;
                  case 4: tipo = "en BCP"; break;
                  case 5: tipo = "Via Web"; break;
                  case 0: cout << "Saliendo..." << endl; return;
                  default: cout << "Valor equivocado, chao" << endl; return;
               }
            } while (menu < 1 || menu > 5);

            nuevo_nodo->tipo_pago = tipo;
            nuevo_nodo->pagado = true;
         } else {
            // Si la respuesta es "N", continuar sin modificar el nodo
            nuevo_nodo->pagado = false;
         }
      }

      // Agregar el nodo a la pila solo si ya ha sido pagado
      if (nuevo_nodo->pagado) {
         nuevo_nodo->sgt = pila;
         pila = nuevo_nodo;
      } else {
         delete nuevo_nodo; // Liberar memoria si no se usa el nodo
      }
   }

   archivo.close();
}

void mostrarPilaSinModificar(Nodo *&pila, const string& edificio, const string& mes) {
   Nodo *_temp = pila;
   double totalTransferencia = 0, totalYape = 0, totalEfectivo = 0, totalBcp = 0, totalWeb = 0;
   double totalContingenciasNeto = 0;

   cout << endl << endl << " " << edificio << " - " << mes << endl;
   cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| " << setw(32) << "Fondo de contingencia" << "|";
   cout << setw(15) << "Transferencia" << "|";
   cout << setw(10) << "por Yape" << "|";
   cout << setw(13) << "En Efectivo" << "|";
   cout << setw(10) << "Por BCP" << "|";
   cout << setw(10) << "Via Web" << "|";
   cout << setw(20) << "Total Contingencia" << "|" << endl;
   cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

   while (_temp != NULL) {
      if (_temp->edificio == edificio && _temp->mes == mes) {
         cout << left << "| " << setw(32) << ("Conting. " + _temp->mes + " Dpto " + _temp->nivel + "0" + _temp->num_dpto) << "|";

         if (_temp->tipo_pago == "Transferencia Bancaria") {
            cout << left <<"s/"<< setw(12) << _temp->valor_contigencia << setw(1) << " |";
            totalTransferencia += _temp->valor_contigencia;
         } else {
            cout << setw(15) << " " << "|";
         }

         if (_temp->tipo_pago == "por Yape") {
            cout << left <<"s/"<< setw(7) << _temp->valor_contigencia << setw(1) << " |";
            totalYape += _temp->valor_contigencia;
         } else {
            cout << setw(10) << " " << "|";
         }

         if (_temp->tipo_pago == "en Efectivo") {
            cout << left <<"s/" << setw(10) << _temp->valor_contigencia << setw(1) << " |";
            totalEfectivo += _temp->valor_contigencia;
         } else {
            cout << setw(13) << " " << "|";
         }

         if (_temp->tipo_pago == "en BCP") {
            cout << left <<"s/" << setw(7) << _temp->valor_contigencia << setw(1) << " |";
            totalBcp += _temp->valor_contigencia;
         } else {
            cout << setw(10) << " " << "|";
         }

         if (_temp->tipo_pago == "Via Web") {
            cout << left <<"s/" << setw(7) << _temp->valor_contigencia << setw(1) << " |";
            totalWeb += _temp->valor_contigencia;
         } else {
            cout << setw(10) << " " << "|";
         }

         cout << right << setw(20) << " " << "|" << endl;
      }

      _temp = _temp->sgt;
   }

   totalContingenciasNeto = totalTransferencia + totalYape + totalEfectivo + totalBcp + totalWeb;
   cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<< setw(32) << "Total Contingencias (x pago)" << "|";
   cout << "s/" << left << setw(12) << totalTransferencia << setw(1) << " |";
   cout << "s/" << left << setw(7) << totalYape << setw(1) << " |";
   cout << "s/" << left << setw(10) << totalEfectivo << setw(1) << " |";
   cout << "s/" << left << setw(7) << totalBcp << setw(1) << " |";
   cout << "s/" << left << setw(7) << totalWeb << setw(1) << " |";
   cout << right << setw(15)<< "s/" << totalContingenciasNeto << "  |" << endl;
   cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
   cout << endl;
}


