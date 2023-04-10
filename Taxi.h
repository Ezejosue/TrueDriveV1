//
// Created by PC on 4/9/2023.
//

#ifndef TAXI_H
#define TAXI_H
#include "conductor.h"

class Taxi {
public:
    std::string placa;
    std::string numero_motor;
    std::string modelo;
    int year;
    std::string categoria;
    Conductor conductor;
    // Otros datos necesarios

    // Constructor por defecto
    Taxi();

    // Constructor con parámetros
    Taxi(const std::string& placa, const std::string& numero_motor, const std::string& modelo, int year, const std::string& categoria, const Conductor& conductor);

    // Funciones setter
    void setPlaca(const std::string& placa);
    void setNumeroMotor(const std::string& numero_motor);
    void setModelo(const std::string& modelo);
    void setYear(int year);
    void setCategoria(const std::string& categoria);
    void setConductor(const Conductor& conductor);

    // Funciones getter
    std::string getPlaca() const;
    std::string getNumeroMotor() const;
    std::string getModelo() const;
    int getYear() const;
    std::string getCategoria() const;
    Conductor getConductor() const;
};


#endif //TAXI_H
