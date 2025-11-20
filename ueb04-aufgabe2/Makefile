CXXFLAGS=-g -O2 -Wall -Wextra -fsanitize=address
CXXFLAGS+=-std=c++20
LINK.o=$(LINK.cc)

ti2sh:: ti2sh.o shell.o env.o parser.o sighnd.o
all:	 ti2sh

# switch off specific warnings for the regex header
parser.o:: CXXFLAGS+=-Wno-maybe-uninitialized

clean:
	-rm -f ti2sh *.o *~ core

