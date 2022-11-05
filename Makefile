.PHONY: test
test:
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
