CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP
COPTS    := -std=c++98 -pedantic-errors

# -- produce binary with 42's test code --

NAME     := 42-test
SRCS     := main.cpp
OBJS     := $(SRCS:%.cpp=%.o)
OBJS     := $(addprefix obj/, $(OBJS))
DEPS     := $(OBJS:.o=.d)
INCS     := $(addprefix -I, includes)

# -- produce binary used std container for compare output --

NAME_STD_COMP_OUT     := test_std_comp_output
SRCS_STD_COMP_OUT     := main_std_for_comp_output.cpp
OBJS_STD_COMP_OUT     := $(SRCS_STD_COMP_OUT:%.cpp=%.o)
OBJS_STD_COMP_OUT     := $(addprefix obj/, $(OBJS_STD_COMP_OUT))
DEPS_STD_COMP_OUT     := $(OBJS_STD_COMP_OUT:.o=.d)

# -- produce binary used ft container for compare output --

NAME_FT_COMP_OUT     := test_ft_comp_output
SRCS_FT_COMP_OUT     := main_ft_for_comp_output.cpp
OBJS_FT_COMP_OUT     := $(SRCS_FT_COMP_OUT:%.cpp=%.o)
OBJS_FT_COMP_OUT     := $(addprefix obj/, $(OBJS_FT_COMP_OUT))
DEPS_FT_COMP_OUT     := $(OBJS_FT_COMP_OUT:.o=.d)

# -- produce binary used std container for perf --

NAME_STD_PERF := test_std_perf
SRCS_STD_PERF := main_std_for_perf.cpp
OBJS_STD_PERF := $(SRCS_STD_PERF:%.cpp=%.o)
OBJS_STD_PERF := $(addprefix obj/, $(OBJS_STD_PERF))
DEPS_STD_PERF := $(OBJS_STD_PERF:.o=.d)

# -- produce binary used ft container for perf --

NAME_FT_PERF := test_ft_perf
SRCS_FT_PERF := main_ft_for_perf.cpp
OBJS_FT_PERF := $(SRCS_FT_PERF:%.cpp=%.o)
OBJS_FT_PERF := $(addprefix obj/, $(OBJS_FT_PERF))
DEPS_FT_PERF := $(OBJS_FT_PERF:.o=.d)

# -- build rule --

all: $(NAME) \
	 $(NAME_STD_COMP_OUT) \
	 $(NAME_FT_COMP_OUT) \
	 $(NAME_STD_PERF) \
	 $(NAME_FT_PERF)

$(NAME): $(OBJS)
	@if [ ! -d $(OBJ_DIR) ]; \
		then mkdir -p obj; \
	fi
	$(CXX) -o $(NAME) $(CXXFLAGS) $(COPTS) $(OBJS)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

-include $(DEPS)

# -- compare output test rule for std container --

$(NAME_STD_COMP_OUT): $(OBJS_STD_COMP_OUT)
	@if [ ! -d $(OBJ_DIR) ]; \
		then mkdir -p obj; \
	fi
	$(CXX) -o $(NAME_STD_COMP_OUT) $(CXXFLAGS) $(COPTS) $(OBJS_STD_COMP_OUT)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

-include $(DEPS_STD_COMP_OUT)

# -- compare output test rule for ft container --

$(NAME_FT_COMP_OUT): $(OBJS_FT_COMP_OUT)
	@if [ ! -d $(OBJ_DIR) ]; \
		then mkdir -p obj; \
	fi
	$(CXX) -o $(NAME_FT_COMP_OUT) $(CXXFLAGS) $(COPTS) $(OBJS_FT_COMP_OUT)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

-include $(DEPS_FT_COMP_OUT)

# -- perf test rule for std container --

$(NAME_STD_PERF): $(OBJS_STD_PERF)
	@if [ ! -d $(OBJ_DIR) ]; \
		then mkdir -p obj; \
	fi
	$(CXX) -o $(NAME_STD_PERF) $(CXXFLAGS) $(COPTS) $(OBJS_STD_PERF)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

-include $(DEPS_STD_PERF)

# -- perf test rule for ft container --

$(NAME_FT_PERF): $(OBJS_FT_PERF)
	@if [ ! -d $(OBJ_DIR) ]; \
		then mkdir -p obj; \
	fi
	$(CXX) -o $(NAME_FT_PERF) $(CXXFLAGS) $(COPTS) $(OBJS_FT_PERF)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) $(INCS) -o $@ -c $<

-include $(DEPS_FT_PERF)

# -- common rule --

clean:
	$(RM) $(OBJS) $(DEPS) \
		$(OBJS_STD_COMP_OUT) $(DEPS_STD_COMP_OUT) \
		$(OBJS_FT_COMP_OUT) $(DEPS_FT_COMP_OUT) \
		$(OBJS_STD_PERF) $(DEPS_STD_PERF) \
		$(OBJS_FT_PERF) $(DEPS_FT_PERF)

fclean: clean
	$(RM) $(NAME) $(NAME_STD_COMP_OUT) \
		$(NAME_FT_COMP_OUT)	\
		$(NAME_STD_PERF)	\
		$(NAME_FT_PERF)	\

re: fclean all

.PHONY: all clean fclean re

# -- other test rule --

comp: SHELL:=/bin/bash
comp: all
	diff <(./test_std_comp_output) <(./test_ft_comp_output)

perf: all
	./test_std_perf > std.perf
	./test_ft_perf > ft.perf
	paste ft.perf std.perf | awk '{print $$1 / $$2}'

test: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors -g -fsanitize=address $(INCS) main_orig.cpp && ./orig-test && $(RM) orig-test

bench: FORCE
	$(CXX) -o bench-test -std=c++11 -O0 -g -fsanitize=address $(INCS) main_bench.cpp && ./bench-test && $(RM) bench-test

leak-mac: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCS) main_orig.cpp && leaks --atExit -- ./orig-test && $(RM) orig-test

leak-linux: FORCE
	$(CXX) -o orig-test -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCS) main_orig.cpp && valgrind --leak-check=full ./orig-test && $(RM) orig-test

FORCE: ;

.PHONY: test leak-mac leak-linux FORCE

