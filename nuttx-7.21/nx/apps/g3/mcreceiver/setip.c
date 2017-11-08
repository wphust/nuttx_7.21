/*
 * setip.c
 *
 *  Created on: 8 Nov 2017
 *      Author: wang_p
 */
#include <netinet/in.h>
#include <stdio.h>
#include <netutils/netlib.h>
#include <arpa/inet.h>


void setip(char* ip, char* netmask, char* gateway) {
	struct in_addr addr;

	printf("Configuring Ethernet...\n");

	/* Set up our host address */
	addr.s_addr = inet_addr(ip);
	netlib_set_ipv4addr("eth0", &addr);

	/* Set up the default router address */

	addr.s_addr = htonl(gateway);
	netlib_set_dripv4addr("eth0", &addr);

	/* Setup the subnet mask */

	addr.s_addr = inet_addr(netmask);
	netlib_set_ipv4netmask("eth0", &addr);

	/* New versions of netlib_set_ipvXaddr will not bring the network up,
	 * So ensure the network is really up at this point.
	 */
	netlib_ifup("eth0");
}
