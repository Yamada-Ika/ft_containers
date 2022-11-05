.PHONY: run
run: build
	cd build && GTEST_COLOR=1 ctest --output-on-failure

.PHONY: vector
vector: build
	cd build && ./test_vector --gtest_brief=1

.PHONY: stack
stack: build
	cd build && ./test_stack --gtest_brief=1

.PHONY: deque
deque: build
	cd build && ./test_deque --gtest_brief=1

.PHONY: tree
tree: build
	cd build && ./test_tree --gtest_brief=1

.PHONY: set
set: build
	cd build && ./test_set --gtest_brief=1

.PHONY: map
map: build
	cd build && ./test_map --gtest_brief=1

.PHONY: pair
pair: build
	cd build && ./test_pair --gtest_brief=1

.PHONY: build
build:
	cmake --build build

.PHONY: install
install:
	cmake -S . -B build
	make run
