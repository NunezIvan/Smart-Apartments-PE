#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

struct egresos{
   string tipo;
   string descrip;
   string dia;
   string mes;
   string tipo_pago;
   double aporte;
};

egresos e;

void aporte(const string& mes, const string& tipo, const string& tipo_pago){
   ofstream archivo("egresos.txt", ios::app);
   if (archivo.fail()) {
      cout << " ..." << endl;
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      exit(1);
   }

   char z;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;

   do {
      fflush(stdin);
      cout << endl;
      cout << " Nombre del personal de limpieza: ";
      getline(cin, e.descrip);
      cout << " Ingrese el nro dia que se realizo la limpieza: "; cin >> e.dia;
      cout << " Ingrese el aporte: "; cin >> e.aporte;

      cout << " Desea agregar otro dia de servicio de limpieza(s/n): "; cin >> z;

      archivo << e.tipo<<";"<<e.descrip<<";"<<e.dia<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<< endl;
   } while (z == 's' || z == 'S');
   cout << endl;
   system("pause");
   archivo.close();
}

void aporteBasico (const string& mes, const string& tipo, const string& tipo_pago){
   ofstream archivo("egresos.txt", ios::app);
   if (archivo.fail()) {
      cout << " ..." << endl;
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      exit(1);
   }
   char z;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;
   fflush(stdin);
   cout << endl;
   cout << " Ingrese el aporte: "; cin >> e.aporte;
   archivo << e.tipo<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<< endl;
   cout << endl;

   system("pause");
   archivo.close();
}

void menuTipoPago(const string& mes, const string& tipo){
   string temp_mes=mes, temp_tipo=tipo;
   char r2 = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******TIPO DE PAGO******" << endl;
      cout<<endl;
      cout<<" 1.- TRANSFERENCIA BANCARIA"<<endl;
      cout<<" 2.- PAGO POR YAPE "<<endl;
      cout<<" 3.- PAGO POR EFECTIVO"<<endl;
      cout<<" 4.- DEPOSITO POR BCP"<<endl;
      cout<<" 5.- PAGO VIA WEB"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r2;

      switch (r2) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_tipo, "Transferencia Bancaria");
            } else {
               aporteBasico (temp_mes, temp_tipo, "Transferencia Bancaria");
            }

            break;

         case '2':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_tipo, "por Yape");
            }else {
               aporteBasico (temp_mes, temp_tipo, "por Yape");
            }

            break;
         case '3':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_tipo, "en Efectivo");
            }else {
               aporteBasico (temp_mes, temp_tipo, "en Efectivo");
            }
            break;
         case '4':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_tipo, "en BCP");
            }else {
               aporteBasico (temp_mes, temp_tipo, "en BCP");
            }
            break;

         case '5':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_tipo, "Via Web");
            }else {
               aporteBasico (temp_mes, temp_tipo, "Via Web");
            }
            break;


         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r2 != '0');
}

void menuMantenimiento(const string& mes){
   string temp_mes=mes;
   char r1 = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******MANTENIMIENTO DEL EDIFICIO******" << endl;
      cout<<endl;
      cout<<" 1.- MANTENIMIENTO DEL ASCENSOR"<<endl;
      cout<<" 2.- MANTENIMIENTO DE EQUIPOS ELECTRICOS"<<endl;
      cout<<" 3.- MANTENIMIENTO DE PINTURA"<<endl;
      cout<<" 4.- MANTENIMIENTO DE AREAS VERDES"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r1;

      switch (r1) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoPago(temp_mes,"Mante. Ascensor");
            break;

         case '2':
            system("CLS");
            menuTipoPago(temp_mes,"Mante. Equipos Electricos");
            break;
         case '3':
            system("CLS");
            menuTipoPago(temp_mes,"Mante. Pintura");
            break;
         case '4':
            system("CLS");
            menuTipoPago(temp_mes,"Mante. Area Verdes");
            break;

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r1 != '0');
}

void menuTipoEgresos(const string& mes){
   string temp_mes=mes;
   char r1 = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******TIPO DE EGRESOS******" << endl;
      cout<<endl;
      cout<<" 1.- LIMPIEZA"<<endl;
      cout<<" 2.- PAGO DE ELECTRICIDAD "<<endl;
      cout<<" 3.- PAGO DEL AGUA"<<endl;
      cout<<" 4.- MANTENIMIENTO "<<endl;
      cout<<" 5.- PAGO A SEGURIDAD"<<endl;
      cout<<" 6.- PAGO ADMINISTRADORES"<<endl;
      cout<<" 7.- TOKEN FISICO"<<endl;
      cout<<" 8.- IMPUESTO ITF"<<endl;
      cout<<" 9.- COMISIONES BANCARIA"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r1;

      switch (r1) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoPago(temp_mes,"Limpieza");
            break;

         case '2':
            system("CLS");
            menuTipoPago(temp_mes,"Pago Luz");
            break;
         case '3':
            system("CLS");
            menuTipoPago(temp_mes,"Pago Agua");
            break;
         case '4':
            system("CLS");
            menuMantenimiento(temp_mes);// habra otro menu para diversos tipos de mantenimiento
            break;

         case '5':
            system("CLS");
            menuTipoPago(temp_mes,"Pago Seguridad");
            break;
         case '6':
            system("CLS");
            menuTipoPago(temp_mes,"Pago Administradores");
            break;
         case '7':
            system("CLS");
            menuTipoPago(temp_mes,"Token físico para pagos (BCP)");
            break;
         case '8':
            system("CLS");
            menuTipoPago(temp_mes,"Impuesto ITF (por ley)");
            break;
         case '9':
            system("CLS");
            menuTipoPago(temp_mes,"Comisión por ventanilla BCP");
            break;


         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r1 != '0');
}

