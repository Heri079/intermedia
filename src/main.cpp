#include <iostream>
#include "MenuPacientes.hpp"
#include "MenuMedicos.hpp"
#include "MenuCitas.hpp"
#include "MenuReportes.hpp"
#include "ControladorHospital.hpp"

void mostrarMenuPrincipal() {
    std::cout << "\n=================== MENU PRINCIPAL ===================\n";
    std::cout << "1. Gestión de Pacientes\n";
    std::cout << "2. Gestión de Médicos\n";
    std::cout << "3. Gestión de Citas Médicas\n";
    std::cout << "4. Generar Reportes\n";
    std::cout << "5. Guardar y Salir\n";
    std::cout << "=====================================================\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    ControladorHospital controlador; // Para centralizar la lógica del sistema.
    int opcion;

    do {
        mostrarMenuPrincipal();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMenuPacientes(controlador);
                break;
            case 2:
                mostrarMenuMedicos(controlador);
                break;
            case 3:
                mostrarMenuCitas(controlador);
                break;
            case 4:
                mostrarMenuReportes(controlador);
                break;
            case 5:
                std::cout << "Guardando datos y saliendo...\n";
                controlador.guardarDatos(); // Guardar los datos en archivos.
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}

