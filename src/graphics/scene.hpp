#ifndef MENU_HPP
#define MENU_HPP

#include <string>

using namespace std;

class Menu {
   public:
    void mostrarMenu();

   private:
    string nombreArchivo;
    void pausar();
    void limpiarPantalla();
};

#endif  // MENU_HPP