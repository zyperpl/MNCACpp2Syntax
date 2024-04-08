

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "gui.cpp2"

#line 7 "gui.cpp2"
class GUI;
  

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "gui.cpp2"
#include "types.h"

#include <raylib.h>

#include "config.h"

#line 7 "gui.cpp2"
class GUI {
  private: Font font {GetFontDefault()}; 
  private: cpp2::u64 font_size {10}; 
  private: cpp2::u64 text_spacing {0}; 

  public: auto draw_text(cpp2::in<std::string_view> text, Rectangle rect, cpp2::in<TextJustification> justification, cpp2::in<Color> color) const& -> void;

#line 27 "gui.cpp2"
  public: auto draw(cpp2::in<Config> config) const& -> void;

#line 31 "gui.cpp2"
  private: auto draw_board(cpp2::in<Config> config) const& -> void;
  public: GUI() = default;
  public: GUI(GUI const&) = delete; /* No 'that' constructor, suppress copy */
  public: auto operator=(GUI const&) -> void = delete;


#line 54 "gui.cpp2"
};


//=== Cpp2 function definitions =================================================

#line 1 "gui.cpp2"

#line 12 "gui.cpp2"
  auto GUI::draw_text(cpp2::in<std::string_view> text, Rectangle rect, cpp2::in<TextJustification> justification, cpp2::in<Color> color) const& -> void{

    cpp2::deferred_init<Vector2> size; 
    if (justification == TextJustification::Left) {size.construct(Vector2(0, 0)); }
    else {
      size.construct(MeasureTextEx(font, CPP2_UFCS(data)(text), font_size, text_spacing));
    }

    if (justification == TextJustification::Center) {rect.x += rect.width / 2 - size.value().x / 2; }
    if (justification == TextJustification::Right)  { rect.x += rect.width - std::move(size.value()).x;}

    DrawText(CPP2_UFCS(data)(text), rect.x, rect.y, font_size, color);
    DrawText(CPP2_UFCS(data)(text), rect.x + 1, rect.y + 1, font_size, ColorBrightness(color, -0.5f));
  }

#line 27 "gui.cpp2"
  auto GUI::draw(cpp2::in<Config> config) const& -> void{
    draw_board(config);
  }

#line 31 "gui.cpp2"
  auto GUI::draw_board(cpp2::in<Config> config) const& -> void{
    auto const size {30}; 
    auto iy {0}; for( ; cpp2::cmp_less(iy,config.colors_number); ++iy ) 
    {
      DrawRectangle(-1, (iy + 1) * size, size, size, CPP2_ASSERT_IN_BOUNDS(config.all_colors, iy));
      DrawRectangle((iy + 1) * size, -1, size, size, CPP2_ASSERT_IN_BOUNDS(config.all_colors, iy));
      auto ix {0}; for( ; cpp2::cmp_less(ix,config.colors_number); ++ix ) 
      {
        auto x {ix * size}; 
        auto y {iy * size}; 
        auto attraction {CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(config.attraction_matrix, iy), ix)}; 
        auto color {ColorBrightness(RED, 1.0f - attraction)}; 
        if (cpp2::cmp_less(attraction,0.0f)) {
          color = ColorBrightness(BLUE, 1.0f - (-attraction));
        }
        DrawRectangle(x + size, y + size, size, size, color);
        auto const text {TextFormat("%.02f", std::move(attraction))}; 

        auto text_rect {Rectangle(std::move(x) + size, std::move(y) + size + size / 2, size, size)}; 
        draw_text(std::move(text), std::move(text_rect), TextJustification::Center, ColorBrightness(std::move(color), -0.1f));
      }
    }
  }

