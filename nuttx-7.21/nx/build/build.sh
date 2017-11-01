#!/bin/bash
cd ../nuttx/tools/
./configure.sh g3-amm-stm32f746g-disco/nsh
cd ..
make
cd ../build
