DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CXXFLAGS?=
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CXXFLAGS:=$(CXXFLAGS) -ffreestanding -fno-stack-protector -Wall -Wextra -Wpedantic
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CXXFLAGS:=$(CXXFLAGS) $(KERNEL_ARCH_CXXFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS)\
kernel/kernel.o

OBJS=$(KERNEL_OBJS)
LINK_LIST=$(LDFLAGS) $(KERNEL_OBJS) $(LIBS)

# OBJS=\
# $(ARCHDIR)/crti.o\
# $(ARCHDIR)/crtbegin.o\
# $(KERNEL_OBJS)\
# $(ARCHDIR)/crtend.o\
# $(ARCHDIR)/crtn.o\

# LINK_LIST=\
# $(LDFLAGS)\
# $(ARCHDIR)/crti.o\
# $(ARCHDIR)/crtbegin.o\
# $(KERNEL_OBJS)\
# $(LIBS)\
# $(ARCHDIR)/crtend.o\
# $(ARCHDIR)/crtn.o\

.PHONY: all clean install install-headers install-kernel

all: cppos.kernel

cppos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CXX) -T $(ARCHDIR)/linker.ld -o $@ $(CXXFLAGS) $(LINK_LIST)
	#grub-file --is-x86-multiboot myos.kernel

#$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
#	OBJ=`$(CXX) $(CXXFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.cpp.o:
	$(CXX) -MD -c $< -o $@ -std=c++17 $(CXXFLAGS) $(CPPFLAGS)

.S.o:
	as $(ASFLAGS) $< -o $@

clean:
	rm -f cppos.kernel
	find . -type f -name '*.o' -delete
	find . -type f -name '*.d' -delete

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: cppos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp cppos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
