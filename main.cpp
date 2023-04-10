#include <iostream>
#include "empresa.h"

int main() {
    Empresa empresa;

    int opcion = 0;
    while (opcion != 5) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Agregar taxi" << std::endl;
        std::cout << "2. Solicitar taxi" << std::endl;
        std::cout << "3. Mostrar taxis disponibles" << std::endl;
        std::cout << "4. Mostrar taxis en ruta" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                empresa.agregar_taxi();
                break;
            case 2:
                empresa.solicitar_taxi();
                break;
            case 3:
                empresa.mostrar_taxis_disponibles();
                break;
            case 4:
                empresa.mostrar_taxis_en_ruta();
                break;
            case 5:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                break;
        }
    }
    return 0;
}
