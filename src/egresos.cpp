#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "menu.cpp"

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
   ofstream archivo("data/egresos.txt", ios::app);
   if (archivo.fail()) {
      gotoxy(35, 5);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      Sleep(1500);
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
      system("cls");
      printtitle1();
      gotoxy(40,11);
      cout <<"▂▃▄▅▆▇█▓▒░PERSONAL DEL LIMPIEZA░▒▓█▇▆▅▄▃▂" << endl;
      gotoxy(40, 13); cout << " Nombre del personal de limpieza: "; getline(cin, e.descrip);
      gotoxy(40, 14); cout << " Ingrese el nro dia que se realizo la limpieza: "; cin >> e.dia;
      gotoxy(40, 15); cout << " Ingrese el aporte: "; cin >> e.aporte;

      gotoxy(40, 16); cout << " Desea agregar otro dia de servicio de limpieza(s/n): "; cin >> z;

      archivo << e.tipo<<";"<<e.descrip<<";"<<e.dia<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;
   } while (z == 's' || z == 'S');
   archivo.close();
}

void aporteBasico (const string& mes, const string& edificio, const string& tipo, const string& tipo_pago){
   ofstream archivo("data/egresos.txt", ios::app);
   string temp_edificio = edificio;
   if (archivo.fail()) {
      gotoxy(35, 5);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      Sleep(1500);
      exit(1);
   }

   e.nombre_edificio=temp_edificio;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;

   system("cls");
   printtitle1();
   gotoxy(40,11);
   cout <<"▂▃▄▅▆▇█▓▒░DATOS DEL APORTE░▒▓█▇▆▅▄▃▂" << endl;
   gotoxy(40, 12); cout << " Ingrese el aporte: "; cin >> e.aporte;
   archivo << e.tipo<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;

   gotoxy(40, 13);
   archivo.close();
}

