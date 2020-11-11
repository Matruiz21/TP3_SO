.PHONY: clean all server client

all: clean server client

GCCFLAGS=-g3 -ggdb -m64 -fno-exceptions -Wall -ffreestanding -fno-common -std=c99 -fno-stack-protector
GCC=gcc

server:
	$(GCC) $(GCCFLAGS)  server.c random.c -o server -lm

client:
	$(GCC) $(GCCFLAGS) client.c -o client

clean:
	rm -rf *.o server client