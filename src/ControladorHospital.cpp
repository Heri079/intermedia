#include "ControladorHospital.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <map>    
#include <vector>

// --- Cargar datos ---

void ControladorHospital::leerDatos() {
    // Leer médicos desde el archivo CSV
    std::ifstream medicosFile("medicos.csv");
    if (medicosFile.is_open()) {
        std::string line;
        std::getline(medicosFile, line); // Ignorar encabezado
        while (std::getline(medicosFile, line)) {
            if (!line.empty()) {
                medicos.emplace_back(line);
            }
        }
        medicosFile.close();
        std::cout << "Datos de médicos cargados exitosamente desde medicos.csv.\n";
    } else {
        std::cerr << "No se pudo abrir el archivo de médicos.\n";
    }

    // Leer pacientes desde el archivo CSV
    std::ifstream pacientesFile("pacientes.csv");
    if (pacientesFile.is_open()) {
        std::string line;
        std::getline(pacientesFile, line); // Ignorar encabezado
        while (std::getline(pacientesFile, line)) {
            if (!line.empty()) {
                pacientes.emplace_back(line);
            }
        }
        pacientesFile.close();
        std::cout << "Datos de pacientes cargados exitosamente desde pacientes.csv.\n";
    } else {
        std::cerr << "No se pudo abrir el archivo de pacientes.\n";
    }

    // Leer citas
    std::ifstream citasFile("citas.csv");
if (citasFile.is_open()) {
    std::string line;
    std::getline(citasFile, line); // Ignorar encabezado
    while (std::getline(citasFile, line)) {
        if (!line.empty()) {
            citas.emplace_back(line); // Leer con el nuevo formato que incluye estado
        }
    }
    citasFile.close();
    std::cout << "Datos de citas cargados exitosamente desde citas.csv.\n";
} else {
    std::cerr << "No se pudo abrir el archivo de citas.\n";
}

}




// --- Guardar datos ---

void ControladorHospital::guardarDatos() {
    // Ordenar y guardar médicos
    std::sort(medicos.begin(), medicos.end(), [](const Medico& a, const Medico& b) {
        if (a.id != b.id)
            return a.id < b.id; // Ordenar por ID
        if (a.nombre != b.nombre)
            return a.nombre < b.nombre; // Ordenar por nombre
        return a.especialidad < b.especialidad; // Ordenar por especialidad
    });

    std::ofstream medicosFile("medicos.csv");
    if (medicosFile.is_open()) {
        medicosFile << "ID,Nombre,Especialidad\n"; // Encabezado
        for (const auto& medico : medicos) {
            medicosFile << medico.toCSV() << "\n";
        }
        medicosFile.close();
        std::cout << "Datos de médicos guardados exitosamente en medicos.csv.\n";
    } else {
        std::cerr << "Error al abrir el archivo de médicos para guardar.\n";
    }

    // Ordenar y guardar pacientes
    std::sort(pacientes.begin(), pacientes.end(), [](const Paciente& a, const Paciente& b) {
        if (a.id != b.id)
            return a.id < b.id; // Ordenar por ID
        if (a.nombre != b.nombre)
            return a.nombre < b.nombre; // Ordenar por nombre
        return a.enfermedad < b.enfermedad; // Ordenar por enfermedad
    });

    std::ofstream pacientesFile("pacientes.csv");
    if (pacientesFile.is_open()) {
        pacientesFile << "ID,Nombre,Enfermedad\n"; // Encabezado
        for (const auto& paciente : pacientes) {
            pacientesFile << paciente.toCSV() << "\n";
        }
        pacientesFile.close();
        std::cout << "Datos de pacientes guardados exitosamente en pacientes.csv.\n";
    } else {
        std::cerr << "Error al abrir el archivo de pacientes para guardar.\n";
    }

    // Guardar citas
    
    std::ofstream citasFile("citas.csv");
    if (citasFile.is_open()) {
        citasFile << "ID_Paciente,ID_Medico,Fecha,Estado\n"; // Encabezado
        for (const auto& cita : citas) {
            citasFile << cita.toCSV() << "\n";
        }
        citasFile.close();
        std::cout << "Datos de citas guardados exitosamente en citas.csv.\n";
    } else {
        std::cerr << "Error al abrir el archivo de citas para guardar.\n";
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
                      << ", Enfermedad: " << paciente.enfermedad << "\n";
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
        citas.emplace_back(idPaciente, idMedico, fecha, "Pendiente");
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
                      << ", Fecha: " << cita.fecha << "\n"
                      << ", Estado: " << cita.estado << "\n";
        }
    }
}
void ControladorHospital::cambiarEstadoCita() {
    int idPaciente, idMedico;
    std::string nuevoEstado;

    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> idPaciente;
    std::cout << "Ingrese el ID del médico: ";
    std::cin >> idMedico;

    auto it = std::find_if(citas.begin(), citas.end(),
                           [idPaciente, idMedico](const Cita &cita) {
                               return cita.idPaciente == idPaciente && cita.idMedico == idMedico;
                           });

    if (it != citas.end()) {
        std::cout << "Estado actual: " << it->estado << "\n";
        std::cout << "Ingrese el nuevo estado (Pendiente, Cancelada, Realizada): ";
        std::cin.ignore();
        std::getline(std::cin, nuevoEstado);

        if (nuevoEstado == "Pendiente" || nuevoEstado == "Cancelada" || nuevoEstado == "Realizada") {
            it->estado = nuevoEstado;
            std::cout << "Estado de la cita actualizado exitosamente.\n";
        } else {
            std::cout << "Estado no válido. No se realizaron cambios.\n";
        }
    } else {
        std::cout << "Cita no encontrada.\n";
    }
}



