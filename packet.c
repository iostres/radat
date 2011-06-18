#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>


#include "radat.h"

/* globals */
const char packet[MAX_BUFF_SIZE];
char *pack_curr = NULL;
WORD len;
struct rad_hdr *p_hdr = (struct rad_hdr *)packet;


void setup_header(BYTE code, BYTE ident) 
{
  p_hdr = (struct rad_hdr *)packet;
  srand(time(NULL));
  p_hdr->ident = ident;    
  p_hdr->code = code;    
  p_hdr->auth[0] = rand();
  p_hdr->auth[1] = rand();
  p_hdr->auth[2] = rand();
  p_hdr->auth[3] = rand();

  len = pack_curr - packet;
  p_hdr->len[0] = (len & 0xFF00) >> 8; 
  p_hdr->len[1] = len & 0xFF; 
}

void incr_ident(void)
{
  p_hdr->ident++;
}

void add_attrib_string(BYTE type, char *string)
{
  int str_len = 0;

  str_len = strlen(string);
  *pack_curr++ = type;
  *pack_curr++ = str_len+2;
  memcpy(pack_curr, string, str_len);
  pack_curr+=str_len;

}

void add_attrib_int(BYTE type, unsigned int ui_val)
{
    *pack_curr++ = type;
    *pack_curr++ = 6; /* Length */
    *(unsigned int *)pack_curr = htonl(ui_val);
    pack_curr += sizeof(unsigned int);
}
