#include "scene.hpp"
#include <iostream>
#include "logic/engine.hpp"

using namespace std;

void Menu::limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Para sistemas Windows
#else
    system("clear");  // Para sistemas Unix/Linux
#endif
}

void Menu::pausar() {
#ifdef _WIN32
    system("pause");  // Para sistemas Windows
#else
    cout << "Pulse una tecla para continuar..." << endl;
    cin.ignore();  // Limpiar el buffer de entrada
    cin.get();
#endif
}

void Menu::mostrarMenu() {
    nombreArchivo = "ArchivoPrueba.txt";
    Engine engine = Engine(nombreArchivo);
    string palabra;
    int opcion;

    do {
        cout << "=== Menú ===" << endl;
        cout << "1. Indice ordenado alfabéticamente" << endl;
        cout << "2. Indice ordenado de un capítulo en particular" << endl;
        cout << "3. Buscar una palabra" << endl;
        cout << "4. Eliminar una palabra del índice" << endl;
        cout << "5. Capítulo en qué página inicia" << endl;
        cout << "6. Contadores del documento" << endl;
        cout << "7. Salir" << endl;
        cout << "Por favor, ingrese el número correspondiente a la opción "
                "deseada: ";
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << engine.obtenerIndiceOrdenado() << endl;
                break;
            case 2:
                cout << "Ingrese el capítulo deseado: ";
                int capitulo;
                cin >> capitulo;
                cout << engine.obtenerPaginasDeCapitulo(capitulo) << endl;
                break;
            case 3:
                cout << "Ingrese la palabra a buscar: ";
                cin >> palabra;
                cout << engine.buscarPalabra(palabra) << endl;
                break;

            case 4:
                cout << "Ingrese la palabra a eliminar: ";
                cin >> palabra;
                engine.eliminarPalabra(palabra);
                break;
            case 5:
                cout << engine.obtenerCapituloInciosDEPaginas() << endl;
                break;
            case 6:
                cout << "Contadores del documento:" << endl;
                cout << engine.obtenerContadoresDocumento() << endl;
                break;
            case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese un número válido."
                     << endl;
                break;
        }
        if (opcion != 7) {
            pausar();
            limpiarPantalla();
        }
    } while (opcion != 7);
}
