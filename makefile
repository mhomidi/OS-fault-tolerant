all: Search

Search : main.o functions.o
	g++ main.o functions.o -o Search

functions.o : functions.cpp functions.h
	g++ -c functions.cpp

main.o : main.cpp functions.h
	g++ -c main.cpp

clean:
	rm *.o Search

