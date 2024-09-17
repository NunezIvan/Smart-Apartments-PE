#include <iostream>
#include <fstream>   // Asegúrate de incluir fstream aquí
#include <stdlib.h>
#include <usuario.hpp>
#include <usuario_Apartamento.hpp>
using namespace std;

propietario_Apartamento::propietario_Apartamento(string _nom_Usuario, string _contr_Usuario, int _num_Edificio, int _nivel_Edificio, int _num_Apartamento): Usuario(_nom_Usuario, _contr_Usuario) {
    num_Edificio = _num_Edificio;
    nivel_Edificio = _nivel_Edificio;
    num_Apartamento = _num_Apartamento;
    setRol_Usuario("Propietario");

    ofstream file("propietarios.txt", ios::app);
    if (file.is_open()) {
        file << getId_Usuario() << " " << getNom_Usuario() << " " << getContr_Usuario() << " " << num_Edificio << " " << nivel_Edificio << " " << num_Apartamento << "\n";
        file.close();
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

int propietario_Apartamento::getnum_Edificio() const {
    return num_Edificio;
}
int propietario_Apartamento::getNivel_Edificio() const {
    return nivel_Edificio;
}

int propietario_Apartamento::getnum_Apartamento() const {
    return num_Apartamento;
}
