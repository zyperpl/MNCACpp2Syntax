

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "src/gui.cpp2"

#line 10 "src/gui.cpp2"
class GUI;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "src/gui.cpp2"
#include "types.h"

#include <raylib.h>
#include <raymath.h>

#include "config.h"

extern Font load_font();

#line 10 "src/gui.cpp2"
class GUI {
  private: Font const font {load_font()}; 
  private: cpp2::u64 font_size {18}; 
  private: cpp2::u64 text_spacing {0}; 

  private: float element_x {0.0f}; 
  private: float element_y {0.0f}; 
  private: cpp2::u64 element_counter {0}; 
  private: cpp2::u64 active {0}; 
  private: cpp2::u64 hover {0}; 

  private: bool show_board {true}; 
  private: float board_start_x {0.0f}; 
  private: float board_start_y {0.0f}; 
  private: float const board_size {44.0f}; 

  private: bool show_attraction_slider {false}; 
  private: cpp2::u8 attraction_slider_index_x {0}; 
  private: cpp2::u8 attraction_slider_index_y {0}; 

  public: auto draw_text(
                      cpp2::in<std::string_view> text, 
                      Rectangle rect, 
                      cpp2::in<TextJustification> justification, 
                      cpp2::in<Color> color) const& -> void;

#line 47 "src/gui.cpp2"
  public: auto draw(Config& config) & -> void;

#line 68 "src/gui.cpp2"
  private: static const int main_mouse_button;
  private: [[nodiscard]] static auto is_mouse_pressed() -> bool;
  private: [[nodiscard]] static auto is_mouse_released() -> bool;
  private: [[nodiscard]] static auto mouse_position() -> Vector2;
  private: [[nodiscard]] static auto mouse_in_rect(cpp2::in<Rectangle> rect) -> bool;
  private: static const Color default_button_color;

  private: [[nodiscard]] auto is_active(cpp2::in<cpp2::u64> id) const& -> bool;
  private: auto set_active(cpp2::in<cpp2::u64> id) & -> void;
  private: [[nodiscard]] auto is_hover(cpp2::in<cpp2::u64> id) const& -> bool;
  private: auto set_hover(cpp2::in<cpp2::u64> id) & -> void;
  private: auto advance_element_counter() & -> void;

  private: auto begin_frame() & -> void;

#line 88 "src/gui.cpp2"
  private: auto end_frame() & -> void;

#line 94 "src/gui.cpp2"
  private: auto start_layout(cpp2::in<float> x, cpp2::in<float> y) & -> void;

#line 99 "src/gui.cpp2"
  private: auto draw_board(cpp2::in<Config> config) & -> void;

#line 142 "src/gui.cpp2"
  private: [[nodiscard]] auto button(cpp2::in<std::string_view> text, cpp2::in<cpp2::i32> width, cpp2::in<cpp2::i32> height, Color color) & -> bool;

#line 181 "src/gui.cpp2"
  private: auto enable_hover(cpp2::in<cpp2::u64> id, cpp2::in<Rectangle> rect) & -> void;

#line 188 "src/gui.cpp2"
  private: [[nodiscard]] auto check_active_rect_pressed(cpp2::in<cpp2::u64> id, cpp2::in<Rectangle> rect) & -> bool;

#line 204 "src/gui.cpp2"
  private: [[nodiscard]] static auto hash(cpp2::in<std::string_view> text) -> cpp2::u64;
  private: [[nodiscard]] static auto hash(cpp2::in<cpp2::u64> a, cpp2::in<std::string_view> b) -> cpp2::u64;
  public: GUI() = default;
  public: GUI(GUI const&) = delete; /* No 'that' constructor, suppress copy */
  public: auto operator=(GUI const&) -> void = delete;

#line 206 "src/gui.cpp2"
};


//=== Cpp2 function definitions =================================================

#line 1 "src/gui.cpp2"

