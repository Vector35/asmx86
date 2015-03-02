CC = gcc
CFLAGS = -std=gnu99 -Wall -Wshadow -Wimplicit -Wunused -Wstrict-aliasing=2

all: libasmx86.a

asmx86str.h: makeopstr.py asmx86.h
	python makeopstr.py asmx86.h asmx86str.h

asmx86.o: asmx86.c asmx86.h asmx86str.h
	$(CC) $(CFLAGS) -O3 -fPIC -o asmx86.o -c asmx86.c

libasmx86.a: asmx86.o
	rm -f libasmx86.a
	ar rc libasmx86.a asmx86.o

clean:
	rm -rf *.o *.a
