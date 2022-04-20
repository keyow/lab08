#include <fib.hpp>

int fibonacci(int number) {
    if (number < 0) {
        throw std::logic_error("number less then zero");
    } else if (number == 0) {
        return 0;
    } else if (number == 1) {
        return 1;
    } else {
        return fibonacci(number - 1) + fibonacci(number - 2);
    }
}