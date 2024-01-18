build:
	rm -f program.out
	g++ -g -std=c++20 -Wall main.cpp -o program.out
	
run:
	./program.out

clean:
	rm -f ./program.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.out