void registrarConsumoAgua (const string& mes, const string& edificio, const string& tipo, const string& tipo_pago){
   ofstream archivo("data/egresos.txt", ios::app);
   string temp_edificio = edificio;
   if (archivo.fail()) {
      gotoxy(35, 5);
      cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
      Sleep(1500);
      exit(1);
   }
   e.nombre_edificio = temp_edificio;
   e.mes =mes;
   e.tipo = tipo;
   e.tipo_pago=tipo_pago;

   const float CARGO_FIJO=6.26, IGV=0.18, VOLUMEN=2.02, SERVICIO_ALCANTARILLADO=1.26;
   float lec_actual, lec_anterior;
   float consumo_agua_m3=0, subtotal=0, subtotal_desague=0,total=0, total_igv=0;

   system("cls");
   printtitle1();
   gotoxy(40,11);
   cout <<"▂▃▄▅▆▇█▓▒░DATOS DE LECTURA░▒▓█▇▆▅▄▃▂" << endl;
   gotoxy(40, 12); cout << " Ingrese la lectura anterior: ";cin >> lec_anterior;
   gotoxy(40, 13); cout << " Ingrese la lectura actual: ";cin >> lec_actual;

   consumo_agua_m3=lec_actual-lec_anterior;
   subtotal=consumo_agua_m3*VOLUMEN;
   subtotal_desague=consumo_agua_m3*SERVICIO_ALCANTARILLADO;
   total_igv=(subtotal+subtotal_desague+CARGO_FIJO)*IGV;
   total=subtotal+subtotal_desague+CARGO_FIJO+total_igv;
   e.aporte=total;

   gotoxy(0, 13); cout << "--------------------------------------------------------------------------------------------------------------------";
   gotoxy(0, 14); cout << left << "| " << "Egresos de " << setw(102) << e.mes << " |";
   gotoxy(0, 15); cout << "--------------------------------------------------------------------------------------------------------------------";
   gotoxy(0, 16); cout << left << "| " << setw(6) << " " << "|";
   gotoxy(10, 16); cout << setw(12) << "Lec. actual" << " |";
   gotoxy(30, 16); cout << setw(14) << "Lec. anterior" << " |";
   gotoxy(50, 16); cout << setw(6) << "c. m^3" << " |";
   gotoxy(60, 16); cout << setw(4) << "F" << " |";
   gotoxy(70, 16); cout << setw(8) << "Subtotal" << " |";
   gotoxy(85, 16); cout << setw(4) << "F" << " |";
   gotoxy(95, 16); cout << setw(9) << "Subtotal" << " |";
   gotoxy(110, 16); cout << setw(10) << "Cargo Fijo" << " |";
   gotoxy(125, 16); cout << setw(11) << "Total IGV" << " |";
   gotoxy(140, 16); cout << setw(9) << "Total" << " |";
   gotoxy(0, 17); cout << "--------------------------------------------------------------------------------------------------------------------";
   gotoxy(0, 18); cout << left << "|" << setw(7) << "Datos" << "|";
   gotoxy(10, 18); cout << setw(12) << lec_actual << " |";
   gotoxy(30, 18); cout << setw(14) << lec_anterior << " |";
   gotoxy(50, 18); cout << setw(6) << consumo_agua_m3 << " |";
   gotoxy(60, 18); cout << setw(4) << VOLUMEN << " |";
   gotoxy(70, 18); cout << "s/" << setw(6) << subtotal << " |";
   gotoxy(85, 18); cout << setw(4) << SERVICIO_ALCANTARILLADO << " |";
   gotoxy(95, 18); cout << "s/" << setw(7) << subtotal_desague << " |";
   gotoxy(110, 18); cout << "s/" << setw(8) << CARGO_FIJO << " |";
   gotoxy(125, 18); cout << "s/" << setw(9) << total_igv << " |";
   gotoxy(140, 18); cout << "s/" << setw(5) << total << " |";
   gotoxy(0, 19); cout << "--------------------------------------------------------------------------------------------------------------------";

   archivo << e.tipo<<";"<<e.mes<<";"<<e.tipo_pago<<";"<<e.aporte<<";"<<e.nombre_edificio<< endl;
   gotoxy(35, 21);
   archivo.close();
}

