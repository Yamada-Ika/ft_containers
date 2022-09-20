.PHONY: run
run:
	cmake --build build
	cd build && ctest

.PHONY: install
install:
	cmake -S . -B build
	make run
