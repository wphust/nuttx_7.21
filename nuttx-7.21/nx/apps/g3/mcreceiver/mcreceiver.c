#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netutils/ipmsfilter.h>

void setip(char* ip, char* netmask, char* gateway);

#define TARGET_IP_ADDRESS "10.0.0.1"
#define TARGET_IP_MASK	  "255.255.255.0"
#define TARGET_IP_GATEWAY "10.0.0.254"

#define MULTICAST_PORT 	   12345
#define MULTICAST_GROUP    "224.0.0.3"

#define MSGBUFSIZE 800

void mcreceiver_run(void) {
	struct sockaddr_in addr;
	int fd, nbytes, addrlen;
	//struct ip_mreq mreq;
	char msgbuf[MSGBUFSIZE];
	u_int reuseaddr = 1; /*** MODIFICATION TO ORIGINAL */

	/* Configure ethernet*/
	setip(TARGET_IP_ADDRESS, TARGET_IP_MASK, TARGET_IP_GATEWAY);

	/* create what looks like an ordinary UDP socket */
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	/* allow multiple sockets to use the same PORT number */
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) < 0)
	{
		perror("Reusing ADDR failed");
		exit(1);
	}

	/* set up destination address */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
	addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
	addr.sin_port = htons(MULTICAST_PORT);

	/* bind to receive address */
	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{800
		perror("bind");
		exit(1);
	}

	printf("Target:%s join group:%s\n", TARGET_IP_ADDRESS, MULTICAST_GROUP);
	if (ipmsfilter("eth0", &(addr.sin_addr), MCAST_INCLUDE))
	{
		printf("Join group failed\n");
		exit(1);
	}

	/* now just enter a read-print loop */
	printf("listening multicast messages...\n");
	while (1)
	{
		addrlen = sizeof(addr);
		if ((nbytes = recvfrom(fd, msgbuf, MSGBUFSIZE, 0,
				(struct sockaddr *) &addr, &addrlen)) < 0) {
			perror("recvfrom");
			exit(1);
		}
		puts(msgbuf);
		memset(msgbuf, 0, sizeof(msgbuf));
	}
}
