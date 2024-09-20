#include <stdlib.h>
#include <time.h>
using namespace std;

class Usuario{
    private:
        string nom_Usuario, contr_Usuario, rol_Usuario;
        int id_Usuario;
    public:
        Usuario(string _nom_Usuario, string _contr_Usuario);
        string getNom_Usuario() const;
        string getContr_Usuario() const;
        int getId_Usuario() const;
        void setRol_Usuario(string _rol_Usuario);
        void setId_Usuario(int _id_Usuario);
};

int generate_ID() {
    srand(time(0));
    return rand() % 900000000 + 100000000;
}

Usuario::Usuario(string _nom_Usuario, string _contr_Usuario) {
    nom_Usuario = _nom_Usuario;
    contr_Usuario = _contr_Usuario;
    id_Usuario = generate_ID();  // Generar ID
}

string Usuario::getNom_Usuario() const {
    return nom_Usuario;
}

string Usuario::getContr_Usuario() const {
    return contr_Usuario;
}

int Usuario::getId_Usuario() const {
    return id_Usuario;
}

void Usuario::setRol_Usuario(string _rol_Usuario) {
    rol_Usuario = _rol_Usuario;
}

void Usuario::setId_Usuario(int _id_Usuario) {
    id_Usuario = _id_Usuario;
}
