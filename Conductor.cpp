//
// Created by PC on 4/9/2023.
//

#include "Conductor.h"
Conductor::Conductor() {}

Conductor::Conductor(const std::string& nombre, const std::string& apellido, const std::string& numero_documento_identidad, const std::string& numero_seguro_social, const std::string& numero_telefono) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->numero_documento_identidad = numero_documento_identidad;
    this->numero_seguro_social = numero_seguro_social;
    this->numero_telefono = numero_telefono;
}

void Conductor::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Conductor::setApellido(const std::string& apellido) {
    this->apellido = apellido;
}

void Conductor::setNumeroDocumentoIdentidad(const std::string& numero_documento_identidad) {
    this->numero_documento_identidad = numero_documento_identidad;
}

void Conductor::setNumeroSeguroSocial(const std::string& numero_seguro_social) {
    this->numero_seguro_social = numero_seguro_social;
}

void Conductor::setNumeroTelefono(const std::string& numero_telefono) {
    this->numero_telefono = numero_telefono;
}

std::string Conductor::getNombre() const {
    return this->nombre;
}

std::string Conductor::getApellido() const {
    return this->apellido;
}

std::string Conductor::getNumeroDocumentoIdentidad() const {
    return this->numero_documento_identidad;
}

std::string Conductor::getNumeroSeguroSocial() const {
    return this->numero_seguro_social;
}

std::string Conductor::getNumeroTelefono() const {
    return this->numero_telefono;
}