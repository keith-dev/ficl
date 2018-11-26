#----------------------------------------------------------------------------
.POSIX:

MAJOR = 4
MINOR = 1.0

SRCS = dictionary.c system.c fileaccess.c float.c double.c prefix.c search.c softcore.c stack.c tools.c vm.c primitives.c bit.c lzuncompress.c ficlplatform/unix.c utility.c hash.c callback.c word.c extras.c
HEADERS = ficl.h ficlplatform/unix.h
OBJS = $(SRCS:.c=.o)
SHOBJS = $(SRCS:.c=.os)

SHFLAGS += -fPIC
CFLAGS += -I.

LIB = ar cr
RANLIB = ranlib

all: lib ficl main

clean:
	rm -f $(OBJS) $(SHOBJS) main.o main ficl libficl.a libficl.so libficl.so.$(MAJOR) libficl.so.$(MAJOR).$(MINOR)

ficl: main.o $(HEADERS) libficl.a
	$(CC) main.o -o ficl $(LDADD) libficl.a -lm

main: main.o ficl.h libficl.so
	$(CC) main.o -o main $(LDADD) libficl.so -lm

lib: libficl.a libficl.so

libficl.a: $(OBJS)
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