void menuTipoPago(const string& mes, const string& edificio, const string& tipo){
   string temp_mes = mes, temp_edificio = edificio, temp_tipo = tipo;
   char r2 = ' ';
   do {
      system("cls");
      printtitle1();
      gotoxy(40,11);
        cout <<"▂▃▄▅▆▇█▓▒░TIPO DE PAGO░▒▓█▇▆▅▄▃▂" << endl;
      gotoxy(35, 13); cout << " 1.- TRANSFERENCIA BANCARIA";
      gotoxy(35, 14); cout << " 2.- PAGO POR YAPE";
      gotoxy(35, 15); cout << " 3.- PAGO POR EFECTIVO";
      gotoxy(35, 16); cout << " 4.- DEPOSITO POR BCP";
      gotoxy(35, 17); cout << " 5.- PAGO VIA WEB";
      gotoxy(35, 18); cout << " 0.- Salir";
      gotoxy(35, 20); cout << " Elija una opcion: ";
      cin >> r2;

      switch (r2) {
         case '0':
            return;
            break;

         case '1':
            system("CLS");
            if (temp_tipo == "Limpieza") {
               aporte(temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            } else if (temp_tipo == "Pago Agua") {
               registrarConsumoAgua(temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            } else {
               aporteBasico(temp_mes, temp_edificio, temp_tipo, "Transferencia Bancaria");
            }
            break;

         case '2':
            system("CLS");
            if (temp_tipo == "Limpieza") {
               aporte(temp_mes, temp_edificio, temp_tipo, "por Yape");
            } else if (temp_tipo == "Pago Agua") {
               registrarConsumoAgua(temp_mes, temp_edificio, temp_tipo, "por Yape");
            } else {
               aporteBasico(temp_mes, temp_edificio, temp_tipo, "por Yape");
            }
            break;

         case '3':
            system("CLS");
            if (temp_tipo == "Limpieza") {
               aporte(temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            } else if (temp_tipo == "Pago Agua") {
               registrarConsumoAgua(temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            } else {
               aporteBasico(temp_mes, temp_edificio, temp_tipo, "en Efectivo");
            }
            break;

         case '4':
            system("CLS");
            if (temp_tipo == "Limpieza") {
               aporte(temp_mes, temp_edificio, temp_tipo, "en BCP");
            } else if (temp_tipo == "Pago Agua") {
               registrarConsumoAgua(temp_mes, temp_edificio, temp_tipo, "en BCP");
            } else {
               aporteBasico(temp_mes, temp_edificio, temp_tipo, "en BCP");
            }
            break;

         case '5':
            system("CLS");
            if (temp_tipo == "Limpieza") {
               aporte(temp_mes, temp_edificio, temp_tipo, "Via Web");
            } else if (temp_tipo == "Pago Agua") {
               registrarConsumoAgua(temp_mes, temp_edificio, temp_tipo, "Via Web");
            } else {
               aporteBasico(temp_mes, temp_edificio, temp_tipo, "Via Web");
            }
            break;

         default:
            gotoxy(35, 21); cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      gotoxy(35, 23);
      system("pause");
   } while (r2 != '0');
}
void menuMantenimiento(const string& mes, const string& edificio){
   string temp_mes = mes, temp_edificio = edificio;
   char r1 = ' ';
   do {
      system("CLS");
      printtitle1();
      gotoxy(40,11);
        cout <<"▂▃▄▅▆▇█▓▒░TIPO DE MANTENIMIENTO░▒▓█▇▆▅▄▃▂" << endl;
      gotoxy(40, 13); cout << " 1.- MANTENIMIENTO DEL ASCENSOR";
      gotoxy(40, 14); cout << " 2.- MANTENIMIENTO DE EQUIPOS ELECTRICOS";
      gotoxy(40, 15); cout << " 3.- MANTENIMIENTO DE PINTURA";
      gotoxy(40, 16); cout << " 4.- MANTENIMIENTO DE AREAS VERDES";
      gotoxy(40, 17); cout << " 0.- Salir";
      gotoxy(40, 19); cout << " Elija una opcion: ";
      cin >> r1;

      switch (r1) {
         case '0':
            return;
            break;
         case '1':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio, "Mante. Ascensor");
            break;
         case '2':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio, "Mante. Equipos Electricos");
            break;
         case '3':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio, "Mante. Pintura");
            break;
         case '4':
            system("CLS");
            menuTipoPago(temp_mes, temp_edificio, "Mante. Area Verdes");
            break;
         default:
            gotoxy(35, 20); cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      gotoxy(35, 22);
      system("pause");
   } while (r1 != '0');
}

void menuTipoEgresos(const string& mes, const string& edificio){ // Ponerlo en un archivo (Control_Caja)
   string temp_mes=mes, temp_edificio=edificio;
   char r1 = ' ';
   do {
      system("CLS");
      printtitle1();
      gotoxy(40,11);
        cout <<"▂▃▄▅▆▇█▓▒░TIPO DE EGRESOS░▒▓█▇▆▅▄▃▂" << endl;
      gotoxy(40, 12); cout << " 1.- LIMPIEZA";
      gotoxy(40, 13); cout << " 2.- MANTENIMIENTO";
      gotoxy(40, 14); cout << " 3.- PAGO A SEGURIDAD";
      gotoxy(40, 15); cout << " 4.- PAGO ADMINISTRADORES";
      gotoxy(40, 16); cout << " 5.- TOKEN FISICO";
      gotoxy(40, 17); cout << " 6.- IMPUESTO ITF";
      gotoxy(40, 18); cout << " 7.- COMISIONES BANCARIA";
      gotoxy(40, 19); cout << " 0.- Salir";
      gotoxy(40, 21); cout << " Elija una opcion: ";
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
            gotoxy(35, 23); cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
      }
      gotoxy(35, 25);
      system("pause");
   } while (r1 != '0');
}

int espacioTabla(const string& _tipo, const string& _mes){
   string concatenado = _tipo + _mes;
   int a = concatenado.size() + 1;
   return a;
}

int espacioTabla2(const string& _tipo, const string& _mes, const string& _dia, const string& _descrip){
   string concatenado = _tipo + _mes + _dia + _descrip;
   int a = concatenado.size() + 3;
   return a;
}

void mostrarEgresos(const string& mes, const string& edificio) {
    ifstream archivo("data/egresos.txt", ios::in);
    if (!archivo.is_open()) {
        gotoxy(35, 5);
        cout << " ERROR, ARCHIVO NO ENCONTRADO" << endl;
        Sleep(1500);
        cin.get();
        return;
    }

    string temp_edificio = edificio;
    string temp_mes = mes;
    string linea;
    double aporteTotalTransaccion = 0, aporteTotalYape = 0, aporteTotalEfectivo = 0, aporteTotalBcp = 0, aporteTotalWeb = 0;
    double egresoTotalNeto = 0;

    system("cls");
    printtitle1();

    int y = 11; // Coordenada y donde empezamos a imprimir la tabla

    // Encabezado de la tabla
    gotoxy(0, y++); cout << "+----------------------------+----------------------+------------+----------------+----------------+------------+-------------+";
    gotoxy(0, y++); cout << "| Egresos de " << setw(26) << temp_mes << right << setw(88) << " |";
    gotoxy(0, y++); cout << "+----------------------------+----------------------+------------+----------------+----------------+------------+-------------+";
    gotoxy(0, y); cout << "| Concepto                   | Transferencia        | Yape       | Efectivo       | Depósito BCP   | Vía Web    | Egre. Neto  |";
    y++;
    gotoxy(0, y++); cout << "+----------------------------+----------------------+------------+----------------+----------------+------------+-------------+";

    // Filas de los datos
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string _tipo, _descrip, _dia, _mes, _tipoPago, _aporte, _nombreEdificio;
        getline(ss, _tipo, ';');

        if (_tipo == "Limpieza") {
            getline(ss, _descrip, ';');
            getline(ss, _dia, ';');
            getline(ss, _mes, ';');
            getline(ss, _tipoPago, ';');
            getline(ss, _aporte, ';');
            getline(ss, _nombreEdificio, ';');
            e.aporte = stod(_aporte);
            e.nombre_edificio = _nombreEdificio;

            if (temp_mes == _mes && temp_edificio == _nombreEdificio) {
                gotoxy(0, y); cout << "| " << left << setw(27) << (_tipo + " " + _descrip + " " + _dia) << "|";

                // Columna Transferencia
                if (_tipoPago == "Transferencia Bancaria") {
                    gotoxy(30, y); cout << "s/" << setw(20) << e.aporte << "|";
                    aporteTotalTransaccion += e.aporte;
                } else {
                    gotoxy(30, y); cout << setw(22) << " " << "|";
                }

                // Columna Yape
                if (_tipoPago == "por Yape") {
                    gotoxy(53, y); cout << "s/" << setw(13) << e.aporte;gotoxy(65,y); cout<<"|";
                    aporteTotalYape += e.aporte;
                } else {
                    gotoxy(53, y); cout << setw(13) << " ";gotoxy(65,y); cout<<"|";
                }

                // Columna Efectivo
                if (_tipoPago == "en Efectivo") {
                    gotoxy(66, y); cout << "s/" << setw(14) << e.aporte << "|";
                    aporteTotalEfectivo += e.aporte;
                } else {
                    gotoxy(66, y); cout << setw(16) << " " << "|";
                }

                // Columna Depósito BCP
                if (_tipoPago == "en BCP") {
                    gotoxy(84, y); cout << "s/" << setw(14) << e.aporte << "|";
                    aporteTotalBcp += e.aporte;
                } else {
                    gotoxy(84, y); cout << setw(15) << " " << "|";
                }

                // Columna Vía Web
                if (_tipoPago == "Via Web") {
                    gotoxy(100, y); cout << "s/" << setw(10) << e.aporte;gotoxy(112,y); cout <<"|";
                    aporteTotalWeb += e.aporte;
                } else {
                    gotoxy(100, y); cout << setw(10) << " ";gotoxy(112,y); cout <<"|";
                }

                // Columna Egreso Neto (vacía por ahora)
                gotoxy(114, y); cout << setw(12) << " " << "|";
                y++;
            }
        }
    } // fin while

    archivo.clear();  // Limpiar las banderas de fin de archivo
    archivo.seekg(0); // Mover el cursor al inicio del archivo

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string _tipo, _mes, _tipoPago, _aporte, _nombreEdificio;
        getline(ss, _tipo, ';');

        if (_tipo != "Limpieza") {
            getline(ss, _mes, ';');
            getline(ss, _tipoPago, ';');
            getline(ss, _aporte, ';');
            getline(ss, _nombreEdificio, ';');

            e.aporte = stod(_aporte);
            e.nombre_edificio = _nombreEdificio;

            if (temp_mes == _mes && temp_edificio == _nombreEdificio) {
                gotoxy(0, y); cout << "| " << left << setw(27) << (_tipo + "-" + _mes) << "|";

                // Columna Transferencia
                if (_tipoPago == "Transferencia Bancaria") {
                    gotoxy(30, y); cout << "s/" << setw(20) << e.aporte << "|";
                    aporteTotalTransaccion += e.aporte;
                } else {
                    gotoxy(30, y); cout << setw(22) << " " << "|";
                }

                // Columna Yape
                if (_tipoPago == "por Yape") {
                    gotoxy(53, y); cout << "s/" << setw(13) << e.aporte;gotoxy(65,y); cout<<"|";
                    aporteTotalYape += e.aporte;
                } else {
                    gotoxy(53, y); cout << setw(13) << " ";gotoxy(65,y); cout<<"|";
                }

                // Columna Efectivo
                if (_tipoPago == "en Efectivo") {
                    gotoxy(66, y); cout << "s/" << setw(14) << e.aporte << "|";
                    aporteTotalEfectivo += e.aporte;
                } else {
                    gotoxy(66, y); cout << setw(16) << " " << "|";
                }

                // Columna Depósito BCP
                if (_tipoPago == "en BCP") {
                    gotoxy(84, y); cout << "s/" << setw(13) << e.aporte << "|";
                    aporteTotalBcp += e.aporte;
                } else {
                    gotoxy(84, y); cout << setw(15) << " " << "|";
                }

                // Columna Vía Web
                if (_tipoPago == "Via Web") {
                    gotoxy(100, y); cout << "s/" << setw(10) << e.aporte;gotoxy(112,y); cout <<"|";
                    aporteTotalWeb += e.aporte;
                } else {
                    gotoxy(100, y); cout << setw(10) << " ";gotoxy(112,y); cout <<"|";
                }

                // Columna Egreso Neto (vacía por ahora)
                gotoxy(114, y); cout << setw(12) << " " << "|";
                y++;
            }
        }
    } // fin while

    // Imprimir Totales
    gotoxy(0, y++); cout << "+----------------------------+----------------------+------------+----------------+----------------+------------+-------------+";
    gotoxy(0, y); cout << left << "| Egresos Totales (x pago)    ";gotoxy(29,y); cout <<"|";
    gotoxy(30, y); cout << "s/" << setw(20) << aporteTotalTransaccion << "|";
    gotoxy(53, y); cout << "s/" << setw(12) << aporteTotalYape; gotoxy(65,y);cout<<"|";
    gotoxy(66, y); cout << "s/" << setw(14) << aporteTotalEfectivo << "|";
    gotoxy(83, y); cout << "s/" << setw(14) << aporteTotalBcp << "|";
    gotoxy(100, y); cout << "s/" << setw(16) << aporteTotalWeb; gotoxy(112,y); cout<<"|";
    egresoTotalNeto = aporteTotalTransaccion + aporteTotalYape + aporteTotalEfectivo + aporteTotalBcp + aporteTotalWeb;
    gotoxy(113, y); cout << "s/" << setw(11) << egresoTotalNeto << "|";
    y++;
    gotoxy(0, y); cout << "+----------------------------+----------------------+------------+----------------+----------------+------------+-------------+";

    archivo.close();
    cin.ignore();
}


