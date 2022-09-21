.PHONY: run
run:
	cmake --build build
	cd build && GTEST_COLOR=1 ctest --verbose

.PHONY: install
install:
	cmake -S . -B build
	make run
