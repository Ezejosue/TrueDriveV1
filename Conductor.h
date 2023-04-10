//
// Created by PC on 4/9/2023.
//

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include <string>

class Conductor {
public:
    std::string nombre;
    std::string apellido;
    std::string numero_documento_identidad;
    std::string numero_seguro_social;
    std::string numero_telefono;
    // Otros datos necesarios

    // Constructor por defecto
    Conductor();

    // Constructor con parámetros
    Conductor(const std::string& nombre, const std::string& apellido, const std::string& numero_documento_identidad, const std::string& numero_seguro_social, const std::string& numero_telefono);

    // Funciones setter
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setNumeroDocumentoIdentidad(const std::string& numero_documento_identidad);
    void setNumeroSeguroSocial(const std::string& numero_seguro_social);
    void setNumeroTelefono(const std::string& numero_telefono);

    // Funciones getter
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNumeroDocumentoIdentidad() const;
    std::string getNumeroSeguroSocial() const;
    std::string getNumeroTelefono() const;
};


#endif //CONDUCTOR_H
