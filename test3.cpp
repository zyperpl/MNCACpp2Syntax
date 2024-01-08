

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "test3.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "test3.cpp2"
[[nodiscard]] auto add(cpp2::in<int> a, cpp2::in<int> b) -> int;

#line 5 "test3.cpp2"
[[nodiscard]] auto subtract(cpp2::in<int> a, cpp2::in<int> b) -> int;

#line 9 "test3.cpp2"
[[nodiscard]] auto multiply(cpp2::in<int> a, cpp2::in<int> b) -> int;

#line 13 "test3.cpp2"
[[nodiscard]] auto divide(cpp2::in<int> a, cpp2::in<int> b) -> int;

#line 18 "test3.cpp2"
// Main function to demonstrate the usage of the calculator

auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "test3.cpp2"
[[nodiscard]] auto add(cpp2::in<int> a, cpp2::in<int> b) -> int{
#line 2 "test3.cpp2"
    return a + b; 
}

[[nodiscard]] auto subtract(cpp2::in<int> a, cpp2::in<int> b) -> int{
    return a - b; 
}

[[nodiscard]] auto multiply(cpp2::in<int> a, cpp2::in<int> b) -> int{
    return a * b; 
}

[[nodiscard]] auto divide(cpp2::in<int> a, cpp2::in<int> b) -> int{
    // Simple division, without handling division by zero
    return a / b; 
}

#line 20 "test3.cpp2"
auto main() -> int{
    auto result1 {add(5, 3)};    // Expected: 8
    auto result2 {subtract(5, 3)}; // Expected: 2
    auto result3 {multiply(5, 3)}; // Expected: 15
    auto result4 {divide(6, 2)}; // Expected: 3

    // Print the results
    std::cout << "5 + 3 = " << std::move(result1) << "\n";
    std::cout << "5 - 3 = " << std::move(result2) << "\n";
    std::cout << "5 * 3 = " << std::move(result3) << "\n";
    std::cout << "6 / 2 = " << std::move(result4) << "\n";
}

