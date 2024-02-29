#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "archive.hpp"

using namespace std;

FileManager::FileManager(std::string filename) : filename(filename) {}

void FileManager::guardar(string nombreArchivo, string contenido) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << contenido;
        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
    }
}

string FileManager:: obtenerContenido() {

    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
        return ""; 
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf(); 
    return buffer.str();
}
