#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "radat.h"

extern const char *packet;
extern char *pack_curr;

int main(int argc, char *argv[])
{
  int sock;

  char *a_val = NULL;
  int opt;
  
  /* Shift to position of first attribute */
  pack_curr = (char *)packet + sizeof(struct rad_hdr);


  print_version();
  while ((opt = getopt (argc, argv, "a:s:d:p:i:r:")) != -1)
    switch (opt)
      {
      case 'a':
	a_val = optarg;
	break;
      case '?':
	if (optopt == 'c') {
	  fprintf (stderr, "Option -%c requires an argument.\n", optopt);
	  print_usage();
	} else if (isprint (optopt)) {
	  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	  print_usage();
	} else {
	  fprintf (stderr,
		   "Unknown option character `\\x%x'.\n",
		   optopt);
	}
	return 1;
      default:
	abort ();
      }
  printf("Option -a equals %s\n",a_val);


  /*
  
  parse_config("../testcfg.txt");
  setup_header(1, 1);
  
  sock = alloc_socket("192.168.254.1", 1812);
  start_timed_send(sock, len, 0.1, 10);
  */

  return 0;
}

