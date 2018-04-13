IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./obj
LDIR= ../lib

_DEPS=headers.h catch.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=jogo20perguntas.o funcoes.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: jogo20perguntas testes

jogo20perguntas:	$(OBJ)
	gcc -o $@ $^ $(CFLAGS)

testes: testes.cpp funcoes.c
	g++ -std=c++11 -o testes -ftest-coverage -fprofile-arcs testes.cpp funcoes.c -I../include

.PHONY:	clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
