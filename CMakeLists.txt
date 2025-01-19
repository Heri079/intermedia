cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(HospitalSimulator)

# Establecer el estándar de C++, no uso los de otro estándar porque es demasiado para este proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Especificar el directorio de los archivos fuente
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Buscar automáticamente todos los archivos .cpp y .hpp en el directorio src
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${SOURCE_DIR}/*.hpp)

# Incluir el directorio de encabezados para el compilador
include_directories(${SOURCE_DIR})

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Archivos CSV que se deben copiar al mismo directorio que el binario final
set(CSV_FILES ${CMAKE_SOURCE_DIR}/medicos.csv ${CMAKE_SOURCE_DIR}/pacientes.csv ${CMAKE_SOURCE_DIR}/citas.csv ${CMAKE_SOURCE_DIR}/reportes.csv)

# Copiar los archivos CSV al directorio de salida
foreach(CSV_FILE ${CSV_FILES})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CSV_FILE} $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copiando ${CSV_FILE} al directorio binario"
    )
endforeach()
