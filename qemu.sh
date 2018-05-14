#!/bin/sh
set -e
#. ./iso.sh
. ./build.sh

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom cppos.iso
qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel kernel/cppos.kernel
