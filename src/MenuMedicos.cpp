#include <iostream>
#include "MenuMedicos.hpp"

void mostrarMenuMedicos(ControladorHospital &controlador) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Médicos ---\n";
        std::cout << "1. Alta de médico\n";
        std::cout << "2. Baja de médico\n";
        std::cout << "3. Asignar especialidad\n";
        std::cout << "4. Listar médicos\n";
        std::cout << "5. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                controlador.altaMedico();
                break;
            case 2:
                controlador.bajaMedico();
                break;
            case 3:
                controlador.asignarEspecialidad();
                break;
            case 4:
                controlador.listarMedicos();
                break;
            case 5:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}
