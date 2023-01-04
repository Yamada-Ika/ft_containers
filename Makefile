test: FORCE
	c++ main_bonus.cpp && ./a.out
test-42: FORCE
	c++ main.cpp && ./a.out 4242

vector: FORCE
	c++ main_bonus.cpp && ./a.out vector
deque: FORCE
	c++ main_bonus.cpp && ./a.out deque
stack: FORCE
	c++ main_bonus.cpp && ./a.out stack
tree: FORCE
	c++ main_bonus.cpp && ./a.out tree
set: FORCE
	c++ main_bonus.cpp && ./a.out set
map: FORCE
	c++ main_bonus.cpp && ./a.out map

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
leak-set: FORCE
	c++ -g main_bonus.cpp && valgrind --leak-check=full ./a.out set
leak-map: FORCE
	c++ -g main_bonus.cpp && valgrind --leak-check=full ./a.out map
leak-all: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out all
leak-mac-all: FORCE
	c++ main_bonus.cpp && leaks --atExit -- ./a.out all

FORCE: ;