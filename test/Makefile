.PHONY: run
run: build
	cd build && GTEST_COLOR=1 ctest --output-on-failure

.PHONY: vector
vector: build
	cd build && ./test_vector --gtest_brief=1 2>/dev/null

.PHONY: stack
stack: build
	cd build && ./test_stack --gtest_brief=1 2>/dev/null

.PHONY: deque
deque: build
	cd build && ./test_deque --gtest_brief=1 2>/dev/null

.PHONY: build
build:
	cmake --build build

.PHONY: install
install:
	cmake -S . -B build
	make run
