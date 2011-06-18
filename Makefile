IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -Wall -ggdb

ODIR=.
LDIR =.

LIBS=-lm -lcrypto -framework CoreFoundation

_DEPS = radat.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = packet.o parse_cnf.o network.o timer_mac.o help.o radat.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

radat: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ core $(INCDIR)/*~ *.dSYM radat
