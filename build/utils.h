
#ifndef BUILD_UTILS_H_CPP2
#define BUILD_UTILS_H_CPP2


//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "src/utils.h2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "src/utils.h2"
#include <raylib.h>

#line 3 "src/utils.h2"
template<typename T> [[nodiscard]] auto random_value(T const& min, T const& max) -> T;

#line 6 "src/utils.h2"
template<typename T> [[nodiscard]] auto random_value(cpp2::in<float> min, cpp2::in<float> max) -> float;

//=== Cpp2 function definitions =================================================

#line 1 "src/utils.h2"

#line 3 "src/utils.h2"
template<typename T> [[nodiscard]] auto random_value(T const& min, T const& max) -> T { 
  return cpp2::unsafe_narrow<T>(GetRandomValue(cpp2::unsafe_narrow<int>(min), cpp2::unsafe_narrow<int>(max)));  }

#line 6 "src/utils.h2"
template<typename T> [[nodiscard]] auto random_value(cpp2::in<float> min, cpp2::in<float> max) -> float { 
  return min + (GetRandomValue(0, 10000) / 10000.0f) * (max - min);  }
#endif