void ControladorHospital::generarReportePacientesAtendidos(const std::string& fechaInicio, const std::string& fechaFin) {
    std::cout << "\n--- Reporte de Pacientes Atendidos ---\n";

    // Convertir las fechas de string a un formato que se pueda comparar
    std::tm tmInicio = {};
    std::tm tmFin = {};
    std::stringstream ssInicio(fechaInicio);
    std::stringstream ssFin(fechaFin);
    
    ssInicio >> std::get_time(&tmInicio, "%d/%m/%Y");
    ssFin >> std::get_time(&tmFin, "%d/%m/%Y");

    for (const auto& cita : citas) {
        std::tm tmCita = {};
        std::stringstream ssCita(cita.fecha);
        ssCita >> std::get_time(&tmCita, "%d/%m/%Y");

        if (std::difftime(std::mktime(&tmCita), std::mktime(&tmInicio)) >= 0 && std::difftime(std::mktime(&tmCita), std::mktime(&tmFin)) <= 0) {
            // Si la cita está dentro del rango, mostrar información
            auto paciente = std::find_if(pacientes.begin(), pacientes.end(), [cita](const Paciente& p) {
                return p.id == cita.idPaciente;
            });

            if (paciente != pacientes.end()) {
                std::cout << "Paciente: " << paciente->nombre
                          << ", Fecha: " << cita.fecha
                          << ", Médico: " << std::find_if(medicos.begin(), medicos.end(), [cita](const Medico& m) { return m.id == cita.idMedico; })->nombre
                          << "\n";
            }
        }
    }
}

void ControladorHospital::generarReporteCitasPendientesPorMedico() {
    std::cout << "\n--- Reporte de Citas Pendientes por Médico ---\n";

    std::map<int, std::vector<Cita>> citasPorMedico;
    
    // Agrupar las citas por médico
    for (const auto& cita : citas) {
        citasPorMedico[cita.idMedico].push_back(cita);
    }

    for (const auto& [idMedico, citas] : citasPorMedico) {
        auto medico = std::find_if(medicos.begin(), medicos.end(), [idMedico](const Medico& m) { return m.id == idMedico; });
        
        if (medico != medicos.end()) {
            std::cout << "Médico: " << medico->nombre << "\n";
            for (const auto& cita : citas) {
                std::cout << "  - Paciente: " << std::find_if(pacientes.begin(), pacientes.end(), [cita](const Paciente& p) { return p.id == cita.idPaciente; })->nombre
                          << ", Fecha: " << cita.fecha << "\n";
            }
        }
    }
}

void ControladorHospital::generarReporteCitasPendientesPorEspecialidad() {
    std::cout << "\n--- Reporte de Citas Pendientes por Especialidad ---\n";

    std::map<std::string, std::vector<Cita>> citasPorEspecialidad;
    
    // Agrupar las citas por especialidad
    for (const auto& cita : citas) {
        auto medico = std::find_if(medicos.begin(), medicos.end(), [cita](const Medico& m) { return m.id == cita.idMedico; });
        
        if (medico != medicos.end()) {
            citasPorEspecialidad[medico->especialidad].push_back(cita);
        }
    }

    for (const auto& [especialidad, citas] : citasPorEspecialidad) {
        std::cout << "Especialidad: " << especialidad << "\n";
        for (const auto& cita : citas) {
            std::cout << "  - Paciente: " << std::find_if(pacientes.begin(), pacientes.end(), [cita](const Paciente& p) { return p.id == cita.idPaciente; })->nombre
                      << ", Médico: " << std::find_if(medicos.begin(), medicos.end(), [cita](const Medico& m) { return m.id == cita.idMedico; })->nombre
                      << ", Fecha: " << cita.fecha << "\n";
        }
    }
}