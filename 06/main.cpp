#include <iostream>
#include "format.hpp"
#include <stdexcept>

void Test_1()
{
    try {
        auto text_1 = format("{1}+{1} = {0}", 2, "one");
        assert(text_1 == "one+one = 2");
        auto text_2 = format("{0}{0}", "rock");
        assert(text_2 == "rockrock");
        auto text_3 = format("{2} {1} {0}", "breathtaking", "are", "you");
        assert(text_3 == "you are breathtaking");
    }
    catch (...) {
        std::cout << "problem, test_1\n";
    }
}
void Test_2()
{
    try {
        auto text_1 = format("{0 + {0 = 4", 2);
    }
    catch (const std::runtime_error& exception) {
    }
    catch (...) {
        std::cout << "problem, test_2\n";
    }
    try {
        auto text_1 = format("{} here", 2);
    }
    catch (const std::runtime_error& exception) {
    }
    catch (...) {
        std::cout << "problem, test_2\n";
    }
}
void Test_3()
{
    try {
        auto text_1 = format("{0}{1}{3}", 1, 2);
    }
    catch (const std::runtime_error& exception) {
    }
    catch (...) {
        std::cout << "problem, test_3\n";
    }
}
void Test_4()
{
    try {
        auto text_1 = format("{0}{1}", 1, 2, 3, 4);
    }
    catch (const std::runtime_error& exception) {
    }
    catch (...) {
        std::cout << "problem, test_4\n";
    }
}

int main()
{
    Test_1();
    Test_2();
    Test_3();
    Test_4();
    std::cout << "Everything is ok\n";
    return 0;
}