all: Search

Search : main.o functions.o
	g++ main.o functions.o -o Server

functions.o : functions.cpp functions.h
	g++ functions.cpp

main.o : main.cpp functions.h
	g++ main.cpp

clean:
	rm *.o Search

