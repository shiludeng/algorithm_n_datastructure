#include <thread>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <future>

int main() {
    int n  = 100;
    std::vector<std::future<void>> futs;
    for (int i = 0; i<n; ++i) {
        futs.push_back(std::async(std::launch::async, [i](){printf("%d\n", i);}));
    }
    for (int i = 0; i<n; ++i) {
        futs[i].wait();
    }

    return 0;
}
