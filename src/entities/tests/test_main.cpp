// Fichier benchmark/benchmark_performance.cpp
#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>

class PerformanceTester
{
public:
    static void sortLargeVector(std::vector<int> &vec)
    {
        std::sort(vec.begin(), vec.end());
    }
};

// Benchmark pour le tri d'un grand vecteur
static void BM_SortLargeVector(benchmark::State &state)
{
    // Taille du vecteur à partir de `state.range(0)`
    int size = state.range(0);

    for (auto _ : state)
    {
        // Créer et remplir le vecteur
        std::vector<int> largeVector(size);
        std::generate(largeVector.begin(), largeVector.end(), []()
                      { return rand(); });

        // Appeler la méthode à benchmarker
        PerformanceTester::sortLargeVector(largeVector);
    }
}

// Ajouter différentes tailles de vecteurs au benchmark
BENCHMARK(BM_SortLargeVector)->Arg(1000)->Arg(1000000);

// Fonction principale pour exécuter le benchmark
BENCHMARK_MAIN();
