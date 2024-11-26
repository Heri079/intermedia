#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <iostream>

class Hospital {
public:
    void cargarDatos();
    void gestionPacientes();
    void gestionMedicos();
    void gestionCitas();
    void generarReportes();
    void guardarDatos();
};

#endif // HOSPITAL_HPP
