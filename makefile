CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline


all: controlador exemplo1 exemplo2 randomic 

controlador: controlador.c

exemplo1: campo.h campo.c exemplo1.c

exemplo2: campo.h campo.c exemplo2.c

randomic: campo.h campo.c randomic_player.c
	gcc $(CFLAGS) campo.h campo.c randomic_player.c $(LDLIBS) -o randomic


clean:
	rm -f controlador exemplo1 exemplo2 random *.o
