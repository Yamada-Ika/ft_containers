CC			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -MMD -MP
COPTS		:= -std=c++98 -pedantic-errors

NAME	:= 42-test
SRCS	:= main.cpp
OBJS	:= $(SRCS:%.cpp=%.o)
OBJS	:= $(addprefix obj/, $(OBJS))
DEPS    := $(OBJS:.o=.d)
INCS    := $(addprefix -I, srcs) 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CXXFLAGS) $(COPTS) $(OBJS)

obj/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

clean:
	rm -rf $(OBJS) $(DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test: FORCE
	$(CC) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors main_bonus.cpp && ./orig-test

leak-mac: FORCE
	$(CC) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors main_bonus.cpp && leaks --atExit -- ./orig-test

leak-linux: FORCE
	$(CC) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors main_bonus.cpp && valgrind --leak-check=full ./orig-test

FORCE: ;

.PHONY: test leak-mac leak-linux FORCE

-include $(DEPS)