#line 30 "src/gui.cpp2"
  auto GUI::draw_text(
                      cpp2::in<std::string_view> text, 
                      Rectangle rect, 
                      cpp2::in<TextJustification> justification, 
                      cpp2::in<Color> color) const& -> void{

    auto text_size {MeasureTextEx(font, CPP2_UFCS(data)(text), font_size, text_spacing)}; 

    if (justification == TextJustification::Center) {rect.x += rect.width / 2 - text_size.x / 2; }
    if (justification == TextJustification::Right)  { rect.x += rect.width - text_size.x; }

    rect.y += rect.height / 2 - std::move(text_size).y / 2;

    DrawTextEx(font, CPP2_UFCS(data)(text), Vector2(rect.x + 1, rect.y + 1), font_size, text_spacing, ColorBrightness(color, -0.5f));
    DrawTextEx(font, CPP2_UFCS(data)(text), Vector2(rect.x, std::move(rect).y), font_size, text_spacing, color);
  }

#line 47 "src/gui.cpp2"
  auto GUI::draw(Config& config) & -> void{
    begin_frame();
    start_layout(8, 4);

    if ((button("Show board", 11 * 12, 11 * 5, default_button_color))) 
    {
      show_board = !(show_board);
    }

    if ((show_board)) 
    {
      draw_board(config);
    }
    else 
    {
      board_start_x = -board_size * config.colors_number;
    }

    end_frame();
  }

  inline CPP2_CONSTEXPR int GUI::main_mouse_button = MOUSE_LEFT_BUTTON;
  [[nodiscard]] auto GUI::is_mouse_pressed() -> bool { return IsMouseButtonPressed(main_mouse_button);  }
#line 70 "src/gui.cpp2"
  [[nodiscard]] auto GUI::is_mouse_released() -> bool { return IsMouseButtonReleased(main_mouse_button);  }
#line 71 "src/gui.cpp2"
  [[nodiscard]] auto GUI::mouse_position() -> Vector2 { return GetMousePosition();  }
#line 72 "src/gui.cpp2"
  [[nodiscard]] auto GUI::mouse_in_rect(cpp2::in<Rectangle> rect) -> bool { return CheckCollisionPointRec(mouse_position(), rect);  }
  inline CPP2_CONSTEXPR Color GUI::default_button_color = Color(110, 110, 110, 255);

#line 75 "src/gui.cpp2"
  [[nodiscard]] auto GUI::is_active(cpp2::in<cpp2::u64> id) const& -> bool { return active == id;  }
#line 76 "src/gui.cpp2"
  auto GUI::set_active(cpp2::in<cpp2::u64> id) & -> void { active = id;  }
#line 77 "src/gui.cpp2"
  [[nodiscard]] auto GUI::is_hover(cpp2::in<cpp2::u64> id) const& -> bool { return hover == id;  }
#line 78 "src/gui.cpp2"
  auto GUI::set_hover(cpp2::in<cpp2::u64> id) & -> void { hover = id;  }
#line 79 "src/gui.cpp2"
  auto GUI::advance_element_counter() & -> void { element_counter += 1;  }

#line 81 "src/gui.cpp2"
  auto GUI::begin_frame() & -> void{
    element_x = 0.0f;
    element_y = 0.0f;
    element_counter = 0;
    hover = 0;
  }

#line 88 "src/gui.cpp2"
  auto GUI::end_frame() & -> void{
    if (is_mouse_released()) {
      active = 0;
    }
  }

#line 94 "src/gui.cpp2"
  auto GUI::start_layout(cpp2::in<float> x, cpp2::in<float> y) & -> void{
    element_x = x;
    element_y = y;
  }

