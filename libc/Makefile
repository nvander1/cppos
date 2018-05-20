DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CXXFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(PREFIX)/lib

CXXFLAGS:=$(CXXFLAGS) -ffreestanding -fno-stack-protector -Wall -Wextra -Wpedantic
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CXXFLAGS:=$(CXXFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CXXFLAGS:=$(CXXFLAGS) $(ARCH_CXXFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CXXFLAGS:=$(CXXFLAGS) $(KERNEL_ARCH_CXXFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS)\
string/strlen.o\

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS)\

OBJS=\
$(FREEOBJS)\
$(HOSTEDOBJS)\

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # not ready for libc yet
BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.cpp.o:
	$(CXX) -MD -c $< -o $@ -std=c++17 $(CXXFLAGS) $(CPPFLAGS)

.S.o:
	$(CXX) -MD -c $< -o $@ -std=c++17 $(CPPFLAGS)

.cpp.libk.o:
	$(CXX) -MD -c $< -o $@ -std=c++17 $(LIBK_CXXFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
	as $(ASFLAGS) $< -o $@

clean:
	rm -f $(BINARIES) *.a
	find . -type f -name '*.o' -delete
	find . -type f -name '*.d' -delete

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
