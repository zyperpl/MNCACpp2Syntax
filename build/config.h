
#ifndef BUILD_CONFIG_H_CPP2
#define BUILD_CONFIG_H_CPP2


//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "config.h2"

#line 5 "config.h2"
class Config;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "config.h2"
#include "utils.h"

#line 3 "config.h2"
extern bool const RANDOM_ATTRACTION;

class Config {
  public: std::vector<Color> const all_colors {RED, LIME, YELLOW, MAGENTA, SKYBLUE, PINK, WHITE, VIOLET, GOLD, ORANGE, LIGHTGRAY}; 
  public: cpp2::u8 const colors_number {5}; 
  public: std::vector<std::vector<float>> attraction_matrix; 

  public: [[nodiscard]] static auto generate_attraction_matrix(cpp2::in<int> num) -> std::vector<std::vector<float>>;

#line 43 "config.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "config.h2"

#line 3 "config.h2"
bool const RANDOM_ATTRACTION {true}; 

#line 10 "config.h2"
  [[nodiscard]] auto Config::generate_attraction_matrix(cpp2::in<int> num) -> std::vector<std::vector<float>>{
    auto matrix {std::vector<std::vector<float>>(num, std::vector<float>(num, 0.0f))}; 

    if constexpr (RANDOM_ATTRACTION) {
      auto i {0}; for( ; cpp2::cmp_less(i,num); ++i ) 
      {
        auto j {0}; for( ; cpp2::cmp_less(j,num); ++j ) 
        {
          auto val {random_value<float>(-1.0f, 1.0f)}; 

          if (i == j) {
          //  val = 1.0f; // TODO: add as parameter
          }

          CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(matrix, i), j) = std::move(val);
          std::cout << CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(matrix, i), j) << " ";
        }
        std::cout << "\n";
      }
    }else {
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 0), 0) = -0.2f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 0), 1) = +0.1f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 0), 2) = -0.0f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 1), 0) = -0.5f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 1), 1) = -1.0f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 1), 2) = +1.0f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 2), 0) = +1.0f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 2), 1) = +0.5f;
      CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS_LITERAL(matrix, 2), 2) = -0.2f;
    }

    return matrix; 
  }
#endif

