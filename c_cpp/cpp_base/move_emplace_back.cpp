#include <iostream>
#include <vector>

class TestMoveConstructor {
public:
    TestMoveConstructor() {
        std::cout << "default constructor \n";
    }

    explicit TestMoveConstructor(int i) {
        std::cout << "another constructor\n";
    }

    TestMoveConstructor(const TestMoveConstructor&) {
        std::cout << "copy constructor\n";
    }

    TestMoveConstructor(const TestMoveConstructor&&) {
        std::cout << "move constructor\n";
    }
};

int main() {
    std::vector<TestMoveConstructor> test_vec;
    // avoid re-allocating
    test_vec.reserve(10);

    TestMoveConstructor test;
    // move constructor
    test_vec.push_back(std::move(test));

    // move constructor
    test_vec.push_back(TestMoveConstructor());

    std::cout << "\ntest emplace back:\n";
    // default & move constructor
    test_vec.emplace_back(TestMoveConstructor());
    
    // only another constructor
    test_vec.emplace_back(1);
    return 0;
}
