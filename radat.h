#ifndef RADAT_H
#define RADAT_H

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long

#define MAX_BUFF_SIZE 4096 /* in bytes */

#define RAD_CODE_ACCREQ 1
#define RAD_CODE_ACCACC 2
#define RAD_CODE_ACCREJ 3

#define ERROR(...) { fprintf(stderr, __VA_ARGS__); exit(0); }

struct rad_hdr {
  BYTE code;
  BYTE ident;
  BYTE len[2];
  DWORD auth[4];
};


/* prototypes */
void add_attrib_string(BYTE, char *);
void add_attrib_int(BYTE, unsigned int);

int parse_config(char *);

int alloc_socket(char *, unsigned int);
void send_pack(int, unsigned int);

void start_timed_send(int, int, double, int);

void incr_ident(void);

void print_version(void);
void print_usage(void);

#endif
