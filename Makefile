Differentiator: diff.o Optim.o main.o print_tree.o
	g++ Diff.o Optim.o print_tree.o main.o -o Differentiator

print_scanf_tree.o: print_tree.cpp
	g++ -c print_tree.cpp
diff.o: Diff.cpp
	g++ -c Diff.cpp
Optim.o: Optim.cpp
	g++ -c Optim.cpp
main.o: main.cpp
	g++ -c main.cpp
clean: 
	rm -rf *.o Differentiator

