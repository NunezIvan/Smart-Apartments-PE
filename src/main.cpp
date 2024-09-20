#include <iostream>
#include <cstdlib>
#include "login.cpp"

using namespace std;

int main() {
    fflush(stdin);
    int opcion;
    do {
        cout << "=====================================" << endl;
        cout << "          BIENVENIDO AL SISTEMA     " << endl;
        cout << "=====================================" << endl;
        cout << "\n";
        cout << "         1. Iniciar Sesión           " << endl;
        cout << "         2. Salir                    " << endl;
        cout << "\n"<<endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
            fflush(stdin);
                inicio_Sesion();
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
        }
    } while (opcion != 2);
    return 0;
}
