#include <iostream>
#include "MenuReportes.hpp"

void mostrarMenuReportes(ControladorHospital &controlador) {
    int opcion;
    do {
        std::cout << "\n--- Generación de Reportes ---\n";
        std::cout << "1. Listado de pacientes atendidos\n";
        std::cout << "2. Citas pendientes\n";
        std::cout << "3. Pacientes con enfermedades crónicas\n";
        std::cout << "4. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                controlador.generarReportePacientes();
                break;
            case 2:
                controlador.generarReporteCitas();
                break;
            case 3:
                controlador.generarReporteEnfermedades();
                break;
            case 4:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}
