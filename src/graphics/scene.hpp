#ifndef MENU_HPP
#define MENU_HPP

#include <string>

using namespace std;

class Menu {
private:

    string nombreArchivo;
    void  pausar();
    void limpiarPantalla();

public:
    void mostrarMenu();
    
};

#endif // MENU_HPP