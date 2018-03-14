Differentiator: diff.o Optim.o main.o
	g++ Diff.o Optim.o main.o -o Differentiator
diff.o: Diff.cpp Diff.hpp
	g++ -c Diff.cpp
Optim.o: Optim.cpp Optim.hpp
	g++ -c Optim.cpp
main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o Differentiator
