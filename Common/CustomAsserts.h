#pragma once

#include <iostream>
#include <sstream>

namespace test {

template <typename T1, typename T2>
void assertEqual(const T1& value,
                 const T2& expectedValue,
                 int line,
                 char const* file) {
    if (value == expectedValue) {
        return;
    }
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cerr << file << ':' << line << ": Assertion failed:\n";
    std::cerr << "The expected value was " << expectedValue << ", but got "
              << value << " instead.\n";
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::exit(1);
}

template <typename T1, typename T2>
void assertFloatEqual(const T1& actual,
                      const T2& expected,
                      int line,
                      char const* file) {
    static constexpr auto c_precision = 0.00001;
    if (std::abs(actual - expected) < c_precision) {
        return;
    }
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cerr << file << ':' << line << ": Assertion failed:\n";
    std::cerr << "The expected value was " << expected << ", but got " << actual
              << " instead.\n";
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::exit(1);
}

template <typename T1, typename T2>
void assertGreater(const T1& actual,
                   const T2& expected,
                   int line,
                   char const* file) {
    if (actual > expected) {
        return;
    }
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cerr << file << ':' << line << ": Assertion failed:\n";
    std::cerr << "The value was expected to be greater than " << expected
              << ", but was " << actual << " instead.\n";
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::exit(1);
}

template <typename T1, typename T2>
void assertLess(const T1& actual,
                const T2& expected,
                int line,
                char const* file) {
    if (actual < expected) {
        return;
    }
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cerr << file << ':' << line << ": Assertion failed:\n";
    std::cerr << "The value was expected to be less than " << expected
              << ", but was " << actual << " instead.\n";
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::exit(1);
}

template <typename T>
void assertLexicallyEqual(const T& actual,
                          const std::string_view& expected,
                          int line,
                          char const* file) {
    std::stringstream ss;
    ss << actual;
    assertEqual(ss.str(), expected, line, file);
}

void assertBool(bool condition, int line, char const* file) {
    if (condition) {
        return;
    }
    std::cerr << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cerr << file << ':' << line << ": Assertion failed:\n";
    std::cerr << "The condition was expected to be true, but was false "
                 "instead.\n";
    std::cerr << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::exit(1);
}

}  // namespace test
