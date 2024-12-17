#include "ControladorHospital.hpp"
#include <algorithm>

// --- Gestión de Médicos ---

void ControladorHospital::altaMedico() {
    int id;
    std::string nombre;
    std::cout << "Ingrese ID del médico: ";
    std::cin >> id;
    std::cout << "Ingrese nombre del médico: ";
    std::cin.ignore(); // Limpiar el buffer
    std::getline(std::cin, nombre);

    medicos.emplace_back(id, nombre);
    std::cout << "Médico registrado exitosamente.\n";
}

void ControladorHospital::bajaMedico() {
    int id;
    std::cout << "Ingrese ID del médico a eliminar: ";
    std::cin >> id;

    auto it = std::remove_if(medicos.begin(), medicos.end(),
                             [id](const Medico &m) { return m.id == id; });
    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        std::cout << "Médico eliminado exitosamente.\n";
    } else {
        std::cout << "Médico no encontrado.\n";
    }
}

void ControladorHospital::asignarEspecialidad() {
    int id;
    std::string especialidad;
    std::cout << "Ingrese ID del médico: ";
    std::cin >> id;
    std::cout << "Ingrese la especialidad: ";
    std::cin.ignore();
    std::getline(std::cin, especialidad);

    for (auto &medico : medicos) {
        if (medico.id == id) {
            medico.especialidad = especialidad;
            std::cout << "Especialidad asignada exitosamente.\n";
            return;
        }
    }
    std::cout << "Médico no encontrado.\n";
}

void ControladorHospital::listarMedicos() {
    if (medicos.empty()) {
        std::cout << "No hay médicos registrados.\n";
    } else {
        for (const auto &medico : medicos) {
            std::cout << "ID: " << medico.id
                      << ", Nombre: " << medico.nombre
                      << ", Especialidad: " << medico.especialidad << "\n";
        }
    }
}

// --- Gestión de Pacientes ---

void ControladorHospital::altaPaciente() {
    int id;
    std::string nombre, enfermedad;
    std::cout << "Ingrese ID del paciente: ";
    std::cin >> id;
    std::cout << "Ingrese nombre del paciente: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);
    std::cout << "Ingrese enfermedad: ";
    std::getline(std::cin, enfermedad);

    pacientes.emplace_back(id, nombre, enfermedad);
    std::cout << "Paciente registrado exitosamente.\n";
}

void ControladorHospital::bajaPaciente() {
    int id;
    std::cout << "Ingrese ID del paciente a eliminar: ";
    std::cin >> id;

    auto it = std::remove_if(pacientes.begin(), pacientes.end(),
                             [id](const Paciente &p) { return p.id == id; });
    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        std::cout << "Paciente eliminado exitosamente.\n";
    } else {
        std::cout << "Paciente no encontrado.\n";
    }
}

void ControladorHospital::modificarPaciente() {
    int id;
    std::string nuevoNombre, nuevaEnfermedad;
    std::cout << "Ingrese ID del paciente: ";
    std::cin >> id;

    for (auto &paciente : pacientes) {
        if (paciente.id == id) {
            std::cout << "Ingrese nuevo nombre: ";
            std::cin.ignore();
            std::getline(std::cin, nuevoNombre);
            std::cout << "Ingrese nueva enfermedad: ";
            std::getline(std::cin, nuevaEnfermedad);

            paciente.nombre = nuevoNombre;
            paciente.enfermedad = nuevaEnfermedad;
            std::cout << "Datos actualizados exitosamente.\n";
            return;
        }
    }
    std::cout << "Paciente no encontrado.\n";
}

void ControladorHospital::buscarPaciente() {
    int id;
    std::cout << "Ingrese ID del paciente: ";
    std::cin >> id;

    for (const auto &paciente : pacientes) {
        if (paciente.id == id) {
            std::cout << "ID: " << paciente.id
                      << ", Nombre: " << paciente.nombre
                      << ", Enfermedad: " << paciente.enfermedad << "\n";
            return;
        }
    }
    std::cout << "Paciente no encontrado.\n";
}

// --- Gestión de Citas y Reportes (No implementados en detalle) ---

void ControladorHospital::asignarCita() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::cancelarCita() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::modificarCita() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::listarCitas() { std::cout << "Función no implementada.\n"; }


void ControladorHospital::generarReportePacientes() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::generarReporteCitas() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::generarReporteEnfermedades() { std::cout << "Función no implementada.\n"; }

void ControladorHospital::guardarDatos() {
    std::cout << "Guardando datos (no implementado).\n";
}
