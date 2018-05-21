PROJECTS = libc kernel

HOST:=i686-elf
export HOSTARCH!=./target-triplet-to-arch.sh $(HOST)
export AR:=$(HOST)-ar
export AS:=$(HOST)-as
export CXX:=$(HOST)-g++

export PREFIX=/usr
export EXEC_PREFIX:=$(PREFIX)
export BOOTDIR:=/boot
export LIBDIR:=$(EXEC_PREFIX)/lib
export INCLUDEDIR:=$(PREFIX)/include

export CXXFLAGS:=-O2 -g
export CPPFLAGS:=

export SYSROOT:=$(shell pwd)/sysroot
export CXX:=$(CXX) --sysroot=$(SYSROOT)
export DESTDIR:=$(SYSROOT)

ifneq ($(shell echo $(HOST) | grep -Eq -- 'elf($|-)'), 0)
	export CXX:=$(CXX) -isystem=$(INCLUDEDIR)
endif

.PHONY: all clean test $(PROJECTS)

all: $(PROJECTS)

$(PROJECTS):
	$(MAKE) --directory=$@ install-headers
	$(MAKE) --directory=$@ install

clean:
	for PROJ in $(PROJECTS); do \
		$(MAKE) --directory=$$PROJ clean; \
	done

test:
	qemu-system-$(HOSTARCH) -kernel kernel/cppos.kernel

