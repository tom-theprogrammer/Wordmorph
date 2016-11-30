
#Compilador a utilizar:
COMPILER = gcc

#Flags a utilizar:
FLAGS = -O3 -ansi -pedantic

#Programa resultante:
TARGET = wordmorph


wordmorph: main.o file.o list.o ordenador.o libertador.o grafo.o fila_prioritaria.o
	$(COMPILER) $(FLAGS) -o wordmorph main.o file.o list.o ordenador.o libertador.o grafo.o fila_prioritaria.o && rm -r *.o


file.o: file.c estrt_const_bibliot.h prototipos.h
	$(COMPILER) -c $(FLAGS) file.c

main.o: main.c estrt_const_bibliot.h prototipos.h
	$(COMPILER) -c $(FLAGS) main.c

list.o: list.c list.h
	$(COMPILER) -c $(FLAGS) list.c

ordenador.o: ordenador.c ordenador.h prototipos.h
	$(COMPILER) -c $(FLAGS) ordenador.c

libertador.o: libertador.c estrt_const_bibliot.h prototipos.h
	$(COMPILER) -c $(FLAGS) libertador.c

grafo.o: grafo.c estrt_const_bibliot.h prototipos.h
	$(COMPILER) -c $(FLAGS) grafo.c

fila_prioritaria.o: fila_prioritaria.c estrt_const_bibliot.h prototipos.h 
	$(COMPILER) -c $(FLAGS) fila_prioritaria.c

clean:
	rm -f *.o core a.out *~ wordmorph
