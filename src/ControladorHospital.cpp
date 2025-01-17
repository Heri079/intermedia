#include "ControladorHospital.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// --- Cargar datos ---

void ControladorHospital::leerDatos() {
    // Leer médicos desde el archivo CSV
    std::ifstream medicosFile("medicos.csv");
    if (medicosFile.is_open()) {
        std::string line;
        while (std::getline(medicosFile, line)) {
            std::stringstream ss(line);
            int id;
            std::string nombre, especialidad;

            // Leer columnas separadas por comas
            std::getline(ss, nombre, ',');
            ss >> id;
            ss.ignore(); // Ignorar la coma que separa "id" y "especialidad"
            std::getline(ss, especialidad);

            if (!nombre.empty()) { // Evitar entradas vacías
                medicos.emplace_back(id, nombre);
                medicos.back().especialidad = especialidad; // Asignar especialidad
            }
        }
        medicosFile.close();
        std::cout << "Datos de médicos cargados exitosamente desde medicos.csv.\n";
    } else {
        std::cout << "No se pudo abrir el archivo de médicos.\n";
    }

    // Leer pacientes desde el archivo CSV
    std::ifstream pacientesFile("pacientes.csv");
    if (pacientesFile.is_open()) {
        std::string line;
        while (std::getline(pacientesFile, line)) {
            std::stringstream ss(line);
            int id;
            std::string nombre, enfermedad;

            // Leer columnas separadas por comas
            std::getline(ss, nombre, ',');
            ss >> id;
            ss.ignore(); // Ignorar la coma que separa "id" y "enfermedad"
            std::getline(ss, enfermedad);

            if (!nombre.empty()) { // Evitar entradas vacías
                pacientes.emplace_back(id, nombre, enfermedad);
            }
        }
        pacientesFile.close();
        std::cout << "Datos de pacientes cargados exitosamente desde pacientes.csv.\n";
    } else {
        std::cout << "No se pudo abrir el archivo de pacientes.\n";
    }
    // Leer citas
    std::ifstream citasFile("citas.csv");
    if (citasFile.is_open()) {
        std::string line;
        while (std::getline(citasFile, line)) {
            std::stringstream ss(line);
            int idPaciente, idMedico;
            std::string fecha;
            ss >> idPaciente;
            ss.ignore();
            ss >> idMedico;
            ss.ignore();
            std::getline(ss, fecha);
            citas.emplace_back(idPaciente, idMedico, fecha);
        }
        citasFile.close();
        std::cout << "Datos de citas cargados exitosamente.\n";
    }
}



// --- Guardar datos ---

void ControladorHospital::guardarDatos() {
    // Guardar médicos en un archivo CSV
    std::ofstream medicosFile("medicos.csv");
    if (medicosFile.is_open()) {
        for (const auto &medico : medicos) {
            medicosFile << medico.nombre << "," << medico.id << "," << medico.especialidad << "\n";
        }
        medicosFile.close();
        std::cout << "Datos de médicos guardados exitosamente en medicos.csv.\n";
    } else {
        std::cerr << "Error al abrir el archivo de médicos para guardar.\n";
    }

    // Guardar pacientes en un archivo CSV
    std::ofstream pacientesFile("pacientes.csv");
    if (pacientesFile.is_open()) {
        for (const auto &paciente : pacientes) {
            pacientesFile << paciente.nombre << "," << paciente.id << "," << paciente.enfermedad << "\n";
        }
        pacientesFile.close();
        std::cout << "Datos de pacientes guardados exitosamente en pacientes.csv.\n";
    } else {
        std::cerr << "Error al abrir el archivo de pacientes para guardar.\n";
    }
       // Guardar citas
    std::ofstream citasFile("citas.csv");
    if (citasFile.is_open()) {
        for (const auto &cita : citas) {
            citasFile << cita.idPaciente << "," << cita.idMedico << "," << cita.fecha << "\n";
        }
        citasFile.close();
        std::cout << "Datos de citas guardados exitosamente.\n";
    }
}



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
    if (pacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
    } else {
        for (const auto &paciente : pacientes) {
            std::cout << "ID: " << paciente.id
                      << ", Nombre: " << paciente.nombre
                      << ", Especialidad: " << paciente.enfermedad << "\n";
        }
    }
}

// --- Gestión de Citas ---

