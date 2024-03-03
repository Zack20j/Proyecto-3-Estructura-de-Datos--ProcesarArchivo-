#include "engine.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>
#include "storage/archive.hpp"

using namespace std;

Engine::Engine(string filename) {
    FileManager fileManager(filename);
    string contenidoArchivo = fileManager.obtenerContenido();
    procesarArchivo(contenidoArchivo);
    fileManager.guardar("indice_palabras.txt", obtenerIndiceOrdenado());
}

string Engine::obtenerContenidoCapituloYPaginas() {
    string resultado = "Contenido del documento:\n";
    for (const auto& par : contenidoPorCapitulo) {
        resultado += "Capítulo " + to_string(par.first) + " Inicia en la Página " + to_string(par.second.begin()->first) + "\n";
        for (const auto& pagina : par.second) {
            resultado += "Página " + to_string(pagina.first) + ":\n";
            for (const auto& linea : pagina.second) {
                resultado += linea + "\n";
            }
        }
    }
    return resultado;
}

string Engine::obtenerIndiceOrdenado() {
    string resultado;
    char letra_actual = '\0'; 

    for (const auto& entrada : indice) {
        string palabra = entrada.first;

        if (palabra[0] != letra_actual) {
            letra_actual = palabra[0]; 
            if (letra_actual != '\0') {  
                resultado += "\n";  
            }
            resultado += letra_actual; 
            resultado += "\n";
        }

        resultado += palabra + " - ";
        for (const auto& pc : entrada.second) {
            resultado += to_string(pc.pagina) + ", ";
        }
        resultado += "\n";
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

string Engine::obtenerPalabrasDeCapitulo(int numeroCapitulo) {
    if (numeroCapitulo > totalCapitulos || numeroCapitulo < 0) {
        return "Capítulo inexistente";
    }

    string resultado = "Capítulo " + to_string(numeroCapitulo) + "\n";

    char letra_actual = '\0'; // Inicializar la letra actual con un valor que no sea una letra

    // Iterar sobre cada entrada en el índice
    for (const auto& entrada : indice) {
        const string& palabra = entrada.first;
        string paginas;

        // Verificar si la palabra aparece en el capítulo indicado
        for (const auto& pc : entrada.second) {
            if (pc.capitulo == numeroCapitulo) {
                // Verificar si la primera letra de la palabra es una letra nueva
                if (palabra[0] != letra_actual) {
                    letra_actual = palabra[0]; // Actualizar la letra actual
                    resultado += "\n" + string(1, letra_actual) + "\n"; // Agregar la letra como encabezado
                }

                // Agregar la página al resultado
                if (!paginas.empty()) {
                    paginas += ",";
                }
                paginas += to_string(pc.pagina);
            }
        }

        // Agregar la palabra y las páginas al resultado
        if (!paginas.empty()) {
            resultado += palabra + " : " + paginas + "\n";
        }
    }

    return resultado;
}

void Engine::eliminarPalabra(string palabra) {
    if (palabra == "" || indice.find(palabra) == indice.end()) {
        cout << "Palabra inexistente" << endl;
        return;
    }

    indice.erase(palabra);

    FileManager fileManager("indice_palabras.txt");
    fileManager.guardar("indice_palabras.txt", obtenerIndiceOrdenado());
}

string Engine::buscarPalabra(string palabra) {
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
    }else{
        resultado = "Palabra inexistente";
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
        } else if (regex_search(linea, match, regex_pagina)) {
            pagina_actual++;

        } else {
            contenidoPorCapitulo[capitulo_actual][pagina_actual].push_back(linea);//prueba
            for (sregex_iterator it(linea.begin(), linea.end(), regex_palabra),
                 end_it;
                 it != end_it; ++it) {
                string palabra = it->str();
                totalPalabras++;
                PaginaCapitulo pc;
                pc.capitulo = capitulo_actual;
                pc.pagina = pagina_actual;
                bool encontrada = false;

                for (auto& entrada : indice[palabra]) {
                    if (entrada.capitulo == pc.capitulo &&
                        entrada.pagina == pc.pagina) {
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