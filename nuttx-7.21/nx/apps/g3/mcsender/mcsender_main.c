/****************************************************************************
 * g3/mcsender/mcsender_main.c
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * multicast main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int mcsender_main(int argc, char *argv[])
#endif
{
  printf("G3 multicast sender is running\n");
  mcsender_run();
  return 0;
}
