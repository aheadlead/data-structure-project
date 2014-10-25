main: List_Sq.o List_L.o main.o
	gcc List_Sq.o List_L.o main.o -o main -O2 -g

List_Sq.o: List_Sq.c List_Sq.h
	gcc -c List_Sq.c -O2 -g -o List_Sq.o

List_L.o: List_L.c List_L.h
	gcc -c List_L.c -O2 -g -o List_L.o

main.o: main.c
	gcc -c main.c -O2 -g -o main.o

clean:
	-rm main
	-rm *.o
