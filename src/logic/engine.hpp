#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct PaginaCapitulo {
    int capitulo;
    int pagina;
};

class Engine {
   public:
    Engine(string filename);

    string obtenerIndiceOrdenado();
    void eliminarPalabra(string palabra);
    string buscarPalabra(string palabra);
    string obtenerPalabrasDeCapitulo(int numeroCapitulo);
    string obtenerContadoresDocumento();
    string obtenerContenidoCapituloYPaginas();

   private:

    void procesarArchivo(string contenidoArchivo);
    map<string, vector<PaginaCapitulo>> indice;
    map<int, map<int, vector<string>>> contenidoPorCapitulo;
    int totalCapitulos = 0;
    int totalPaginas = 0;
    int totalLineas = 0;
    int totalPalabras = 0;
    int palabrasUnicas = 0;
};

#endif  // ENGINE_HPP