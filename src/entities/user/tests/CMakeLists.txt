cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MyProject)

# Spécifie la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 20)

# Recherche Google Test et Google Benchmark
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Si find_package échoue, spécifie manuellement le répertoire d'inclusion et de bibliothèque
include_directories(${GTEST_INCLUDE_DIRS} ${BENCHMARK_INCLUDE_DIRS})

# Ajoute un chemin explicite pour les bibliothèques de Google Benchmark
link_directories(/usr/local/lib)

# Ajoute l'exécutable à générer
add_executable(prog test_main.cpp)

# Lier explicitement les bibliothèques de Google Test et Google Benchmark
target_link_libraries(prog ${GTEST_LIBRARIES} /usr/local/lib/libbenchmark.a /usr/local/lib/libbenchmark_main.a pthread)

# Ajouter des flags de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -g -fsanitize=address")

# Ajouter des flags pour le linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
