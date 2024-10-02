#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "Cuotas.cpp"
#include "ingresos.cpp"

using namespace std;

struct egresos{
   string tipo;
   string descrip;
   string dia;
   string mes;
   string tipo_pago;
   double aporte;
   string nombre_edificio;
};

egresos e;

void aporte(const string& mes, const string& edificio, const string& tipo, const string& tipo_pago){
   string temp_edificio = edificio;
   ofstream archivo("egresos.txt", ios::app);
   if (archivo.fail()) {
      cout << " ..." << endl;
      Sleep(1500);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      exit(1);
   }

   char z;
   e.nombre_edificio=temp_edificio;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;

   do {
      fflush(stdin);
      cin.ignore();
      cout << endl;
      cout << " Nombre del personal de limpieza: ";
      getline(cin, e.descrip);
      cout << " Ingrese el nro dia que se realizo la limpieza: "; cin >> e.dia;
      cout << " Ingrese el aporte: "; cin >> e.aporte;

      cout << " Desea agregar otro dia de servicio de limpieza(s/n): "; cin >> z;

      archivo << e.tipo<<";"<<e.descrip<<";"<<e.dia<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;
   } while (z == 's' || z == 'S');
   cout << endl;
   system("pause");
   archivo.close();
}

void aporteBasico (const string& mes, const string& edificio, const string& tipo, const string& tipo_pago){
   ofstream archivo("egresos.txt", ios::app);
   string temp_edificio = edificio;
   if (archivo.fail()) {
      cout << " ..." << endl;
      Sleep(1500);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      exit(1);
   }
   char z;
   e.nombre_edificio=temp_edificio;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;
   fflush(stdin);
   cin.ignore();
   cout << endl;
   cout << " Ingrese el aporte: "; cin >> e.aporte;
   archivo << e.tipo<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;
   cout << endl;

   system("pause");
   archivo.close();
}

void registrarConsumoAgua (const string& mes, const string& edificio, const string& tipo, const string& tipo_pago){
   ofstream archivo("egresos.txt", ios::app);
   string temp_edificio = edificio;
   if (archivo.fail()) {
      cout << " ..." << endl;
      Sleep(1500);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      exit(1);
   }
   e.nombre_edificio = temp_edificio;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;

   const float CARGO_FIJO=6.26, IGV=0.18, VOLUMEN=2.02, SERVICIO_ALCANTARILLADO=1.26;
   float lec_actual, lec_anterior;
   float consumo_agua_m3=0, subtotal=0, subtotal_desague=0,total=0, total_igv=0;
   cout<<" Ingrese la lectura anterior: "; cin>>lec_anterior;
   cout<<" Ingrese la lectura actual: "; cin>>lec_actual;

   consumo_agua_m3=lec_actual-lec_anterior;
   subtotal=consumo_agua_m3*VOLUMEN;
   subtotal_desague=consumo_agua_m3*SERVICIO_ALCANTARILLADO;
   total_igv=(subtotal+subtotal_desague+CARGO_FIJO)*IGV;
   total=subtotal+subtotal_desague+CARGO_FIJO+total_igv;
   e.aporte=total;

   cout<<endl;
   cout<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<< "Egresos de "<<setw(102) <<e.mes; ;cout<<"| "<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"| "<<setw(6) << " " ;cout<<"|";
   cout<< setw(12) << "Lec. actual" ; cout<<" |";
   cout<< setw(14) << "Lec. anterior" ; cout<<" |";
   cout<< setw(6) << "c. m^3" ; cout<<" |";
   cout<< setw(4) << "F" ; cout<<" |";
   cout<< setw(8) << "Subtotal" ; cout<<" |";
   cout<< setw(4) << "F" ; cout<<" |";
   cout<< setw(9) << "Subtotal" ; cout<<" |";
   cout<< setw(10) << "Cargo Fijo" ; cout<<" |";
   cout<< setw(11) << "Total IGV" ; cout<<" |";
   cout<< setw(9) << "Total" ; cout<<" |";
   cout<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
   cout << left <<"|"<<setw(7) << "Datos" ;cout<<"|";
   cout<<setw(12) << lec_actual ; cout<<" |";
   cout<< setw(14) << lec_anterior ; cout<<" |";
   cout<< setw(6) << consumo_agua_m3 ; cout<<" |";
   cout<< setw(4) << VOLUMEN ; cout<<" |";
   cout<< "s/"<<setw(6) << subtotal ; cout<<" |";
   cout<< setw(4) << SERVICIO_ALCANTARILLADO ; cout<<" |";
   cout<< "s/"<<setw(7) << subtotal_desague ; cout<<" |";
   cout<<"s/"<< setw(8) << CARGO_FIJO ; cout<<" |";
   cout<<"s/"<< setw(9) <<  total_igv ; cout<<" |";
   cout<< "s/"<<setw(5) << total ; cout<<" |";
   cout<<endl;
   cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

   archivo << e.tipo<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;
   cout << endl;
   system("pause");
   archivo.close();
}

