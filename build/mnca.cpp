

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "mnca.cpp2"

#line 6 "mnca.cpp2"
class Cell;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "mnca.cpp2"
#include <raylib.h>

#include "types.h"
#include "config.h"

#line 6 "mnca.cpp2"
class Cell {
  public: vec2<float> position {0.0f, 0.0f}; 
  public: vec2<float> velocity {0.0f, 0.0f}; 

  private: cpp2::u8 color_num {0}; 
  private: cpp2::u32 cell_iter_index {0}; 

  public: explicit Cell(cpp2::in<float> new_x, cpp2::in<float> new_y, cpp2::in<Config> config);

#line 18 "mnca.cpp2"
  public: Cell(Cell const& that);
#line 18 "mnca.cpp2"
  public: auto operator=(Cell const& that) -> Cell& ;
#line 18 "mnca.cpp2"
  public: Cell(Cell&& that) noexcept;
#line 18 "mnca.cpp2"
  public: auto operator=(Cell&& that) noexcept -> Cell& ;

#line 21 "mnca.cpp2"
  public: auto update(cpp2::in<Config> config) & -> void;

#line 113 "mnca.cpp2"
  public: auto draw(cpp2::in<Config> config) const& -> void;

#line 117 "mnca.cpp2"
};

extern std::vector<Cell> cells;

extern int window_width;
extern int window_height;

extern std::optional<int> mouse_x;
extern std::optional<int> mouse_y;

[[nodiscard]] auto create_random_cell(cpp2::in<Config> config) -> Cell;

#line 133 "mnca.cpp2"
auto main() -> int;

#line 202 "mnca.cpp2"
auto print_xy(cpp2::in<Cell> cell) -> void;

//=== Cpp2 function definitions =================================================

#line 1 "mnca.cpp2"

#line 13 "mnca.cpp2"
  Cell::Cell(cpp2::in<float> new_x, cpp2::in<float> new_y, cpp2::in<Config> config)
    : position{ vec2<float>(new_x, new_y) }
    , color_num{ random_value<cpp2::u8>(cpp2::as_<cpp2::u8, 0>(), config.colors_number - 1) }{

#line 16 "mnca.cpp2"
  }

#line 18 "mnca.cpp2"
  Cell::Cell(Cell const& that)
  : position{ that.position }
  , velocity{ that.velocity }
  , color_num{ that.color_num }
  , cell_iter_index{ that.cell_iter_index }{
#line 19 "mnca.cpp2"
  }
#line 18 "mnca.cpp2"
  auto Cell::operator=(Cell const& that) -> Cell& {
  position = that.position;
  velocity = that.velocity;
  color_num = that.color_num;
  cell_iter_index = that.cell_iter_index;
  return *this;
#line 19 "mnca.cpp2"
  }
#line 18 "mnca.cpp2"
  Cell::Cell(Cell&& that) noexcept
  : position{ std::move(that).position }
  , velocity{ std::move(that).velocity }
  , color_num{ std::move(that).color_num }
  , cell_iter_index{ std::move(that).cell_iter_index }{
#line 19 "mnca.cpp2"
  }
#line 18 "mnca.cpp2"
  auto Cell::operator=(Cell&& that) noexcept -> Cell& {
  position = std::move(that).position;
  velocity = std::move(that).velocity;
  color_num = std::move(that).color_num;
  cell_iter_index = std::move(that).cell_iter_index;
  return *this;
#line 19 "mnca.cpp2"
  }

