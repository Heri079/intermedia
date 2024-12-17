#include <iostream>
#include "MenuCitas.hpp"

void mostrarMenuCitas(ControladorHospital &controlador) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Citas Médicas ---\n";
        std::cout << "1. Asignar cita\n";
        std::cout << "2. Cancelar cita\n";
        std::cout << "3. Modificar cita\n";
        std::cout << "4. Listar citas\n";
        std::cout << "5. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                controlador.asignarCita();
                break;
            case 2:
                controlador.cancelarCita();
                break;
            case 3:
                controlador.modificarCita();
                break;
            case 4:
                controlador.listarCitas();
                break;
            case 5:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}
