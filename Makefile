test: FORCE
	c++ main_bonus.cpp && ./a.out

vector: FORCE
	c++ main_bonus.cpp && ./a.out vector

leak: FORCE
	c++ tmp.cpp && valgrind --leak-check=full ./a.out 

leak-vector: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out vector

leak-deque: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out deque

leak-stack: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out stack

FORCE: ;