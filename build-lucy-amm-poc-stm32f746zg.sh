#!/bin/sh

cd nuttx-7.21/nx/nuttx/tools/
./configure.sh lucy-amm-poc-stm32f746zg/net-nsh

cd ..
make  menuconfig

make
