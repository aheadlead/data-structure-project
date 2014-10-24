main: List.o main.o
	gcc List.o main.o -o main -O2 -g

List.o: List.c List.h
	gcc -c List.c -O2 -g -o List.o

main.o: main.c
	gcc -c main.c -O2 -g -o main.o

clean:
	-rm main
	-rm *.o
