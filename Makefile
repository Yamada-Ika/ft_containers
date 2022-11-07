.PHONY: run
run:
	make -C test run

.PHONY: tree
tree:
	make -C test tree

.PHONY: set
set:
	make -C test set

.PHONY: map
map:
	make -C test map

.PHONY: pair
pair:
	make -C test pair

.PHONY: stack
stack:
	make -C test stack

.PHONY: deque
deque:
	make -C test deque
