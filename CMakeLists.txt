cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(HospitalSimulator)

# Establecer el estándar de C++, no uso los de otro estandar porque es demasiado para este proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Especificar el directorio de los archivos fuente
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Buscar automáticamente todos los archivos .cpp y .hpp en el directorio src
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${SOURCE_DIR}/*.hpp)

# Incluir el directorio de encabezados para el compilador
include_directories(${SOURCE_DIR})


# se crea el ejecutable PARA ESO HAY QUE COMPILARLO
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


