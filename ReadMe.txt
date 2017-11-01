Building for STM32 disco development 

login to host ukbandvsl05v using cygwin X11..
    
1) cd [your local path]/nx/nuttx/tools
2) ./configure.sh stm32f746g-disco/nsh
3) cd ..
4) make  menuconfig   (Optional to change config, not required)
5) export PATH=$PATH:/usr/local/arm/gcc-arm-none-eabi-5_4-2016q3/bin  (This should only be done once, can use setupEnv.sh for this step)
6) make

See build-stm32f746g-disco.sh

=========================================

To debug the stm32f746g-disco development board via the built-in USB stlink interface you will need to :-

1) Install OpenOCD 0.10.0 version from http://svn-general-svc:18080/svn/auto_thirdparty_tools/trunk/openOCD-win32
2) put this in C:\openOCD-win32-0.10.0
3) 