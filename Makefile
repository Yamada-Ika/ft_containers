test: FORCE
	c++ main_bonus.cpp && ./a.out

vector: FORCE
	c++ main_bonus.cpp && ./a.out vector
deque: FORCE
	c++ main_bonus.cpp && ./a.out deque
stack: FORCE
	c++ main_bonus.cpp && ./a.out stack
tree: FORCE
	c++ main_bonus.cpp && ./a.out tree

leak: FORCE
	c++ -g tmp.cpp && valgrind --leak-check=full --track-origins=yes ./a.out 
leak-vector: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out vector
leak-deque: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out deque
leak-stack: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out stack
leak-tree: FORCE
	c++ -g main_bonus.cpp && valgrind --leak-check=full ./a.out tree


FORCE: ;