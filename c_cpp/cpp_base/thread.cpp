#include <thread>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <future>

class A {
public:
    A() {
    }

    A(const A& a) {
        printf("A copy constructor\n");
    }

    ~A() {
        printf("A destructor\n");
    }
public:
    std::vector<std::string> test_strs;
};

class B {
public:
    A a;

    int c;

    B(int c) : c(c) {
    }

    B() : B(10) {
    }

    B(const B& b) {
        printf("B copy constructor\n");
    }
    ~B() {
        printf("B destructor\n");
    }
};

struct C {
    int a = 0;
};

int test_lambda_expression(const A& a) {
    for (const auto& str : a.test_strs) {
        printf("str %s\n", str.c_str());
    }
    printf("test_lambda_expression start\n");
    return 0;
}


std::future<int> fut;
void test() {
    B b;
    printf("b.c = %d\n", b.c);
    b.a.test_strs = {"a", "b", "c"};
    auto func = [=]() {
                std::this_thread::sleep_for (std::chrono::seconds(5));
                return test_lambda_expression(b.a);
            };

    printf("after create lambda expression\n");

    fut = std::async(std::launch::async, [=]() {
                printf("start new thread\n");
                std::this_thread::sleep_for (std::chrono::seconds(5));
                return test_lambda_expression(b.a);
            });
    printf("test end\n");
}

int main() {
    test();
    fut.get();


    printf("end\n");
    return 0;
}
