CC=g++
CFLAGS= -Wall -Werror -ansi -pedantic
LDFLAGS=
SOURCES= ./src/rshell.cpp
OUTFILE = bin/rshell



all: rshell

rshell:
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $(SOURCES) \
	-o $(OUTFILE)


