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
    void procesarArchivo(string contenidoArchivo);
    void eliminarPalabra(string palabra);
    string buscarPalabra(string palabra);
    string obtenerPaginasDeCapitulo(int numeroCapitulo);
    string obtenerContadoresDocumento();
    string obtenerCapituloInciosDEPaginas();

   private:
    map<string, vector<PaginaCapitulo>> indice;
    map<int, int> capitulos_paginas;
    int totalCapitulos = 0;
    int totalPaginas = 0;
    int totalLineas = 0;
    int totalPalabras = 0;
    int palabrasUnicas = 0;
};

#endif  // ENGINE_HPP