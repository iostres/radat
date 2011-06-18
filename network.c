#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "radat.h"

extern const char packet[];

static struct sockaddr_in si_dest;


int alloc_socket(char *dest_ip, unsigned int dest_port)
{
  int s;
 
  if ((s = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP))==-1)
    ERROR("Unable to bind socket!\n");

  memset((char *) &si_dest, 0, sizeof(si_dest));
  si_dest.sin_family = AF_INET;
  si_dest.sin_port = htons(dest_port);

  if (inet_aton(dest_ip, &si_dest.sin_addr)==0)
    ERROR("inet_aton() failed\n");

  return s;
}

void send_pack(int sock, unsigned int len)
{
  if (sendto(sock, packet, len, 0, (struct sockaddr *)&si_dest, sizeof(si_dest))==-1)
    ERROR("Error sending packet!\n");
}
