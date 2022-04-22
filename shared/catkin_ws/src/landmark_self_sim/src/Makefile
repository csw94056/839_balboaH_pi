DBG = -g
OPT = -O2
WARN = -W -Wall -Wcast-qual -Wcast-align

CC = gcc
CFLAGS = -pipe $(DBG) $(WARN) $(OPT)
LINK = gcc

SRC = findlm.c landmark.c digits.c barcode.c findlines.c mcimg.c
OBJ = $(SRC:.c=.o)
BIN = findlm
INC = 

all: $(BIN)

findlm: findlm.o landmark.o digits.o barcode.o findlines.o mcimg.o
	$(LINK) -o findlm findlm.o landmark.o digits.o \
	barcode.o findlines.o mcimg.o -lm

clean:
	/bin/rm -f $(OBJ) *.bak

depend:
	makedepend -- $(CFLAGS) -- $(SRC)

# DO NOT DELETE THIS LINE -- make depend depends on it.
