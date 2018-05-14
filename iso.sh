#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/cppos.kernel isodir/boot/cppos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cppos" {
        multiboot /boot/cppos.kernel
}
EOF
grub-mkrescue -o cppos.iso isodir
