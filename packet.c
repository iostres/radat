#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/evp.h>

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

char *calc_user_passw(char *secret, char *password)
{
  EVP_MD_CTX mdctx;
  const EVP_MD *md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int i;
  unsigned int md_len;

  OpenSSL_add_all_digests();

  md = EVP_get_digestbyname("MD5");

  EVP_MD_CTX_init(&mdctx);
  EVP_DigestInit_ex(&mdctx, md, NULL);
  EVP_DigestUpdate(&mdctx, secret, strlen(secret));
  EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup(&mdctx);

  printf("Digest is: ");
  for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);
  printf("\n");

  return NULL;
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
