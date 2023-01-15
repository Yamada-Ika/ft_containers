CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP
COPTS    := -std=c++98 -pedantic-errors

NAME     := 42-test
SRCS     := main.cpp
OBJS     := $(SRCS:%.cpp=%.o)
OBJS     := $(addprefix obj/, $(OBJS))
DEPS     := $(OBJS:.o=.d)
INCS     := $(addprefix -I, srcs) 

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(CXXFLAGS) $(COPTS) $(OBJS)

obj/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

test: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCS) main_bonus.cpp && ./orig-test && $(RM) orig-test

leak-mac: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCS) main_bonus.cpp && leaks --atExit -- ./orig-test && $(RM) orig-test

leak-linux: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCS) main_bonus.cpp && valgrind --leak-check=full ./orig-test && $(RM) orig-test

FORCE: ;

.PHONY: test leak-mac leak-linux FORCE