void menuConsumo(const string& mes, const string& edificio){ // Ponerlo en un archivo (Control_Caja)
    string temp_mes = mes, temp_edificio = edificio;
    char r1 = ' ';
    do {
        system("CLS");
        printtitle();
        gotoxy(40,14);
        cout <<"▂▃▄▅▆▇█▓▒░MENU DE CONSUMO░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(40, 16); cout << " 1.- CONSUMO DE AGUA";
        gotoxy(40, 17); cout << " 2.- CONSUMO DE LUZ";
        gotoxy(40, 18); cout << " 0.- Salir";
        gotoxy(40, 19); cout << " Elija una opcion: ";
        cin >> r1;

        switch (r1) {
            case '0':
                return;
                break;

            case '1':
                system("CLS");
                menuTipoPago(temp_mes, temp_edificio, "Pago Agua");
                break;

            case '2':
                system("CLS");
                menuTipoPago(temp_mes, temp_edificio, "Pago Luz");
                break;

            default:
                gotoxy(35, 18); cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
        gotoxy(35, 20);
        system("pause");
    } while (r1 != '0');
}

void menuControlDeCaja(const string& mes, const string& edificio) { // Ponerlo en un archivo (Control_Caja)
    char r = ' ';
    string temp_mes = mes, temp_edificio = edificio;
    do {
        system("CLS");
        printtitle1();
        gotoxy(40, 11); cout <<"▂▃▄▅▆▇█▓▒░GESTION DE CONTROL DE CAJA░▒▓█▇▆▅▄▃▂" << endl;
        gotoxy(40, 13); cout << " 1.- REGISTRO DE EGRESOS";
        gotoxy(40, 14); cout << " 2.- VER EGRESOS";
        gotoxy(40, 15); cout << " 3.- REGISTRO DE CONSUMO";
        gotoxy(40, 16); cout << " 4.- INGRESAR CUOTA GENERAL";
        gotoxy(40, 17); cout << " 5.- VER CUOTA GENERAL";
        gotoxy(40, 18); cout << " 6.- VER CUOTAS UNICAS";
        gotoxy(40, 19); cout << " 7.- REGISTRO DE INGRESOS";
        gotoxy(40, 20); cout << " 8.- VER INGRESOS";
        gotoxy(40, 21); cout << " 9.- VER BALANCE";
        gotoxy(40, 22); cout << " 0.- Salir";
        gotoxy(40, 24); cout << " Elija una opcion: ";
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
                // calcularCuotaGeneral(temp_mes, temp_edificio);
                break;

            case '5':
                system("CLS");
                // mostrarCuotasGenerales(temp_mes, temp_edificio);
                break;

            case '6':
                system("CLS");
                // mostrarCuotasEspecificas();
                break;

            case '7':
                system("CLS");
                // pagoCuota(temp_mes, temp_edificio);
                break;

            case '8':
                system("CLS");
                // mostrarIngresos();
                break;

            case '9':
                system("CLS");
                // mostrarBalance();
                break;

            default:
                gotoxy(35, 25); cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
        cin.ignore();
    } while (r != '0');
}