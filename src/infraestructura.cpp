#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "usuario_Apartamento.cpp"
using namespace std;

class Departamento {
public:
    string propietario, nmbr_edificio;
    int nmro_apartamento, nro_nivel;

    Departamento() : nmro_apartamento(0), nro_nivel(0), nmbr_edificio(""), propietario("") {}

    Departamento(int _nmro_apartamento, int _nro_nivel, string _nmbr_edificio, string _propietario = "", bool band = false){
        nmro_apartamento = _nmro_apartamento;
        nro_nivel = _nro_nivel;
        nmbr_edificio = _nmbr_edificio;
        propietario = _propietario;

        if(band){
            ofstream file("departamentos.txt", ios::app);
            if (file.is_open()) {
                file << propietario << ";" << nmro_apartamento << ";" << nro_nivel << ";" << nmbr_edificio << "\n";
                file.close();
            } else {
                cout << "No se pudo abrir el archivo para escritura." << endl;
            }
        }
    }

    string get_Propietario() {
        return propietario;
    }

    bool tienePropietario() const {
        return !propietario.empty();
    }
};

class Nivel {
public:
    int numero;
    vector<Departamento> departamentos;

    Nivel(int _numero, int cantidad_departamentos) : numero(_numero) {
        departamentos.resize(cantidad_departamentos);
    }
};

class Edificio {
public:
    string nombre;
    vector<Nivel> niveles;

    Edificio(string _nombre, int cantidad_niveles, int departamentos_por_nivel) : nombre(_nombre) {
        niveles = cargarDepartamentos(cantidad_niveles, departamentos_por_nivel);
    }

    vector<Nivel> cargarDepartamentos(int cantidad_niveles, int departamentos_por_nivel) {
        ifstream file("departamentos.txt");
        string linea;
        vector<vector<Departamento>> depsPorNivel(cantidad_niveles, vector<Departamento>(departamentos_por_nivel));

        if (file.is_open()) {
            while (getline(file, linea)) {
                stringstream ss(linea);
                string propietario, nmbr_edificio;
                int nmro_apartamento, nro_nivel;
                getline(ss, propietario, ';');
                ss >> nmro_apartamento;
                ss.ignore(); // Ignorar el punto y coma
                ss >> nro_nivel;
                ss.ignore(); // Ignorar el punto y coma
                getline(ss, nmbr_edificio);

                if (nro_nivel > 0 && nro_nivel <= cantidad_niveles && nmro_apartamento > 0 && nmro_apartamento <= departamentos_por_nivel) {
                    int idx_nivel = nro_nivel - 1;
                    int idx_apartamento = nmro_apartamento - 1;
                    depsPorNivel[idx_nivel][idx_apartamento] = Departamento(nmro_apartamento, nro_nivel, nmbr_edificio, propietario);
                }
            }
            file.close();
        } else {
            cout << "No se pudo abrir el archivo para lectura." << endl;
        }

        vector<Nivel> niveles;
        for (int i = 0; i < cantidad_niveles; ++i) {
            Nivel nivel(i + 1, departamentos_por_nivel);
            nivel.departamentos = depsPorNivel[i];
            niveles.push_back(nivel);
        }
        return niveles;
}
    void mostrarDepartamentos() const {
        cout << "Edificio " << nombre << ":\n";
        char lastChar = nombre.back();  // Obtener el último carácter del nombre del edificio

        for (const auto& nivel : niveles) {
            cout << "\tNivel " << nivel.numero << ":\n";
            for (const auto& dep : nivel.departamentos) {
                // Comprueba si el último carácter del nombre del edificio del departamento coincide con el del edificio actual
                if (!dep.nmbr_edificio.empty() && dep.nmbr_edificio.back() == lastChar) {
                    string propietario_modificado = dep.propietario;
                    replace(propietario_modificado.begin(), propietario_modificado.end(), '_', ' '); // Reemplaza '_' por ' '
                    cout << "\t\tDepartamento: " << dep.nmro_apartamento
                        << ", Propietario: " << (propietario_modificado.empty() ? "sin propietario" : propietario_modificado) << "\n";
                }
            }
        }
    }



    Departamento& obtenerDepartamento(int nivel, int numero_departamento) {
        return niveles[nivel - 1].departamentos[numero_departamento - 1];
    }

};



    