#line 99 "src/gui.cpp2"
  auto GUI::draw_board(cpp2::in<Config> config) & -> void{
    advance_element_counter();

    auto const size {board_size}; 
    board_start_x = Lerp(board_start_x, element_x, 0.07f);
    board_start_y = element_y;

    auto const start_x {std::roundf(board_start_x)}; 
    auto const start_y {std::roundf(board_start_y)}; 

    cpp2::u8 iy {0}; for( ; cpp2::cmp_less(iy,config.colors_number); ++iy ) 
    {
      DrawRectangle(start_x + -1, start_y + (iy + 1) * size, size, size, CPP2_ASSERT_IN_BOUNDS(config.all_colors, iy));
      DrawRectangle(start_x + (iy + 1) * size, start_y + -1, size, size, CPP2_ASSERT_IN_BOUNDS(config.all_colors, iy));
      cpp2::u8 ix {0}; for( ; cpp2::cmp_less(ix,config.colors_number); ++ix ) 
      {
        auto x {start_x + ix * size}; 
        auto y {start_y + iy * size}; 
        auto attraction {CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(config.attraction_matrix, iy), ix)}; 
        auto color {ColorBrightness(RED, 1.0f - attraction)}; 
        if (cpp2::cmp_less(attraction,0.0f)) {
          color = ColorBrightness(BLUE, 1.0f - (-attraction));
        }
        DrawRectangle(x + size, y + size, size, size, color);
        auto const text {TextFormat("%.02f", std::move(attraction))}; 
        auto before_element_x {element_x}; 
        auto before_element_y {element_y}; 
        element_x = std::move(x) + size;
        element_y = std::move(y) + size;
        if ((button(std::move(text), size, size, std::move(color)))) 
        {
          attraction_slider_index_x = ix;
          attraction_slider_index_y = iy;
          show_attraction_slider = true;
        }
        element_x = std::move(before_element_x);
        element_y = std::move(before_element_y);
      }

      element_y += size;
    }
  }

#line 142 "src/gui.cpp2"
  [[nodiscard]] auto GUI::button(cpp2::in<std::string_view> text, cpp2::in<cpp2::i32> width, cpp2::in<cpp2::i32> height, Color color) & -> bool{
    advance_element_counter();
    cpp2::u64 my_hash {hash(element_counter, text)}; 
    auto rect {Rectangle(element_x, element_y, width, height)}; 
    auto border_rect {Rectangle(rect.x - 2.0f, rect.y - 2.0f, rect.width + 4.0f, rect.height + 4.0f)}; 
    enable_hover(my_hash, rect);

    auto text_color {Color(255, 255, 255, 255)}; 
    auto border_color {Color(0, 0, 0, 155)}; 

    if (is_hover(my_hash)) {
      color = Color(130, 130, 130, 255);
      border_color = Color(20, 20, 20, 155);
      text_color = Color(250, 250, 255, 255);

      border_rect.y += 1.0f;
    }
    if (is_active(my_hash)) {
      color = Color(90, 90, 90, 255);
      text_color = Color(240, 240, 250, 255);

      if (mouse_in_rect(rect)) {
        border_color = Color(40, 40, 50, 155);
        rect.y += 1.0f;
        border_rect.y += 1.0f;
      }
    }

    auto roundness {0.5f}; 
    auto segments {16}; 

    DrawRectangleRounded(std::move(border_rect), roundness, segments, std::move(border_color));
    DrawRectangleRounded(rect, std::move(roundness), std::move(segments), std::move(color));
    draw_text(text, rect, TextJustification::Center, std::move(text_color));
    element_y += rect.height + 8.0f;

    return check_active_rect_pressed(std::move(my_hash), std::move(rect)); 
  }

#line 181 "src/gui.cpp2"
  auto GUI::enable_hover(cpp2::in<cpp2::u64> id, cpp2::in<Rectangle> rect) & -> void{
    if (mouse_in_rect(rect) && active == 0) 
    {
      set_hover(id);
    }
  }

#line 188 "src/gui.cpp2"
  [[nodiscard]] auto GUI::check_active_rect_pressed(cpp2::in<cpp2::u64> id, cpp2::in<Rectangle> rect) & -> bool{
    if (mouse_in_rect(rect)) 
    {
      if (is_active(id) && is_mouse_released()) 
      {
        return true; 
      }
      else {if (is_mouse_pressed()) 
      {
        set_active(id);
      }}
    }

    return false; 
  }

#line 204 "src/gui.cpp2"
  [[nodiscard]] auto GUI::hash(cpp2::in<std::string_view> text) -> cpp2::u64 { return std::hash<std::string_view>()(text);  }
#line 205 "src/gui.cpp2"
  [[nodiscard]] auto GUI::hash(cpp2::in<cpp2::u64> a, cpp2::in<std::string_view> b) -> cpp2::u64 { return std::hash<std::string_view>()(b) + a;  }