void ControladorHospital::asignarCita() {
    int idPaciente, idMedico;
    std::string fecha;

    std::cout << "Ingrese ID del paciente: ";
    std::cin >> idPaciente;
    std::cout << "Ingrese ID del médico: ";
    std::cin >> idMedico;
    std::cout << "Ingrese fecha de la cita (DD/MM/AAAA): ";
    std::cin.ignore();
    std::getline(std::cin, fecha);

    // Verificar si el paciente y el médico existen
    auto pacienteEncontrado = std::find_if(pacientes.begin(), pacientes.end(),
                                           [idPaciente](const Paciente &p) { return p.id == idPaciente; });
    auto medicoEncontrado = std::find_if(medicos.begin(), medicos.end(),
                                         [idMedico](const Medico &m) { return m.id == idMedico; });

    if (pacienteEncontrado != pacientes.end() && medicoEncontrado != medicos.end()) {
        citas.emplace_back(idPaciente, idMedico, fecha);
        std::cout << "Cita asignada exitosamente.\n";
    } else {
        std::cout << "Paciente o médico no encontrado. Cita no asignada.\n";
    }
}
void ControladorHospital::cancelarCita() {
    int idPaciente, idMedico;
    std::cout << "Ingrese ID del paciente: ";
    std::cin >> idPaciente;
    std::cout << "Ingrese ID del médico: ";
    std::cin >> idMedico;

    auto it = std::remove_if(citas.begin(), citas.end(),
                             [idPaciente, idMedico](const Cita &c) {
                                 return c.idPaciente == idPaciente && c.idMedico == idMedico;
                             });

    if (it != citas.end()) {
        citas.erase(it, citas.end());
        std::cout << "Cita cancelada exitosamente.\n";
    } else {
        std::cout << "Cita no encontrada.\n";
    }
}
void ControladorHospital::modificarCita() {
    int idPaciente, idMedico;
    std::cout << "Ingrese el ID del paciente de la cita a modificar: ";
    std::cin >> idPaciente;
    std::cout << "Ingrese el ID del médico de la cita a modificar: ";
    std::cin >> idMedico;

    // Buscar la cita correspondiente
    auto it = std::find_if(citas.begin(), citas.end(), 
                           [idPaciente, idMedico](const Cita &cita) {
                               return cita.idPaciente == idPaciente && cita.idMedico == idMedico;
                           });

    if (it != citas.end()) {
        // Cita encontrada
        std::cout << "Cita encontrada:\n";
        std::cout << "ID Paciente: " << it->idPaciente
                  << ", ID Médico: " << it->idMedico
                  << ", Fecha: " << it->fecha << "\n";

        int opcion;
        std::cout << "Seleccione qué desea modificar:\n";
        std::cout << "1. Cambiar fecha\n";
        std::cout << "2. Cambiar médico\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nuevaFecha;
            std::cout << "Ingrese la nueva fecha (DD/MM/AAAA): ";
            std::cin.ignore();
            std::getline(std::cin, nuevaFecha);
            it->fecha = nuevaFecha;
            std::cout << "Fecha actualizada exitosamente.\n";
        } else if (opcion == 2) {
            int nuevoIdMedico;
            std::cout << "Ingrese el nuevo ID del médico: ";
            std::cin >> nuevoIdMedico;

            // Verificar si el nuevo médico existe
            auto medicoEncontrado = std::find_if(medicos.begin(), medicos.end(),
                                                 [nuevoIdMedico](const Medico &m) {
                                                     return m.id == nuevoIdMedico;
                                                 });
            if (medicoEncontrado != medicos.end()) {
                it->idMedico = nuevoIdMedico;
                std::cout << "Médico actualizado exitosamente.\n";
            } else {
                std::cout << "Médico con ID " << nuevoIdMedico << " no encontrado. No se realizaron cambios.\n";
            }
        } else {
            std::cout << "Opción no válida. No se realizaron cambios.\n";
        }
    } else {
        // Cita no encontrada
        std::cout << "Cita no encontrada.\n";
    }
}

void ControladorHospital::listarCitas() {
    if (citas.empty()) {
        std::cout << "No hay citas registradas.\n";
    } else {
        for (const auto &cita : citas) {
            std::cout << "ID Paciente: " << cita.idPaciente
                      << ", ID Médico: " << cita.idMedico
                      << ", Fecha: " << cita.fecha << "\n";
        }
    }
}






void ControladorHospital::generarReportePacientes() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::generarReporteCitas() { std::cout << "Función no implementada.\n"; }
void ControladorHospital::generarReporteEnfermedades() { std::cout << "Función no implementada.\n"; }


