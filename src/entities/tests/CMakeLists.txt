cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MyProject)

# Spécifie la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 20)

# Ajoute les répertoires contenant les fichiers d'en-tête
include_directories(/usr/local/include)

# Ajoute l'exécutable à générer
add_executable(prog test_main.cpp)

# Ajouter les bibliothèques nécessaires
target_link_libraries(prog /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a pthread)

# Ajouter des flags de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -g -fsanitize=address")

# Ajouter des flags pour le linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
