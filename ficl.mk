#----------------------------------------------------------------------------
MAJOR = 3
MINOR = 0.3

OBJS = $(SRCS:.c=.o)
SHOBJS = $(SRCS:.c=.os)

SHFLAGS += -fPIC
CFLAGS = -std=c99 -pedantic -I.

LIB = ar cr
RANLIB = ranlib

all: lib ficl main

clean:
	rm -f $(OBJS) $(SHOBJS) testmain.o main ficl libficl.a libficl.so libficl.so.$(MAJOR) libficl.so.$(MAJOR).$(MINOR)

ficl: testmain.o $(HEADERS) libficl.a
	$(CC) testmain.o -o ficl $(LDADD) libficl.a -lm

main: testmain.o ficl.h libficl.so
	$(CC) testmain.o -o main $(LDADD) libficl.so -lm

lib: libficl.a libficl.so

libficl.a: $(HEADERS) $(OBJS)
	$(LIB) libficl.a $(OBJS)
	$(RANLIB) libficl.a

libficl.so: libficl.so.$(MAJOR)
	ln -sf libficl.so.$(MAJOR) libficl.so

libficl.so.$(MAJOR): libficl.so.$(MAJOR).$(MINOR)
	ln -sf libficl.so.$(MAJOR).$(MINOR) libficl.so.$(MAJOR)

libficl.so.$(MAJOR).$(MINOR): $(SHOBJS)
	$(CC) -shared -Wl,-soname,libficl.so.$(MAJOR).$(MINOR) -o libficl.so.$(MAJOR).$(MINOR) $(SHOBJS)

#----------------------------------------------------------------------------
.SUFFIXES: .c .o .os

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.c.os:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SHFLAGS) -c $< -o $@
