#include <iostream>
#include "MenuPacientes.hpp"

void mostrarMenuPacientes(ControladorHospital &controlador) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Pacientes ---\n";
        std::cout << "1. Alta de paciente\n";
        std::cout << "2. Baja de paciente\n";
        std::cout << "3. Modificar datos del paciente\n";
        std::cout << "4. Buscar paciente\n";
        std::cout << "5. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                controlador.altaPaciente();
                break;
            case 2:
                controlador.bajaPaciente();
                break;
            case 3:
                controlador.modificarPaciente();
                break;
            case 4:
                controlador.buscarPaciente();
                break;
            case 5:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}
