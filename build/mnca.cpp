

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "mnca.cpp2"

#line 10 "mnca.cpp2"
class Cell;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "mnca.cpp2"
#include <raylib.h>

#include <thread>
#include <mutex>
#include <shared_mutex>

#include "types.h"
#include "config.h"

#line 10 "mnca.cpp2"
class Cell {
  public: vec2<float> position {0.0f, 0.0f}; 
  public: vec2<float> velocity {0.0f, 0.0f}; 

  private: cpp2::u8 color_num {0}; 
  private: cpp2::u32 cell_iter_index {0}; 

  public: explicit Cell(auto&& other);
#line 17 "mnca.cpp2"
  public: auto operator=(auto&& other) -> Cell& ;

#line 24 "mnca.cpp2"
  public: explicit Cell(cpp2::in<float> new_x, cpp2::in<float> new_y, cpp2::in<Config> config);

#line 29 "mnca.cpp2"
  public: auto update(cpp2::in<Config> config) & -> void;

#line 121 "mnca.cpp2"
  public: auto draw(cpp2::in<Config> config) const& -> void;
  public: Cell(Cell const&) = delete; /* No 'that' constructor, suppress copy */
  public: auto operator=(Cell const&) -> void = delete;


#line 125 "mnca.cpp2"
};

extern std::vector<Cell> cells;

extern int window_width;
extern int window_height;

extern std::atomic<bool> running;

[[nodiscard]] auto create_random_cell(cpp2::in<Config> config) -> Cell;

#line 140 "mnca.cpp2"
auto update_cells(cpp2::in<ssize_t> from, cpp2::in<ssize_t> to, cpp2::in<Config> config) -> void;

#line 151 "mnca.cpp2"
std::string_view const inline constexpr window_name = "Hello, cppfront!";
cpp2::u64 const inline constexpr max_cells = 65536;

auto main() -> int;

#line 267 "mnca.cpp2"
auto print_xy(cpp2::in<Cell> cell) -> void;

//=== Cpp2 function definitions =================================================

#line 1 "mnca.cpp2"

#line 17 "mnca.cpp2"
  Cell::Cell(auto&& other)
    : position{ other.position }
    , velocity{ other.velocity }
    , color_num{ other.color_num }
    , cell_iter_index{ std::move(other).cell_iter_index }{

#line 22 "mnca.cpp2"
  }
#line 17 "mnca.cpp2"
  auto Cell::operator=(auto&& other) -> Cell& {
    position = other.position;
    velocity = other.velocity;
    color_num = other.color_num;
    cell_iter_index = std::move(other).cell_iter_index;
    return *this;

#line 22 "mnca.cpp2"
  }

#line 24 "mnca.cpp2"
  Cell::Cell(cpp2::in<float> new_x, cpp2::in<float> new_y, cpp2::in<Config> config)
    : position{ vec2<float>(new_x, new_y) }
    , color_num{ random_value<cpp2::u8>(cpp2::as_<cpp2::u8, 0>(), config.colors_number - 1) }{

#line 27 "mnca.cpp2"
  }

