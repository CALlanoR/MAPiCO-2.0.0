# plugins
CC = gcc
CFLAGS = -g -O2 -std=c99 -fPIC -shared -ldl

PLGINS := $(wildcard *.c)
OBJSO := $(patsubst %.c,%.so,$(PLGINS))

INCLUDE = -I../include/ -I../constsys/
LIBS =
STLIBS = ../mapico/.libs/libmapico.a

all: $(OBJSO)

%.so: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $@ $< $(STLIBS)


clean:
	rm -f *.so

distclean:
	rm -f *.so config.* Makefile
