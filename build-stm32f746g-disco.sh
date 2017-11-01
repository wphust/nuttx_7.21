#!/bin/sh

cd nuttx-7.21/nx/nuttx/tools/
./configure.sh stm32f746g-disco/net-nsh

cd ..
make  menuconfig

make
