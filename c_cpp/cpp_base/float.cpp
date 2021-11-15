#include <thread>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <future>
#include <cfloat>

#include <limits>
const float kFloatToFix16Scale = 1 << 12;
const float kMaxInt16Float = float(std::numeric_limits<int16_t>::max() - 1) / kFloatToFix16Scale;

int main() {
    //test();
    //fut.get();
    int a = 165536;
    printf("%.7lf\n", kMaxInt16Float * kFloatToFix16Scale);
    return 0;
}
