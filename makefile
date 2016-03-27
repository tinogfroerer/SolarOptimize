objects = obj/main.o obj/soltrack.o
CFLAGS += -I"./inc" -lgsl -lgslcblas -Wall -g

test : $(objects)
	gcc $(CFLAGS) $(objects) -o test

obj/main.o : src/main.c inc/soltrack.h
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/soltrack.o : src/soltrack.c inc/soltrack.h
	gcc $(CFLAGS) -c src/soltrack.c -o obj/soltrack.o

.PHONY : clean
clean :
	-rm test obj/**

