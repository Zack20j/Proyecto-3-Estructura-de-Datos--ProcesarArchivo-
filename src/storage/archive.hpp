#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <sstream>
#include <string>

class FileManager {
   public:
    FileManager(std::string filename);
    std::string obtenerContenido();
    void guardar(std::string nombreArchivo, std::string contenido);

   private:
    std::string filename;
};

#endif  // FILEMANAGER_HPP