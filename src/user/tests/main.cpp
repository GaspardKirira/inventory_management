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