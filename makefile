CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline


all: controlador exemplo1 exemplo2 randomic minimax

controlador: controlador.c

exemplo1: campo.h campo.c exemplo1.c

exemplo2: campo.h campo.c exemplo2.c

randomic: campo.h campo.c randomic_player.c
	gcc $(CFLAGS) campo.h campo.c randomic_player.c $(LDLIBS) -o randomic

minimax: campo.h campo.c hashtable.c tree.c minimax.c
	gcc $(CFLAGS) campo.h campo.c list.h list.c hashtable.h hashtable.c tree.h tree.c minimax.c $(LDLIBS) -o minimax 

clean:
	rm -f controlador exemplo1 exemplo2 minimax random *.o