#line 29 "mnca.cpp2"
  auto Cell::update(cpp2::in<Config> config) & -> void{
    auto friction {0.8f}; 
    auto gravity {0.0f}; 

    auto vx {CPP2_UFCS(load)(velocity.x)}; 
    auto vy {CPP2_UFCS(load)(velocity.y)}; 

    vx *= friction;
    vy *= std::move(friction);
    vy += std::move(gravity);

    auto vel_len {std::sqrt(vx * vx + vy * vy)}; 
    auto const max_vel_len {1.0f}; 
    if (cpp2::cmp_greater(vel_len,max_vel_len)) {
      vx *= max_vel_len / vel_len;
      vy *= std::move(max_vel_len) / std::move(vel_len);
    }

    auto px {CPP2_UFCS(load)(position.x)}; 
    auto py {CPP2_UFCS(load)(position.y)}; 

    auto cell_counter {0}; for( ; cpp2::cmp_less(cell_counter,CPP2_UFCS(ssize)(cells) / 4); cell_counter += 1 ) {
      Cell* other {std::addressof(CPP2_UFCS(at)(cells, cell_iter_index))}; 
      cell_iter_index = (cell_iter_index + 1) % CPP2_UFCS(size)(cells);

      if (&(*this) == other) {
        continue;
      }

      auto other_px {CPP2_UFCS(load)((*cpp2::assert_not_null(other)).position.x)}; 
      auto other_py {CPP2_UFCS(load)((*cpp2::assert_not_null(other)).position.y)}; 

      auto dx {std::move(other_px) - px}; 
      auto dy {std::move(other_py) - py}; 

      dx = std::fmod(dx + 1.5f * window_width, window_width) - 0.5f * window_width;
      dy = std::fmod(dy + 1.5f * window_height, window_height) - 0.5f * window_height;

      auto dist {std::sqrt(dx * dx + dy * dy)}; 

      if (cpp2::cmp_less(dist,0.001f) || cpp2::cmp_greater(dist,90.0f)) {
        continue;
      }

      auto dist2 {dist * dist}; 

      auto sfx {dx / (dist2)}; 
      auto sfy {dy / (dist2)}; 

      auto const separation_max {0.4f}; 
      sfx = std::clamp(sfx, -separation_max, separation_max);
      sfy = std::clamp(sfy, -separation_max, std::move(separation_max));

      vx -= std::move(sfx);
      vy -= std::move(sfy);

      auto damping {0.9f}; 
      auto force {config.attraction_matrix[color_num][(*cpp2::assert_not_null(std::move(other))).color_num] / std::move(damping)}; 
      auto fx {(std::move(dx) / dist2) * force}; 
      auto fy {(std::move(dy) / std::move(dist2)) * std::move(force)}; 

      auto const force_max {0.5f}; 
      fx = std::clamp(fx, -force_max, force_max);
      fy = std::clamp(fy, -force_max, std::move(force_max));

      vx += std::move(fx);
      vy += std::move(fy);
    }

    px += std::move(vx);
    py += std::move(vy);

    if (cpp2::cmp_less(px,0)) {
      px += window_width;
    }

    if (cpp2::cmp_greater(px,window_width)) {
      px -= window_width;
    }

    if (cpp2::cmp_less(py,0)) {
      py += window_height;
    }

    if (cpp2::cmp_greater(py,window_height)) {
      py -= window_height;
    }

    CPP2_UFCS(store)(position.x, std::move(px));
    CPP2_UFCS(store)(position.y, std::move(py));
  }

#line 121 "mnca.cpp2"
  auto Cell::draw(cpp2::in<Config> config) const& -> void{
    auto color {config.all_colors[color_num]}; 
    DrawCircle(position.x, position.y, 3.0f, std::move(color));
  }

#line 127 "mnca.cpp2"
std::vector<Cell> cells {}; 

int window_width {1080}; 
int window_height {720}; 

std::atomic<bool> running {true}; 

#line 134 "mnca.cpp2"
[[nodiscard]] auto create_random_cell(cpp2::in<Config> config) -> Cell{
  auto rw {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_width))}; 
  auto rh {cpp2::unsafe_narrow<float>(GetRandomValue(0, window_height))}; 
  return Cell(cpp2::as_<float>(std::move(rw)), cpp2::as_<float>(std::move(rh)), config); 
}

#line 140 "mnca.cpp2"
auto update_cells(cpp2::in<ssize_t> from, cpp2::in<ssize_t> to, cpp2::in<Config> config) -> void{
  while( (running) ) 
  {
    auto i {from}; for( ; cpp2::cmp_less(i,to); i += 1 ) {
      CPP2_UFCS(update)(cells[i], config);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(0));
  }
}

