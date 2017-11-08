/*
 ============================================================================
 Name        : mcsender.c
 Author      : wang_p
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define TARGET_IP_ADDRESS "10.0.0.2"
#define TARGET_IP_MASK	  "255.255.255.0"
#define TARGET_IP_GATEWAY "10.0.0.254"

#define MULTICAST_PORT 	   12345
#define MULTICAST_GROUP    "224.0.0.3"

#define MSGBUFSIZE 800

void mcsender_run(void)
{
     struct sockaddr_in addr;
     int fd, cnt;
     char buffer[MSGBUFSIZE]="";
     int counter = 0;

     buffer[MSGBUFSIZE-1] = '0';

	 /* Configure ethernet*/
	 setip(TARGET_IP_ADDRESS, TARGET_IP_MASK, TARGET_IP_GATEWAY);

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
     {
	  perror("socket");
	  exit(1);
     }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=inet_addr(MULTICAST_GROUP);
     addr.sin_port=htons(MULTICAST_PORT);


     /* now just sendto() our destination! */
     printf("Target:%s multicast to group:%s...\n", TARGET_IP_ADDRESS, MULTICAST_GROUP);
     while (1)
     {

    	 sprintf(buffer, "%d", counter ++);
	  if (sendto(fd,buffer,MSGBUFSIZE,0,(struct sockaddr *) &addr,
		     sizeof(addr)) < 0) {
	       perror("sendto");
	       exit(1);
	  }
     }
}
