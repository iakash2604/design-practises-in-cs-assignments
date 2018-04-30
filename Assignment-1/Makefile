all: a.out

a.out: main.o Funcky.o
	 g++ main.o Funcky.o

main.o: main.cpp
	 g++ -c main.cpp

Funcky.o: Funcky.cpp
	 g++ -c Funcky.cpp
     
clean:
	 rm Funcky.o main.o