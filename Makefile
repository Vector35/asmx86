CC = gcc
CXX = g++
CFLAGS = -std=gnu99 -Wall -Wshadow -Wimplicit -Wunused -Wstrict-aliasing=2
CXXFLAGS = -std=gnu++98 -Wall -Wshadow -Wimplicit -Wunused -Wstrict-aliasing=2

all: libasmx86.a

makeopstr: makeopstr.cpp
	$(CXX) $(CXXFLAGS) -o makeopstr makeopstr.cpp

asmx86str.h: makeopstr asmx86.h
	./makeopstr asmx86.h asmx86str.h

asmx86.o: asmx86.c asmx86.h asmx86str.h
	$(CC) $(CFLAGS) -O3 -fPIC -o asmx86.o -c asmx86.c

libasmx86.a: asmx86.o
	rm -f libasmx86.a
	ar rc libasmx86.a asmx86.o

clean:
	rm -rf *.o *.a asmx86str.h makeopstr