void menuTipoPago(const string& mes, const string& edificio, const string& tipo){
   string temp_mes=mes, temp_edificio=edificio, temp_tipo=tipo;
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
               aporte(temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            } else if(temp_tipo=="Pago Agua"){
               registrarConsumoAgua (temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            } else {
               aporteBasico (temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            }

            break;

         case '2':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_edificio, temp_tipo, "por Yape");
            } else if(temp_tipo=="Pago Agua"){
               registrarConsumoAgua (temp_mes, temp_edificio, temp_tipo, "por Yape");
            } else {
               aporteBasico (temp_mes, temp_edificio, temp_tipo, "por Yape");
            }

            break;
         case '3':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            } else if(temp_tipo=="Pago Agua"){
               registrarConsumoAgua (temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            } else {
               aporteBasico (temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            }
            break;
         case '4':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_edificio, temp_tipo, "en BCP");
            } else if(temp_tipo=="Pago Agua"){
               registrarConsumoAgua (temp_mes, temp_edificio, temp_tipo, "en BCP");
            } else {
               aporteBasico (temp_mes, temp_edificio, temp_tipo, "en BCP");
            }
            break;

         case '5':
            system("CLS");
            if(temp_tipo=="Limpieza"){
               aporte(temp_mes, temp_edificio, temp_tipo, "Via Web");
            }else if(temp_tipo=="Pago Agua"){
               registrarConsumoAgua (temp_mes, temp_edificio, temp_tipo, "Via Web");
            } else {
               aporteBasico (temp_mes, temp_edificio, temp_tipo, "Via Web");
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

void menuMantenimiento(const string& mes, const string& edificio){
   string temp_mes=mes, temp_edificio=edificio;
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
            menuTipoPago(temp_mes, temp_edificio,"Mante. Ascensor");
            break;

         case '2':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Mante. Equipos Electricos");
            break;
         case '3':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Mante. Pintura");
            break;
         case '4':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Mante. Area Verdes");
            break;

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r1 != '0');
}

void menuTipoEgresos(const string& mes, const string& edificio){
   string temp_mes=mes, temp_edificio=edificio;
   char r1 = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******TIPO DE EGRESOS******" << endl;
      cout<<endl;
      cout<<" 1.- LIMPIEZA"<<endl;
      cout<<" 2.- MANTENIMIENTO "<<endl;
      cout<<" 3.- PAGO A SEGURIDAD"<<endl;
      cout<<" 4.- PAGO ADMINISTRADORES"<<endl;
      cout<<" 5.- TOKEN FISICO"<<endl;
      cout<<" 6.- IMPUESTO ITF"<<endl;
      cout<<" 7.- COMISIONES BANCARIA"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r1;

      switch (r1) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Limpieza");
            break;

         case '2':
            system("CLS");
            menuMantenimiento(temp_mes, temp_edificio);// habra otro menu para diversos tipos de mantenimiento
            break;

         case '3':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Pago Seguridad");
            break;
         case '4':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Pago Administradores");
            break;
         case '5':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Token físico para pagos (BCP)");
            break;
         case '6':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Impuesto ITF (por ley)");
            break;
         case '7':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Comisión por ventanilla BCP");
            break;


         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r1 != '0');
}

//TABLAS

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

