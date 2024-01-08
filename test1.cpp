

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "test1.cpp2"

#line 16 "test1.cpp2"
class Ball;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "test1.cpp2"
#include <raylib.h>

template<typename T>
T random_value(const T &min, const T &max)
{
  return cpp2::unsafe_narrow<T>(GetRandomValue(cpp2::unsafe_narrow<int>(min), cpp2::unsafe_narrow<int>(max)));
}

Color random_color()
{
  return Color { random_value<unsigned char>(0, 255), 
                 random_value<unsigned char>(0, 255), 
                 random_value<unsigned char>(0, 255), 255 };
}

#line 16 "test1.cpp2"
class Ball {
  public: float x; 
  public: float y; 

  private: float vx {0.0f}; 
  private: float vy {0.0f}; 
  private: Color color {random_color()}; 

  public: explicit Ball(cpp2::in<float> new_x, cpp2::in<float> new_y);

#line 29 "test1.cpp2"
  public: Ball(Ball const& that);
#line 29 "test1.cpp2"
  public: auto operator=(Ball const& that) -> Ball& ;
#line 29 "test1.cpp2"
  public: Ball(Ball&& that) noexcept;
#line 29 "test1.cpp2"
  public: auto operator=(Ball&& that) noexcept -> Ball& ;

#line 32 "test1.cpp2"
  public: auto update() & -> void;

#line 71 "test1.cpp2"
  public: auto draw() const& -> void;

#line 74 "test1.cpp2"
};

extern std::vector<Ball> balls;

auto draw_scene() -> void;

#line 85 "test1.cpp2"
extern int window_width;
extern int window_height;

extern std::optional<int> mouse_x;
extern std::optional<int> mouse_y;

[[nodiscard]] auto create_random_ball() -> Ball;

#line 97 "test1.cpp2"
auto main() -> int;

#line 161 "test1.cpp2"
auto print_xy(cpp2::in<Ball> ball) -> void;

//=== Cpp2 function definitions =================================================

#line 1 "test1.cpp2"

#line 24 "test1.cpp2"
  Ball::Ball(cpp2::in<float> new_x, cpp2::in<float> new_y)
    : x{ new_x }
    , y{ new_y }{

#line 27 "test1.cpp2"
  }

  Ball::Ball(Ball const& that)
  : x{ that.x }
  , y{ that.y }
  , vx{ that.vx }
  , vy{ that.vy }
  , color{ that.color }{
#line 30 "test1.cpp2"
  }
#line 29 "test1.cpp2"
  auto Ball::operator=(Ball const& that) -> Ball& {
  x = that.x;
  y = that.y;
  vx = that.vx;
  vy = that.vy;
  color = that.color;
  return *this;
#line 30 "test1.cpp2"
  }
#line 29 "test1.cpp2"
  Ball::Ball(Ball&& that) noexcept
  : x{ std::move(that).x }
  , y{ std::move(that).y }
  , vx{ std::move(that).vx }
  , vy{ std::move(that).vy }
  , color{ std::move(that).color }{
#line 30 "test1.cpp2"
  }
#line 29 "test1.cpp2"
  auto Ball::operator=(Ball&& that) noexcept -> Ball& {
  x = std::move(that).x;
  y = std::move(that).y;
  vx = std::move(that).vx;
  vy = std::move(that).vy;
  color = std::move(that).color;
  return *this;
#line 30 "test1.cpp2"
  }

  auto Ball::update() & -> void{
    auto r {random_value<float>(0.0f, 100.0f) / 100.0f}; 

    (*this).vx *= 0.991f;
    (*this).vy *= 0.991f;
    (*this).vy += 0.08f;

    (*this).x += vx;
    (*this).y += vy;

    if (cpp2::cmp_less((*this).x,0) || cpp2::cmp_greater((*this).x,window_width)) 
    {
      (*this).vx *= -0.9f;
      (*this).vy += -0.5f + r;

      (*this).x = std::clamp((*this).x, 0.0f, cpp2::unsafe_narrow<float>(window_width)) + vx * 2.0f;
    }

    if (cpp2::cmp_less((*this).y,0) || cpp2::cmp_greater((*this).y,window_height)) 
    {
      (*this).vy *= -0.9f;
      (*this).vx += -0.5f + r;

      (*this).y = std::clamp((*this).y, 0.0f, cpp2::unsafe_narrow<float>(window_height)) + vy * 2.0f;
    }

    if (CPP2_UFCS(has_value)(mouse_x) && CPP2_UFCS(has_value)(mouse_y)) 
    {
      auto dx {CPP2_UFCS(value)(mouse_x) - (*this).x}; 
      auto dy {CPP2_UFCS(value)(mouse_y) - (*this).y}; 
      auto distance {std::sqrt(dx * dx + dy * dy)}; 
      auto force {1 / (std::move(distance) + 1) * std::move(r)}; 
      (*this).vx += std::move(dx) * force;
      (*this).vy += std::move(dy) * std::move(force);

      color = random_color();
    }
  }

  auto Ball::draw() const& -> void{
    DrawCircle(x, y, 2.0f, color);
  }

#line 76 "test1.cpp2"
std::vector<Ball> balls {}; 

auto draw_scene() -> void
{
  for ( auto const& ball : balls ) {
    CPP2_UFCS(draw)(ball);
  }
}

int window_width {800}; 
int window_height {600}; 

std::optional<int> mouse_x {}; 
std::optional<int> mouse_y {}; 

[[nodiscard]] auto create_random_ball() -> Ball{
  auto rw {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_width))}; 
  auto rh {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_height))}; 
  return Ball(cpp2::as_<float>(std::move(rw)), cpp2::as_<float>(std::move(rh))); 
}

auto main() -> int{
  auto window_name {"Hello CppFront"}; 
  InitWindow(window_width, window_height, std::move(window_name));
  SetTargetFPS(170);

  std::cout << "Hello World\n";

  auto counter {100}; 
  while( cpp2::cmp_greater(counter,0) ) 
  {
    CPP2_UFCS(push_back)(balls, create_random_ball());
    counter -= 1;
  }

  uint64_t frame {0}; 

  while( !(WindowShouldClose()) ) 
  {
    frame += 1;
    for ( auto& ball : balls ) 
    {
      CPP2_UFCS(update)(ball);

      if (frame % 1000 == 0) 
      {
        CPP2_UFCS(print_xy)(ball);
      }
    }

    window_width = GetRenderWidth();
    window_height = GetRenderHeight();

    if (!(IsMouseButtonDown(MOUSE_BUTTON_LEFT))) 
    {
      CPP2_UFCS(reset)(mouse_x);
      CPP2_UFCS(reset)(mouse_y);
    }
    else 
    {
      mouse_x = GetMouseX();
      mouse_y = GetMouseY();
    }

    if (IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE)) 
    {
      CPP2_UFCS(push_back)(balls, create_random_ball());
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
    {
      auto ball {Ball(cpp2::unsafe_narrow<float>(GetMouseX()), cpp2::unsafe_narrow<float>(GetMouseY()))}; 
      CPP2_UFCS(push_back)(balls, ball);
    }

    BeginDrawing();
    ClearBackground(BLACK);

    draw_scene();

    DrawFPS(1, 1);
    EndDrawing();
  }
}

auto print_xy(cpp2::in<Ball> ball) -> void{
  std::cout << "ball.x = " << ball.x << ", ball.y = " << ball.y << "\n";
}

