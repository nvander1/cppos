#pragma once

#include "string.hpp"
#include <cstdint>

namespace vga {

inline constexpr std::uint8_t BLACK = 0;
inline constexpr std::uint8_t BLUE = 1;
inline constexpr std::uint8_t GREEN = 2;
inline constexpr std::uint8_t CYAN = 3;
inline constexpr std::uint8_t RED = 4;
inline constexpr std::uint8_t MAGENTA = 5;
inline constexpr std::uint8_t BROWN = 6;
inline constexpr std::uint8_t LIGHT_GREY = 7;
inline constexpr std::uint8_t DARK_GREY = 8;
inline constexpr std::uint8_t LIGHT_BLUE = 9;
inline constexpr std::uint8_t LIGHT_GREEN = 10;
inline constexpr std::uint8_t LIGHT_CYAN = 11;
inline constexpr std::uint8_t LIGHT_RED = 12;
inline constexpr std::uint8_t LIGHT_MAGENTA = 13;
inline constexpr std::uint8_t LIGHT_BROWN = 14;
inline constexpr std::uint8_t WHITE = 15;

inline std::uint8_t entry_color(std::uint8_t fg, std::uint8_t bg) {
  return fg | (bg << 4);
}

inline std::uint16_t entry(unsigned char c, std::uint8_t color) {
  return std::uint16_t{c} | (std::uint16_t{color} << 8);
}

template <std::size_t Width = 80, std::size_t Height = 25,
          std::uint64_t Address = 0xB8000>
class Terminal {
 public:
  std::size_t width = Width;
  std::size_t height = Height;

  Terminal(std::uint8_t fg = LIGHT_GREY, std::uint8_t bg = BLACK)
      : d_row{}, d_column{}, d_color{entry_color(fg, bg)} {
    for (auto y = 0ULL; y < Height; ++y) {
      for (auto x = 0ULL; x < Width; ++x) {
        auto index = y * Width + x;
        d_buffer[index] = entry(' ', d_color);
      }
    }
  }

  Terminal& operator<<(const char* data) {
    for (auto i = 0ULL; i < strlen(data); ++i) {
      putc(data[i]);
    }
    return *this;
  }

  void putc(char c) {
    if (c == '\n') {
      d_column = 0;
      ++d_row;
      return;
    }

    auto index = d_row * Width + d_column;
    d_buffer[index] = entry(c, d_color);
    d_column = ((1 + d_column) % Width);
    if (d_column == 0) {
      d_row = ((1 + d_row) % Height);
    }
  }

  void set_color(std::uint8_t fg, std::uint8_t bg) {
    d_color = entry_color(fg, bg);
  }

 private:
  std::size_t d_row;
  std::size_t d_column;
  std::uint8_t d_color;

  volatile std::uint16_t* const d_buffer = reinterpret_cast<volatile std::uint16_t* const>(Address);
};

}