void mostrarEgresos(const string& mes, const string& edificio){
/*   FIN TABLA   */
   ifstream archivo("egresos.txt", ios::in);
   if (!archivo.is_open()) {
      cout << "Error al abrir el archivo de administradores." << endl;
      return;
   }
   string temp_edificio = edificio;
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
      string _tipo, _descrip, _dia, _mes, _tipoPago, _aporte , _nombreEdificio;
      getline(ss, _tipo, ';');

      if(_tipo=="Limpieza"){
         getline(ss, _descrip, ';');
         getline(ss, _dia, ';');
         getline(ss, _mes, ';');
         getline(ss, _tipoPago, ';');
         getline(ss, _aporte, ';');
         getline(ss, _nombreEdificio, ';');
         e.aporte = stod(_aporte);
         e.nombre_edificio = _nombreEdificio;

         if(temp_mes == _mes && temp_edificio == _nombreEdificio){
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
      string _tipo, _mes, _tipoPago, _aporte, _nombreEdificio;
      getline(ss, _tipo, ';');

      if(_tipo!="Limpieza"){
         getline(ss, _mes, ';');
         getline(ss, _tipoPago, ';');
         getline(ss, _aporte, ';');
         getline(ss, _nombreEdificio, ';');

         e.aporte = stod(_aporte);
         e.nombre_edificio = _nombreEdificio;

         if(temp_mes == _mes && temp_edificio == _nombreEdificio ){
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
}

void menuConsumo(const string& mes, const string& edificio){
    string temp_mes=mes, temp_edificio=edificio;
   char r1 = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******REGISTRO DE CONSUMO******" << endl;
      cout<<endl;
      cout<<" 1.- CONSUMO DE AGUA"<<endl;
      cout<<" 2.- CONSUMO DE LUZ"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r1;

      switch (r1) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Pago Agua" );
            break;

         case '2':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio,"Pago Luz" );
            break;

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r1 != '0');
}

void menuControlDeCaja(const string& mes, const string& edificio){
   char r = ' ';
   string temp_mes=mes, temp_edificio=edificio;
   do {
      system("CLS");
      cout << endl;
      cout << " ******GESTION DE CONTROL DE CAJA******" << endl;
      cout<<endl;
      cout<<" 1.- REGISTRO DE EGRESOS"<<endl;
      cout<<" 2.- VER EGRESOS"<<endl;
      cout<<" 3.- REGISTRO DE CONSUMO"<<endl;
      cout<<" 4.- INGRESAR CUOTA GENERAL"<<endl;
      cout<<" 5.- VER CUOTA GENERAL"<<endl;
      cout<<" 6.- VER CUOTAS UNICAS"<<endl;
      cout<<" 7.- REGISTRO DE INGRESOS"<<endl;
      cout<<" 8.- VER INGRESOS"<<endl;
      cout<<" 9.- VER BALANCE"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
      cin >> r;

      switch (r) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            menuTipoEgresos(temp_mes, temp_edificio);
            break;

         case '2':
            system("CLS");
            mostrarEgresos(temp_mes, temp_edificio);
            break;

         case '3':
            system("CLS");
            menuConsumo(temp_mes, temp_edificio);
            break;

         case '4':
            system("CLS");
            calcularCuotaGeneral(temp_mes,temp_edificio);
            break;

         case '5':
            system("CLS");
            mostrarCuotasGenerales();
            break;
         case '6':
            system("CLS");
            mostrarCuotasEspecificas();
            break;
         case '7':
            system("CLS");
            pagoCuota(temp_mes,temp_edificio);
            break;
         case '8':
            system("CLS");
            mostrarIngresos();
            break;
         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r != '0');
}

void menuMeses(const string& edificio){
   string temp_edificio=edificio;
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
         case '0':
            return;
            break;
         case 'a':{
            menuControlDeCaja("Enero", temp_edificio);
            break;
         }
         case 'b':{
            system("CLS");
            menuControlDeCaja("Febrero", temp_edificio);
            break;
         }
         case 'c':{
            system("CLS");
            menuControlDeCaja("Marzo", temp_edificio);

            break;
         }
         case 'd':{
            system("CLS");
            menuControlDeCaja("Abril", temp_edificio);

            break;
         }
         case 'e':{
            system("CLS");
            menuControlDeCaja("Mayo", temp_edificio);
            break;
         }
         case 'f':{
            system("CLS");
            menuControlDeCaja("Junio", temp_edificio);
            break;
         }
         case 'g':{
            system("CLS");
            menuControlDeCaja("Julio", temp_edificio);
            break;
         }
         case 'h':{
            system("CLS");
            menuControlDeCaja("Agosto", temp_edificio);
            break;
         }
         case 'i':{
            system("CLS");
            menuControlDeCaja("Septiembre", temp_edificio);

            break;
         }
         case 'j':{
            system("CLS");
            menuControlDeCaja("Octubre", temp_edificio);

            break;
         }
         case 'k':{
            system("CLS");
            menuControlDeCaja("Noviembre", temp_edificio);

            break;
         }
         case 'l':{
            system("CLS");
            menuControlDeCaja("Diciembre", temp_edificio);

            break;
         }

         default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   }while (opcion != '0');
}

void menuElegirEdificio (){
  char r = ' ';
   do {
      system("CLS");
      cout << endl;
      cout << " ******ELEGIR EDIFICIO******" << endl;
      cout<<endl;
      cout<<" 1.- EDIFICIO 1"<<endl;
      cout<<" 2.- EDIFICIO 2"<<endl;
      cout << " 0.- Salir" << endl;
      cout << " Elija una opcion: ";
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
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      cout<<endl;
   system("CLS");
   } while (r != '0');
}