int espacioTabla(const string& _tipo, const string& _mes){

   string concatenado = _tipo + _mes;
   // Obtenemos la longitud de la cadena concatenada + 1
   int a = concatenado.size() + 1;
   return a;
}

int espacioTabla2(const string& _tipo, const string& _mes,const string& _dia,const string& _descrip){

   string concatenado = _tipo + _mes+_dia+_descrip;
   // Obtenemos la longitud de la cadena concatenada + 1
   int a = concatenado.size() + 3;
   return a;
}

void mostrarEgresos(const string& mes){
   ifstream archivo("egresos.txt", ios::in);
   if (!archivo.is_open()) {
      cout << "Error al abrir el archivo de administradores." << endl;
      return;
   }

   string temp_mes=mes;
   string linea;
   double aporteTotalTransaccion=0, aporteTotalYape=0, aporteTotaEfectivo=0,aporteTotalBcp=0, aporteTotalWeb=0;
   double egresoTotalNeto=0;

   cout<<endl;
   cout<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<< "Egresos de "<<setw(102) <<temp_mes; ;cout<<"| "<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<<setw(28) << " " ;cout<<"|";
   cout<< setw(18) << "por Transferencia" ; cout<<" |";
   cout<< setw(9) << "por Yape" ; cout<<" |";
   cout<< setw(13) << "por Efectivo" ; cout<<" |";
   cout<< setw(13) << "Depósito BCP" ; cout<<" |";
   cout<< setw(10) << "Vía Web" ; cout<<" |";
   cout<< setw(10) << "Egre. Neto" ; cout<<" |";
   cout<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

   while (getline(archivo, linea)) {

      stringstream ss(linea);
      string _tipo, _descrip, _dia, _mes, _tipoPago, _aporte ;
      getline(ss, _tipo, ';');

      if(_tipo=="Limpieza"){
         getline(ss, _descrip, ';');
         getline(ss, _dia, ';');
         getline(ss, _mes, ';');
         getline(ss, _tipoPago, ';');
         getline(ss, _aporte, ';');
         e.aporte = stod(_aporte);

         if(temp_mes == _mes){
            cout <<"| "<< _tipo<<" "<<_descrip<<" "<<_dia<<" "<<_mes<< left << setw(28-espacioTabla2(_tipo, _mes,_dia,_descrip)) << " " ; cout<<"|";
            if(_tipoPago=="Transferencia Bancaria"){

               cout<< "s/" << left <<setw(17) << e.aporte; cout<<"|";
               cout<< setw(10) << " " ; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalTransaccion+=e.aporte;
            } else if (_tipoPago=="por Yape"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<<"s/" << left <<setw(8) << e.aporte; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalYape+=e.aporte;
            } else if (_tipoPago=="en Efectivo"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< "s/" <<left <<setw(12) << e.aporte ; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotaEfectivo+=e.aporte;

            }  else if (_tipoPago=="en BCP"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<< "s/" <<left <<setw(12) << e.aporte ; cout<<"|";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalBcp +=e.aporte;

            }  else if (_tipoPago=="Via Web"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<<"s/" << left <<setw(9) << e.aporte ; cout<<"|";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalWeb+=e.aporte;

            }
         } //fin if control de los  diversos tipos de pagos
      }

   }//fin while

   archivo.clear();  // Limpiar las banderas de fin de archivo
   archivo.seekg(0); // Mover el cursor al inicio del archivo

   while (getline(archivo, linea)) {

      stringstream ss(linea);
      string _tipo, _mes, _tipoPago, _aporte ;
      getline(ss, _tipo, ';');

      if(_tipo!="Limpieza"){
         getline(ss, _mes, ';');
         getline(ss, _tipoPago, ';');
         getline(ss, _aporte, ';');

         e.aporte = stod(_aporte);

         if(temp_mes == _mes){
            cout <<"| "<< _tipo<<"-"<<_mes<< setw(28-espacioTabla(_tipo,_mes)) << " " ; cout<<"|";
            if(_tipoPago=="Transferencia Bancaria"){

               cout<< "s/" << left <<setw(17) << e.aporte; cout<<"|";
               cout<< setw(10) << " " ; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalTransaccion+=e.aporte;
            } else if (_tipoPago=="por Yape"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<<"s/" << left <<setw(8) << e.aporte; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalYape+=e.aporte;
            } else if (_tipoPago=="en Efectivo"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< "s/" <<left <<setw(12) << e.aporte ; cout<<"|";
               cout<< setw(13) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotaEfectivo+=e.aporte;

            }  else if (_tipoPago=="en BCP"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<< "s/" <<left <<setw(12) << e.aporte ; cout<<"|";
               cout<< setw(10) << " " ; cout<<" |";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalBcp +=e.aporte;

            }  else if (_tipoPago=="Via Web"){

               cout<< setw(19) <<" "; cout<<"|";
               cout<< setw(10) << " "; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<< setw(14) << " " ; cout<<"|";
               cout<<"s/" << left <<setw(9) << e.aporte ; cout<<"|";
               cout<< setw(10) << " " ; cout<<" |"<<endl;
               aporteTotalWeb+=e.aporte;

            }
         } //fin if control de los  diversos tipos de pagos
      }//Fin if control de mes
   }//fin while



   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<< setw(28) << "Egresos Totales (x pago)"; cout<<"| ";
   cout<< "s/" << left <<setw(16) << aporteTotalTransaccion; cout<<"|";
   cout<< "s/" << left <<setw(8) << aporteTotalYape; cout<<"|";
   cout<< "s/" << left <<setw(12) << aporteTotaEfectivo ; cout<<"|";
   cout<< "s/" << left <<setw(12) << aporteTotalBcp ; cout<<"|";
   cout<<"s/" << left <<setw(9) << aporteTotalWeb ; cout<<"|";
   egresoTotalNeto=aporteTotalTransaccion+aporteTotalYape+aporteTotaEfectivo+aporteTotalBcp+aporteTotalWeb;
   cout<<"s/" << left <<setw(9) << egresoTotalNeto ; cout<<"|"<<endl;;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout<<endl;
   system("pause");

   archivo.close();
} //fin mostrarEgresos

