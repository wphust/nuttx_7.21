/****************************************************************************
 * netutils/netlib/netlib_setnodeaddr.c
 *
 *   Copyright (C) 2017 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <net/if.h>

#include <nuttx/net/sixlowpan.h>

#include "netutils/netlib.h"

#if defined(CONFIG_NET_6LOWPAN) && CONFIG_NSOCKET_DESCRIPTORS > 0

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: netlib_setnodeaddr
 *
 * Description:
 *   Set the 6loWPAN IEEE802.15.4 MAC network driver node address
 *
 * Parameters:
 *   ifname   The name of the interface to use
 *   nodeaddr Node address to set, size must be NET_6LOWPAN_ADDRSIZE
 *
 * Return:
 *   0 on success; -1 on failure
 *
 ****************************************************************************/

int netlib_setnodeaddr(FAR const char *ifname, FAR const uint8_t *nodeaddr)
{
  int ret = ERROR;

  if (ifname && nodeaddr)
    {
      /* Get a socket (only so that we get access to the INET subsystem) */

      int sockfd = socket(PF_INET6, NETLIB_SOCK_IOCTL, 0);
      if (sockfd >= 0)
        {
          struct ifreq req;

          /* Put the driver name into the request */

          strncpy(req.ifr_name, ifname, IFNAMSIZ);

          /* Put the new MAC address into the request */

          req.ifr_hwaddr.sa_family = AF_INET6;
          memcpy(&req.ifr_hwaddr.sa_data, nodeaddr, NET_6LOWPAN_ADDRSIZE);

          /* Perform the ioctl to set the node address */

          ret = ioctl(sockfd, SIOCSIFHWADDR, (unsigned long)&req);
          close(sockfd);
        }
    }

  return ret;
}

#endif /* CONFIG_NET_6LOWPAN && CONFIG_NSOCKET_DESCRIPTORS */
