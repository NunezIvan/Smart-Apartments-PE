#include <iostream>
#include <fstream>
#include <vector>
#include "infraestructura.cpp"
#include "usuario_Apartamento.cpp"
#include "administrador.cpp"

using namespace std;

string nombre_propietario, apellido_propietario;

void mostrarEdificios(const vector<Edificio>& edificios) {
    for (const auto& edificio : edificios) {
        edificio.mostrarDepartamentos();
    }
}

void registrarPropietario(vector<Edificio>& edificios) {
    string nombre, apellido, edificioNombre;
    int nro_nivel, nmro_apartamento;

    cout << "Ingrese el nombre del propietario: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer correctamente
    getline(cin, nombre);
    cout << "Ingrese el apellido del propietario: ";
    getline(cin, apellido);
    cout << "Ingrese el nombre del edificio: ";
    cin >> edificioNombre;
    cout << "Ingrese el número de nivel: ";
    cin >> nro_nivel;
    cout << "Ingrese el número de apartamento: ";
    cin >> nmro_apartamento;

    bool encontrado = false;
    for (auto& edificio : edificios) {
        if (edificio.nombre == edificioNombre) {
            if (nro_nivel > 0 && nro_nivel <= edificio.niveles.size()) {
                if (nmro_apartamento > 0 && nmro_apartamento <= edificio.niveles[nro_nivel - 1].departamentos.size()) {
                    Departamento& depto = edificio.obtenerDepartamento(nro_nivel, nmro_apartamento);
                    if (!depto.tienePropietario()) {
                        depto.propietario = nombre + "_" + apellido;
                        cout << "Propietario registrado exitosamente.\n";
                        propietario_Apartamento(nombre,apellido,nmro_apartamento,nro_nivel,edificioNombre);
                        Departamento(nmro_apartamento,nro_nivel,edificioNombre,depto.propietario,true);  
                        encontrado = true;
                        break;
                    } else {
                        cout << "Error: Este departamento ya tiene propietario.\n";
                        encontrado = true;
                        break;
                    }
                }
            }
        }
    }

    if (!encontrado) {
        cout << "Error: Datos no válidos o fuera de rango.\n";
    }
}




void manejarPropietarios(){
    int opcion;
    vector<Edificio> edificios = {Edificio("Edificio_1", 5, 4), Edificio("Edificio_2", 5, 4)};

    do{
        cout << "1. Mostrar información de los edificios\n";
        cout << "2. Registrar un nuevo propietario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarEdificios(edificios);
                break;
            case 2:
                registrarPropietario(edificios);
                break;
            case 3:
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    }while(opcion !=3);
}