void menuControlDeCaja(const string& mes){
   char r = ' ';
   string temp_mes=mes;
   do {
      system("CLS");
      cout << endl;
      cout << " ******GESTION DE CONTROL DE CAJA******" << endl;
      cout<<endl;
      cout<<" 1.- REGISTRO DE EGRESOS"<<endl;
      cout<<" 2.- VER EGRESOS"<<endl;
      cout<<" 3.- REGISTRO DE INGRESOS"<<endl;
      cout<<" 4.- VER INGRESOS"<<endl;
      cout<<" 5.- VER BALANCE"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r;

      switch (r) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoEgresos(temp_mes);
            break;

         case '2':
            system("CLS");
            mostrarEgresos(temp_mes);
            break;

         case '3':
            system("CLS");

            break;

         case '4':
            system("CLS");

            break;

         case '5':
            system("CLS");

            break;

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r != '0');
}

void gestionControlCaja(){
   char opcion;
   do{
      system("CLS");

      cout << endl;
      cout << " BIENVENIDO A:" << endl;
      cout << " ******GESTION DE CONTROL DE CAJA******" << endl;
      cout<<endl;
      cout<< " Control de caja del mes:"<<endl;
      cout << "  A) ENERO" << endl;
      cout << "  B) FEBRERO" << endl;
      cout << "  C) MARZO" << endl;
      cout << "  D) ABRIL" << endl;
      cout << "  E) MAYO" << endl;
      cout << "  F) JUNIO" << endl;
      cout << "  G) JULIO" << endl;
      cout << "  H) AGOSTO" << endl;
      cout << "  I) SEPTIEMBRE" << endl;
      cout << "  J) OCTUBRE" << endl;
      cout << "  K) NOVIEMBRE" << endl;
      cout << "  L) DICIEMBRE" << endl;
      cout << "  0.- Salir" << endl;
      cout << "  Ingrese una opcion: ";

      cin>>opcion;
      fflush(stdin);

      switch (opcion) {
         case '0':{
            exit(0);
         }
         case 'a':{
            menuControlDeCaja("Enero");
            break;
         }
         case 'b':{
            system("CLS");
            menuControlDeCaja("Febrero");
            break;
         }
         case 'c':{
            system("CLS");
            menuControlDeCaja("Marzo");

            break;
         }
         case 'd':{
            system("CLS");
            menuControlDeCaja("Abril");

            break;
         }
         case 'e':{
            system("CLS");
            menuControlDeCaja("Mayo");
            break;
         }
         case 'f':{
            system("CLS");
            menuControlDeCaja("Junio");
            break;
         }
         case 'g':{
            system("CLS");
            menuControlDeCaja("Julio");
            break;
         }
         case 'h':{
            system("CLS");
            menuControlDeCaja("Agosto");
            break;
         }
         case 'i':{
            system("CLS");
            menuControlDeCaja("Septiembre");

            break;
         }
         case 'j':{
            system("CLS");
            menuControlDeCaja("Octubre");

            break;
         }
         case 'k':{
            system("CLS");
            menuControlDeCaja("Noviembre");

            break;
         }
         case 'l':{
            system("CLS");
            menuControlDeCaja("Diciembre");

            break;
         }

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   }while (opcion != '0');
}