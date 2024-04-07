cmake_minimum_required(VERSION 3.22)
project(MyProject)

# Agrega todos los archivos fuente al proyecto
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/main/*.cpp" "src/background/*.cpp" "src/enemies/*.cpp" "src/entity/*.cpp" "src/states/*.cpp")

# Indica que queremos compilar un ejecutable llamado "ejecutable"
add_executable(ejecutable ${SOURCES})

# Enlaza las bibliotecas SDL2, SDL2_image, SDL2_mixer y SDL2_ttf
target_link_libraries(ejecutable SDL2 SDL2_image SDL2_mixer SDL2_ttf)
