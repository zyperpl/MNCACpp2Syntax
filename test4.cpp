

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "test4.cpp2"
class my_class;
#line 2 "test4.cpp2"
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "test4.cpp2"
class my_class {
#line 2 "test4.cpp2"
    private: int x; 

#line 5 "test4.cpp2"
        public: explicit my_class(cpp2::in<int> initial_x);
#line 5 "test4.cpp2"
        public: auto operator=(cpp2::in<int> initial_x) -> my_class& ;

#line 9 "test4.cpp2"
        // Member function to set 'x'
        public: auto set_x(cpp2::in<int> new_x) & -> void;

#line 14 "test4.cpp2"
        // Member function to get 'x'
        public: [[nodiscard]] auto get_x() const& -> int;

#line 19 "test4.cpp2"
        // Member function to increment 'x'
        public: auto increment_x() & -> void;
    public: my_class(my_class const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(my_class const&) -> void = delete;


#line 23 "test4.cpp2"
};

auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "test4.cpp2"

#line 5 "test4.cpp2"
        my_class::my_class(cpp2::in<int> initial_x)
            : x{ initial_x }{

#line 7 "test4.cpp2"
        }
#line 5 "test4.cpp2"
        auto my_class::operator=(cpp2::in<int> initial_x) -> my_class& {
            x = initial_x;
            return *this;

#line 7 "test4.cpp2"
        }

#line 10 "test4.cpp2"
        auto my_class::set_x(cpp2::in<int> new_x) & -> void{
            (*this).x = new_x;
        }

#line 15 "test4.cpp2"
        [[nodiscard]] auto my_class::get_x() const& -> int{
            return (*this).x; 
        }

#line 20 "test4.cpp2"
        auto my_class::increment_x() & -> void{
            (*this).x += 1;
        }

#line 25 "test4.cpp2"
auto main() -> int{
    my_class obj {10}; 

    CPP2_UFCS(set_x)(obj, 20);
    std::cout << "x is: " << CPP2_UFCS(get_x)(obj) << "\n";

    CPP2_UFCS(increment_x)(obj);
    std::cout << "x is now: " << CPP2_UFCS(get_x)(std::move(obj)) << "\n";
}

