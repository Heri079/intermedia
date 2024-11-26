#include "main.hpp"

void mostrarMenu() {
    std::cout << "=====================" << std::endl;
    std::cout << " Simulador Hospital " << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "1. Gestión de pacientes" << std::endl;
    std::cout << "2. Gestión de médicos" << std::endl;
    std::cout << "3. Gestión de citas médicas" << std::endl;
    std::cout << "4. Generar reportes" << std::endl;
    std::cout << "5. Guardar datos y salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void ejecutarOpcion(Hospital& hospital, int opcion) {
    switch (opcion) {
        case 1:
            hospital.gestionPacientes();
            break;
        case 2:
            hospital.gestionMedicos();
            break;
        case 3:
            hospital.gestionCitas();
            break;
        case 4:
            hospital.generarReportes();
            break;
        case 5:
            hospital.guardarDatos();
            std::cout << "Datos guardados correctamente. Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente de nuevo." << std::endl;
    }
}

int main() {
    Hospital hospital; // Instancia de la clase principal que gestiona el sistema
    hospital.cargarDatos(); // Carga inicial de datos desde los archivos

    int opcion = 0;
    while (opcion != 5) {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada
        ejecutarOpcion(hospital, opcion);
        std::cout << std::endl;
    }

    return 0;
}
