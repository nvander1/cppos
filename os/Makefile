ASFLAGS = --32 -march=i686
CXXFLAGS = -m32 -ffreestanding -nostdlib --std=c++17 -fno-stack-protector -Wall -Wextra -Wpedantic
LDLIBS = -lgcc

all: os

kernel.o: kernel.cpp vga.hpp string.hpp
	$(CXX) $(CXXFLAGS) -c -o kernel.o kernel.cpp $(LDLIBS)

os: tty.o kernel.o boot.o linker.ld
	$(CXX) $(CXXFLAGS) -T linker.ld -o os.bin boot.o kernel.o tty.o $(LDLIBS)

.PHONY: test
test:
	qemu-system-i386 -kernel os.bin

.PHONY: clean
clean:
	rm *.o os.bin
