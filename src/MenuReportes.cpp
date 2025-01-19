#include <iostream>
#include "MenuReportes.hpp"

void mostrarMenuReportes(ControladorHospital &controlador) {
    int opcion;
    do {
        std::cout << "\n--- Generación de Reportes ---\n";
        std::cout << "1. Listado de pacientes atendidos\n";
        std::cout << "2. Citas pendientes por médico\n";
        std::cout << "3. Citas pendientes por especialidad\n";
        std::cout << "4. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string fechaInicio, fechaFin;
                std::cout << "Ingrese fecha de inicio (DD/MM/AAAA): ";
                std::cin >> fechaInicio;
                std::cout << "Ingrese fecha de fin (DD/MM/AAAA): ";
                std::cin >> fechaFin;
                controlador.generarReportePacientesAtendidos(fechaInicio, fechaFin);
                break;
            }
            case 2:
                controlador.generarReporteCitasPendientesPorMedico();
                break;
            case 3:
                controlador.generarReporteCitasPendientesPorEspecialidad();
                break;
            case 4:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}