#line 21 "mnca.cpp2"
  auto Cell::update(cpp2::in<Config> config) & -> void{
    auto friction {0.8f}; 
    auto gravity {0.0f}; 

    velocity.x *= friction;
    velocity.y *= std::move(friction);
    velocity.y += std::move(gravity);

    auto vel_len {std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y)}; 
    auto const max_vel_len {1.0f}; 
    if (cpp2::cmp_greater(vel_len,max_vel_len)) {
      velocity.x *= max_vel_len / vel_len;
      velocity.y *= std::move(max_vel_len) / std::move(vel_len);
    }

    auto cell_counter {0}; for( ; cpp2::cmp_less(cell_counter,CPP2_UFCS(ssize)(cells) / 4); cell_counter += 1 ) {
      auto const other {CPP2_ASSERT_IN_BOUNDS(cells, cell_iter_index % CPP2_UFCS(size)(cells))}; 
      cell_iter_index = (cell_iter_index + 1) % CPP2_UFCS(size)(cells);

      if (&(*this) != &other) {
        auto dx {other.position.x - position.x}; 
        auto dy {other.position.y - position.y}; 

        dx = std::fmod(dx + 1.5f * window_width, window_width) - 0.5f * window_width;
        dy = std::fmod(dy + 1.5f * window_height, window_height) - 0.5f * window_height;

        auto dist {std::sqrt(dx * dx + dy * dy)}; 

        if (cpp2::cmp_less(dist,0.001f) || cpp2::cmp_greater(dist,100.0f)) {
          continue;
        }

        // might have some calculation bugs
        auto dist2 {dist * dist}; 

        auto sfx {dx / (dist2)}; 
        auto sfy {dy / (dist2)}; 

        auto const separation_max {0.8f}; 
        sfx = std::clamp(sfx, -separation_max, separation_max);
        sfy = std::clamp(sfy, -separation_max, std::move(separation_max));

        velocity.x -= std::move(sfx);
        velocity.y -= std::move(sfy);

        auto damping {0.4f}; 
        auto force {CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(config.attraction_matrix, color_num), std::move(other).color_num) / std::move(damping)}; 
        auto fx {(std::move(dx) / dist2) * force}; 
        auto fy {(std::move(dy) / std::move(dist2)) * std::move(force)}; 

        auto const force_max {0.1f}; 
        fx = std::clamp(fx, -force_max, force_max);
        fy = std::clamp(fy, -force_max, std::move(force_max));

        velocity.x += std::move(fx);
        velocity.y += std::move(fy);

      }
    }

    position.x += velocity.x;
    position.y += velocity.y;

    if (cpp2::cmp_less(position.x,0)) {
      position.x += window_width;
    }

    if (cpp2::cmp_greater(position.x,window_width)) {
      position.x -= window_width;
    }

    if (cpp2::cmp_less(position.y,0)) {
      position.y += window_height;
    }

    if (cpp2::cmp_greater(position.y,window_height)) {
      position.y -= window_height;
    }

    if (CPP2_UFCS(has_value)(mouse_x) && CPP2_UFCS(has_value)(mouse_y)) 
    {
      auto dx {CPP2_UFCS(value)(mouse_x) - position.x}; 
      auto dy {CPP2_UFCS(value)(mouse_y) - position.y}; 
      auto distance {std::sqrt(dx * dx + dy * dy)}; 
      auto force {1 / (std::move(distance) + 1)}; 
      velocity.x += std::move(dx) * force;
      velocity.y += std::move(dy) * std::move(force);

      color_num = (color_num + 1) % config.colors_number;
    }
  }

#line 113 "mnca.cpp2"
  auto Cell::draw(cpp2::in<Config> config) const& -> void{
    Color color {CPP2_ASSERT_IN_BOUNDS(config.all_colors, color_num)}; 
    DrawCircle(position.x, position.y, 2.0f, std::move(color));
  }

#line 119 "mnca.cpp2"
std::vector<Cell> cells {}; 

int window_width {800}; 
int window_height {600}; 

std::optional<int> mouse_x {}; 
std::optional<int> mouse_y {}; 

#line 127 "mnca.cpp2"
[[nodiscard]] auto create_random_cell(cpp2::in<Config> config) -> Cell{
  auto rw {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_width))}; 
  auto rh {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_height))}; 
  return Cell(cpp2::as_<float>(std::move(rw)), cpp2::as_<float>(std::move(rh)), config); 
}

#line 133 "mnca.cpp2"
auto main() -> int{
  auto window_name {"Hello, cppfront"}; 
  InitWindow(window_width, window_height, std::move(window_name));
  SetTargetFPS(170);

  auto config {Config()}; 
  auto gui {GUI()}; 

  config.attraction_matrix = CPP2_UFCS(generate_attraction_matrix)(config, config.colors_number);

  std::cout << "Hello, cppfront!\n";

  auto cell_num {200}; for( ; cpp2::cmp_greater(cell_num,0); cell_num -= 1 ) {
    CPP2_UFCS(push_back)(cells, create_random_cell(config));
  }

  cpp2::u64 frame {0}; 

  while( !(WindowShouldClose()) ) 
  {
    frame += 1;
    for ( auto& cell : cells ) 
    {
      CPP2_UFCS(update)(cell, config);

      if (frame % 100000 == 0) 
      {
        CPP2_UFCS(print_xy)(cell);
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
      CPP2_UFCS(push_back)(cells, create_random_cell(config));
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
    {
      auto cell {Cell(cpp2::unsafe_narrow<float>(GetMouseX()), cpp2::unsafe_narrow<float>(GetMouseY()), config)}; 
      CPP2_UFCS(push_back)(cells, std::move(cell));
    }

    BeginDrawing();
    //DrawRectangle(0, 0, window_width, window_height, ColorAlpha(BLACK, 0.5f));
    DrawRectangle(0, 0, window_width, window_height, BLACK);

    for ( auto const& cell : cells ) {
      CPP2_UFCS(draw)(cell, config);
    }
    CPP2_UFCS(draw)(gui, config);

    EndDrawing();
  }
}

#line 202 "mnca.cpp2"
auto print_xy(cpp2::in<Cell> cell) -> void{
  std::cout << "cell.position = " << cell.position << "\n";
}

