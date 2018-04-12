IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./obj
LDIR= ../lib

_DEPS=headers.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=jogo20perguntas.o funcoes.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

jogo20perguntas:	$(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
