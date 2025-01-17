#ifndef CONTROLADORHOSPITAL_HPP
#define CONTROLADORHOSPITAL_HPP

#include <iostream>
#include <vector>
#include <string>

// Clase para representar un médico.
struct Medico {
    int id;
    std::string nombre;
    std::string especialidad;

    Medico(int id, const std::string &nombre) : id(id), nombre(nombre), especialidad("Sin asignar") {}
};

// Clase para representar un paciente.
struct Paciente {
    int id;
    std::string nombre;
    std::string enfermedad;

    Paciente(int id, const std::string &nombre, const std::string &enfermedad)
        : id(id), nombre(nombre), enfermedad(enfermedad) {}
};
// Clase para representar una cita médica
struct Cita {
    int idPaciente;
    int idMedico;
    std::string fecha;

    Cita(int idPaciente, int idMedico, const std::string &fecha)
        : idPaciente(idPaciente), idMedico(idMedico), fecha(fecha) {}
};

// Clase con la que manejo las operaciones del hospital.
class ControladorHospital {
private:
    std::vector<Medico> medicos;
    std::vector<Paciente> pacientes;
    std::vector<Cita> citas;

public:
    // Gestión de médicos.
    void altaMedico();
    void bajaMedico();
    void asignarEspecialidad();
    void listarMedicos();

    // Gestión de pacientes.
    void altaPaciente();
    void bajaPaciente();
    void modificarPaciente();
    void buscarPaciente();

    // Gestión de citas.
    void asignarCita();
    void cancelarCita();
    void modificarCita();
    void listarCitas();

    // Generando los reportes.
    void generarReportePacientes();
    void generarReporteCitas();
    void generarReporteEnfermedades();

    // Guardar datos.
    void guardarDatos();
    void leerDatos();
};

#endif // CONTROLADORHOSPITAL_HPP
