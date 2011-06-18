#include <stdio.h>

const double VERSION = 1.0;

void print_usage(void)
{

  fprintf(stdout, 
	  "usage: radat -s<secret> -d<dest> -p<port> -i<interval> -r<repetitions> -a<attributes>\n\n"
	  "\t-s<secret>\t Radius secret string\n"
	  "\t-d<dest>\t IP address of Radius server\n"
	  "\t-p<port>\t UDP Port of Radius server\n"
	  "\t-i<interval>\t Interval between requests (miliseconds)\n"
	  "\t-r<repetitions>\t Number of packets to send (0 - infinity)\n"
	  "\t-a<attributes>\t File containing radius attributes which should be sent in Radius packet\n");
}

void print_version(void)
{
  fprintf(stdout, "radat - Radius stress testing tool. Copyright by Ivan Ostres, 2011.  Version %1.1f\n", VERSION);
}
