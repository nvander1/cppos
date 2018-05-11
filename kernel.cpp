#include "vga.hpp"
#include <cstdint>

#ifndef __i386__
#error "need ix86 elf compiler"
#endif


extern "C" void kernel_main(void) {
  auto term = vga::Terminal{};
  term << "Hello, World!\n\nThis is hopefully on a new line!\nWoot";
}
