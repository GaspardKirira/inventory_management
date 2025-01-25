cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MyProject)

# Spécifie la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 20)

# Ajouter le répertoire contenant les en-têtes de bcrypt
include_directories(${CMAKE_SOURCE_DIR}/bcrypt)

# Ajouter le répertoire contenant la bibliothèque statique libbcrypt.a
link_directories(${CMAKE_SOURCE_DIR}/bcrypt)

# Ajoute l'exécutable à générer
add_executable(prog main.cpp User.cpp)

# Ajouter les bibliothèques nécessaires
target_link_libraries(prog 
    /usr/local/lib/libgtest.a 
    /usr/local/lib/libgtest_main.a 
    pthread 
    bcrypt 
    ssl 
    crypto
)

# Ajouter des flags de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -g -fsanitize=address")

# Ajouter des flags pour le linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
