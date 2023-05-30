#include <iostream>
#include "empresa.h"
#include "cstdlib"


int main() {
    Empresa empresa;
    empresa.cargar_datos();
    empresa.mostrar_menus();
    return 0;
}
