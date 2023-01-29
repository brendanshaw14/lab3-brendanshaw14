# Makefile for 'hashtable' module
#
# Brendan Shaw, CS5023W

OBJS = hashtabletest.o hashtable.o ../lib/file.o ../lib/mem.o ../set/set.o hash.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../lib/file.h ../set/set.h
hashtable.o: hashtable.h
../set/set.o: ../set/set.h
../lib/file.o: ../lib/file.h
hash.o: hash.h

test: hashtabletest
	./hashtabletest

.PHONY: test valgrind clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
