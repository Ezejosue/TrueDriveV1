//
// Created by PC on 4/9/2023.
//

#include "Taxi.h"
Taxi::Taxi() {}

Taxi::Taxi(const std::string& placa, const std::string& numero_motor, const std::string& modelo, int year, const std::string& categoria, const Conductor& conductor) {
    this->placa = placa;
    this->numero_motor = numero_motor;
    this->modelo = modelo;
    this->year = year;
    this->categoria = categoria;
    this->conductor = conductor;
}

void Taxi::setPlaca(const std::string& placa) {
    this->placa = placa;
}

void Taxi::setNumeroMotor(const std::string& numero_motor) {
    this->numero_motor = numero_motor;
}

void Taxi::setModelo(const std::string& modelo) {
    this->modelo = modelo;
}

void Taxi::setYear(int year) {
    this->year = year;
}

void Taxi::setCategoria(const std::string& categoria) {
    this->categoria = categoria;
}

void Taxi::setConductor(const Conductor& conductor) {
    this->conductor = conductor;
}

std::string Taxi::getPlaca() const {
    return this->placa;
}

std::string Taxi::getNumeroMotor() const {
    return this->numero_motor;
}

std::string Taxi::getModelo() const {
    return this->modelo;
}

int Taxi::getYear() const {
    return this->year;
}

std::string Taxi::getCategoria() const {
    return this->categoria;
}

Conductor Taxi::getConductor() const {
    return this->conductor;
}