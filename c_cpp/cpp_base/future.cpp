#include <future>
#include <stdexcept>
#include <chrono>
#include <thread>

int test_throw() {
    throw std::logic_error("test throw");
    printf("test throw\n");
    return 0;
}

int main() {
    std::future<int> fut = std::async(std::launch::async, test_throw);
    //std::future<int> fut;
    try {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        printf("future is valid: %s\n", std::to_string(fut.valid()).c_str());
        //int a = fut.get();
        fut.wait();
        printf("fut wait\n");
    } catch(std::exception& e) {
        printf("caught an exception%s\n", e.what());
    }
    printf("end\n");
    
    return 0;
}
