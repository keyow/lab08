//
// Created by keyow on 19.04.2022.
//

#include <gtest/gtest.h>

#include <fib.hpp>

TEST(Fibonacci, fib_function) {
    EXPECT_EQ(75025, fibonacci(25));
    EXPECT_EQ(0, fibonacci(0));
}

TEST(Fibonacci, less_then_zero) {
    EXPECT_THROW(fibonacci(-1), std::logic_error);
}