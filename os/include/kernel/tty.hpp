#pragma once

#include <cstdint>

namespace tty {

class Terminal {
 public:
  Terminal();
  void put_char(char ch);
  void put_string(const char* string);

 private:
  std::size_t make_index(std::size_t x, std::size_t y);
  void scrollup();

  std::size_t d_row = 0;
  std::size_t d_column = 0;
  volatile std::uint16_t* const d_buffer =
      reinterpret_cast<std::uint16_t*>(0xB8000);

  static std::size_t WIDTH;
  static std::size_t HEIGHT;
  static std::uint8_t COLOR;
};

} // namespace tty
