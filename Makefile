#Sample Makefile for Malloc
CC=gcc
CFLAGS=-g -O0 -w -fPIC #-Werror -Wall

TESTS = test t-test1
HEADERS= #Add list of header files

all:	${TESTS} libmalloc.so

clean:
	rm -rf *.o *.so ${TESTS}

lib: libmalloc.so


libmalloc.so: mallib.o    #add other sources here
	$(CC) $(CFLAGS) -shared -Wl,--unresolved-symbols=ignore-all $^ -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lpthread

# For every XYZ.c file, generate XYZ.o.
%.o: %.c ${HEADERS}
	$(CC) $< $(CFLAGS) --static -c -o $@

check1:	libmalloc.so test t-test1.o
	LD_PRELOAD=`pwd`/libmalloc.so ./t-test1

check:	libmalloc.so ${TESTS}
	LD_PRELOAD=`pwd`/libmalloc.so ./test
