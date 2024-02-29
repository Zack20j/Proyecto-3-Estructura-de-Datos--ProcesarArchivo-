#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <algorithm>
#include "storage/archive.hpp"
#include "engine.hpp"

using namespace std;

Engine::Engine(string filename) {
    FileManager fileManager(filename);
    string contenidoArchivo = fileManager.obtenerContenido();
    procesarArchivo(contenidoArchivo);
    fileManager.guardarIndice("indice_palabras.txt", obtenerIndiceOrdenado());
    fileManager.guardarIndice("contadores.txt", obtenerContadoresDocumento()); // quizas no hace falta
}

string Engine::obtenerIndiceOrdenado() {
    string resultado;
    for (const auto& entrada : indice) {
        resultado += entrada.first + " - ";
        for (const auto& pc : entrada.second) {
            resultado += to_string(pc.pagina) + ", ";
        }
        resultado += "\n";
    }
    return resultado;
}

string Engine::obtenerCapituloInciosDEPaginas() {
    string resultado = "Contenido del documento:\n";
    for (const auto& par : capitulos_paginas) {
        resultado += "Capítulo " + to_string(par.first) + " - Página " + to_string(par.second) + "\n";
    }
    return resultado;
}

string Engine::obtenerContadoresDocumento() {
    string informacion;
    informacion += "Total de Capítulos: " + to_string(totalCapitulos) + "\n";
    informacion += "Total de Páginas: " + to_string(totalPaginas) + "\n";
    informacion += "Total de Líneas: " + to_string(totalLineas) + "\n";
    informacion += "Total de Palabras: " + to_string(totalPalabras) + "\n";
    informacion += "Palabras Únicas: " + to_string(palabrasUnicas) + "\n";
    return informacion;
}

string Engine::obtenerPaginasDeCapitulo(int numeroCapitulo) {

    if (numeroCapitulo > totalCapitulos || numeroCapitulo < 0){
        return "Capítulo inexistente";
    }
    
    string resultado = "Capítulo " + to_string(numeroCapitulo) + "\n";
    for (const auto& entrada : indice) {

        bool encontrada = false; 
        for (const auto& pc : entrada.second) {
            if (pc.capitulo == numeroCapitulo) {
                if (!encontrada) {
                    resultado += entrada.first + " : " + to_string(pc.pagina) + ", ";
                    encontrada = true;
                } else {
                    resultado += to_string(pc.pagina) + ", ";
                }
            }
        }
        if (encontrada) {
            resultado += "\n";
        }
    }
    return resultado;
}

void Engine:: eliminarPalabra( string palabra) {

    if (palabra == "" || indice.find(palabra) == indice.end()) {
        cout << "Palabra inexistente" << endl;
        return;
    }

    indice.erase(palabra);
}

string Engine::buscarPalabra( string palabra) {

    if (palabra == "" || indice.find(palabra) == indice.end()) {
        return "Palabra inexistente";
    }

    string resultado;
    auto it = indice.find(palabra);
    if (it != indice.end()) {
        resultado += palabra + ": ";
        for (const auto& pc : it->second) {
            resultado += to_string(pc.pagina) + ", ";
        }
        // Eliminar la última coma y espacio
        resultado.pop_back();
        resultado.pop_back();
    }
    return resultado;
}

void Engine::procesarArchivo(string contenidoArchivo) {

    istringstream archivo(contenidoArchivo);

    int capitulo_actual = 0;
    int pagina_actual = 0;
    string linea;
    regex regex_capitulo("<capitulo (\\d+) - .*>");
    regex regex_pagina("<pagina (\\d+)>");
    regex regex_palabra("\\b\\w+\\b"); 

    while (getline(archivo, linea)) {
        totalLineas++;

        smatch match;
        if (regex_search(linea, match, regex_capitulo)) {
            capitulo_actual++;

            if (pagina_actual == 0){
                capitulos_paginas[capitulo_actual] = 1;
            }
            else {
                capitulos_paginas[capitulo_actual] = pagina_actual;
            }

        } else if (regex_search(linea, match, regex_pagina)) {
            pagina_actual++;

        } else {
            for (sregex_iterator it(linea.begin(), linea.end(), regex_palabra), end_it; it != end_it; ++it) {
                string palabra = it->str();
                totalPalabras++;
                PaginaCapitulo pc;
                pc.capitulo = capitulo_actual;
                pc.pagina = pagina_actual;
                bool encontrada = false;

                for (auto &entrada : indice[palabra]) {
                    if (entrada.capitulo == pc.capitulo && entrada.pagina == pc.pagina) {
                        encontrada = true;
                        break;
                    }
                }

                if (!encontrada) {
                    indice[palabra].push_back(pc);
                }
            }
        }
    }

    totalCapitulos = capitulo_actual;
    totalPaginas = pagina_actual;
    palabrasUnicas = indice.size();
}