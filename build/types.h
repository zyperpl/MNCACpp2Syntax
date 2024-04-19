
#ifndef BUILD_TYPES_H_CPP2
#define BUILD_TYPES_H_CPP2


//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "types.h2"

#line 3 "types.h2"
template<typename T> class vec2;
  

#line 27 "types.h2"
class TextJustification;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "types.h2"
#include <atomic>

#line 3 "types.h2"
template<typename T> class vec2 {
  public: std::atomic<T> x; 
  public: std::atomic<T> y; 

  public: explicit vec2(T const& new_x, T const& new_y);

#line 12 "types.h2"
  public: vec2(vec2 const& that);
#line 12 "types.h2"
  public: auto operator=(vec2 const& that) -> vec2& ;
#line 12 "types.h2"
  public: vec2(vec2&& that) noexcept;
#line 12 "types.h2"
  public: auto operator=(vec2&& that) noexcept -> vec2& ;

#line 19 "types.h2"
};

template<typename T>
auto operator<<(std::ostream &os, const vec2<T> &v) -> std::ostream & {
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

class TextJustification {
private: cpp2::i8 _value; private: constexpr TextJustification(cpp2::in<cpp2::i64> _val);

private: constexpr auto operator=(cpp2::in<cpp2::i64> _val) -> TextJustification& ;
public: static const TextJustification Left;
public: static const TextJustification Center;
public: static const TextJustification Right;
public: [[nodiscard]] constexpr auto get_raw_value() const& -> cpp2::i8;
public: constexpr explicit TextJustification();
public: constexpr TextJustification(TextJustification const& that);
public: constexpr auto operator=(TextJustification const& that) -> TextJustification& ;
public: constexpr TextJustification(TextJustification&& that) noexcept;
public: constexpr auto operator=(TextJustification&& that) noexcept -> TextJustification& ;
public: [[nodiscard]] auto operator<=>(TextJustification const& that) const& -> std::strong_ordering = default;
public: [[nodiscard]] auto to_string() const& -> std::string;

#line 31 "types.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "types.h2"

#line 7 "types.h2"
  template <typename T> vec2<T>::vec2(T const& new_x, T const& new_y)
    : x{ std::atomic<T>(new_x) }
    , y{ std::atomic<T>(new_y) }{

#line 10 "types.h2"
  }

#line 12 "types.h2"
  template <typename T> vec2<T>::vec2(vec2 const& that)
    : x{ std::atomic<T>() }
    , y{ std::atomic<T>() }{

#line 16 "types.h2"
    CPP2_UFCS(store)((*this).x, CPP2_UFCS(load)(that.x));
    CPP2_UFCS(store)((*this).y, CPP2_UFCS(load)(that.y));
  }
#line 12 "types.h2"
  template <typename T> auto vec2<T>::operator=(vec2 const& that) -> vec2& {
    x = std::atomic<T>();
    y = std::atomic<T>();

#line 16 "types.h2"
    CPP2_UFCS(store)((*this).x, CPP2_UFCS(load)(that.x));
    CPP2_UFCS(store)((*this).y, CPP2_UFCS(load)(that.y));
    return *this;
#line 18 "types.h2"
  }
#line 12 "types.h2"
  template <typename T> vec2<T>::vec2(vec2&& that) noexcept
    : x{ std::atomic<T>() }
    , y{ std::atomic<T>() }{

#line 16 "types.h2"
    CPP2_UFCS(store)((*this).x, CPP2_UFCS(load)(std::move(that).x));
    CPP2_UFCS(store)((*this).y, CPP2_UFCS(load)(std::move(that).y));
  }
#line 12 "types.h2"
  template <typename T> auto vec2<T>::operator=(vec2&& that) noexcept -> vec2& {
    x = std::atomic<T>();
    y = std::atomic<T>();

#line 16 "types.h2"
    CPP2_UFCS(store)((*this).x, CPP2_UFCS(load)(std::move(that).x));
    CPP2_UFCS(store)((*this).y, CPP2_UFCS(load)(std::move(that).y));
    return *this;
#line 18 "types.h2"
  }


  constexpr TextJustification::TextJustification(cpp2::in<cpp2::i64> _val)
                                                          : _value{ cpp2::unsafe_narrow<cpp2::i8>(_val) } {  }

constexpr auto TextJustification::operator=(cpp2::in<cpp2::i64> _val) -> TextJustification&  { 
                                                          _value = cpp2::unsafe_narrow<cpp2::i8>(_val);
                                                          return *this; }
inline CPP2_CONSTEXPR TextJustification TextJustification::Left = 0;

inline CPP2_CONSTEXPR TextJustification TextJustification::Center = 1;

inline CPP2_CONSTEXPR TextJustification TextJustification::Right = 2;

[[nodiscard]] constexpr auto TextJustification::get_raw_value() const& -> cpp2::i8 { return _value; }
constexpr TextJustification::TextJustification()
                                        : _value{ Left._value }{}
constexpr TextJustification::TextJustification(TextJustification const& that)
                                              : _value{ that._value }{}
constexpr auto TextJustification::operator=(TextJustification const& that) -> TextJustification& {
                                              _value = that._value;
                                              return *this;}
constexpr TextJustification::TextJustification(TextJustification&& that) noexcept
                                              : _value{ std::move(that)._value }{}
constexpr auto TextJustification::operator=(TextJustification&& that) noexcept -> TextJustification& {
                                              _value = std::move(that)._value;
                                              return *this;}
[[nodiscard]] auto TextJustification::to_string() const& -> std::string{
  if ((*this) == Left) {return "Left"; }
  if ((*this) == Center) {return "Center"; }
  if ((*this) == Right) {return "Right"; }
  return "invalid TextJustification value"; 
  }
#endif
