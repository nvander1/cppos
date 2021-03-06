#pragma once

#include <stdint.h>

namespace vga {

enum Color {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHT_GREY = 7,
  DARK_GREY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN = 14,
  WHITE = 15
};

inline constexpr uint8_t entry_color(Color fg, Color bg) {
  return fg | (bg << 4);
}

inline constexpr uint16_t entry(unsigned char c, uint8_t color) {
  return uint16_t{c} | (uint16_t{color} << 8);
}

} // namespace vga