#line 154 "mnca.cpp2"
auto main() -> int{
  InitWindow(window_width, window_height, CPP2_UFCS(data)(window_name));
  SetTargetFPS(170);

  auto config {Config()}; 
  auto gui {GUI()}; 

  config.attraction_matrix = CPP2_UFCS(generate_attraction_matrix)(config, config.colors_number);

  std::cout << ("Window title is '" + cpp2::to_string(window_name) + "'.\n");
  std::cout << ("Size of a cell is " + cpp2::to_string(sizeof(Cell)) + " bytes.\n");

  CPP2_UFCS(reserve)(cells, max_cells);
  auto cell_num {1000}; for( ; cpp2::cmp_greater(cell_num,0); cell_num -= 1 ) {
    CPP2_UFCS(push_back)(cells, create_random_cell(config));
  }

  cpp2::u64 frame {0}; 
  auto const num_threads {std::max(cpp2::as_<ssize_t, 1>(), std::thread::hardware_concurrency() - cpp2::as_<ssize_t, 1>())}; 
  std::vector<std::thread> threads {}; 
  cpp2::u64 threads_cells {0}; 

  auto delegate_threads {[_0 = (&running), _1 = num_threads, _2 = (&cells), _6 = (&threads), _7 = config, _8 = (&threads_cells)]() mutable -> void{
    *cpp2::assert_not_null(_0) = true;
    auto i {cpp2::as_<ssize_t, 0>()}; for( ; cpp2::cmp_less(i,_1); i += 1 ) {
      auto cells_size {CPP2_UFCS(ssize)((*cpp2::assert_not_null(_2)))}; 
      auto from {(cells_size / _1) * i}; 
      auto to {(cells_size / _1) * (i + 1)}; 
      if (i == _1 - 1) {
        to = cells_size;
      }

      CPP2_UFCS(push_back)((*cpp2::assert_not_null(_6)), std::thread(update_cells, std::move(from), std::move(to), _7));

      *cpp2::assert_not_null(_8) = std::move(cells_size);
    }
  }}; 

  auto stop_threads {[_0 = (&running), _1 = (&threads)]() mutable -> void{
    *cpp2::assert_not_null(_0) = false;
    for ( auto& thread : *cpp2::assert_not_null(_1) ) {
      CPP2_UFCS(join)(thread);
    }
    CPP2_UFCS(clear)((*cpp2::assert_not_null(_1)));
  }}; 

  if ((cpp2::cmp_greater(num_threads,0))) 
  {
    delegate_threads();
  }

  while( !(WindowShouldClose()) ) 
  {
    frame += 1;

    if ((num_threads == 0)) 
    {
      for ( auto& cell : cells ) 
      {
        CPP2_UFCS(update)(cell, config);
      }
    }

    if ((frame % 10000 == 0)) 
    {
      for ( auto const& cell : cells ) 
      {
        CPP2_UFCS(print_xy)(cell);
      }
    }

    window_width = GetRenderWidth();
    window_height = GetRenderHeight();

    if (cpp2::cmp_less(CPP2_UFCS(size)(cells),max_cells)) 
    {
      if (IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE)) 
      {
        CPP2_UFCS(push_back)(cells, create_random_cell(config));
      }

      if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
      {
        auto mx {GetMouseX()}; 
        auto my {GetMouseY()}; 
        auto cell {Cell(std::move(mx), std::move(my), config)}; 
        CPP2_UFCS(push_back)(cells, std::move(cell));
      }

      if (threads_cells != CPP2_UFCS(size)(cells)) 
      {
        stop_threads();
        delegate_threads();
      }
    }

    BeginDrawing();
    DrawRectangle(0, 0, window_width, window_height, ColorAlpha(BLACK, 0.6f));
    //DrawRectangle(0, 0, window_width, window_height, BLACK);

    for ( auto const& cell : cells ) {
      CPP2_UFCS(draw)(cell, config);
    }
    CPP2_UFCS(draw)(gui, config);

    EndDrawing();
  }

  std::move(stop_threads)();

  CloseWindow();
}

#line 267 "mnca.cpp2"
auto print_xy(cpp2::in<Cell> cell) -> void{
  std::cout << "cell.position = " << cell.position << "\n";
}

