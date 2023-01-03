test: FORCE
	c++ main_bonus.cpp && ./a.out

vector: FORCE
	c++ main_bonus.cpp && ./a.out vector

leak: FORCE
	c++ tmp.cpp && valgrind ./a.out

leak-vector: FORCE
	c++ main_bonus.cpp && valgrind --leak-check=full ./a.out vector

FORCE: ;