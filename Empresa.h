//
// Created by PC on 4/9/2023.
//

#ifndef EMPRESA_H
#define EMPRESA_H

#include <vector>
#include <string>
#include "conductor.h"
#include "taxi.h"
#include "cliente.h"
#include <queue>

class Empresa {
public:
    Empresa();
    void agregar_taxi();
    bool validar_taxi(Taxi& nuevo_taxi);
    bool validar_conductor(Conductor& nuevo_conductor);
    bool buscar_conductor(std::string numero_documento_identidad);
    void mostrar_taxis();
    void agregar_a_cola(Taxi taxi);
    bool asignar_taxi(Cliente cliente);
    void solicitar_taxi();
    void reingresar_a_cola();
    void mostrar_taxis_disponibles();
    void mostrar_taxis_en_ruta();
    static std::queue<Taxi> taxis_en_espera;
    static std::queue<Taxi> cola_ruta_;


private:
    std::vector<Taxi> taxis_;
};



#endif //EMPRESA_H
