# UCM Makefile for C++ projects
# Angelo Kyrilov


NOT_ALLOWED = 'stl_vector|stl_list|stl_deque|std_stack|stl_queue|stl_set|stl_map|unordered_map|unordered_set|algorithmfwd.h'
DEP = $(shell g++ -M main.cpp | grep -E $(NOT_ALLOWED))


all:
ifneq ($(DEP),)
	@echo
	@echo Your project includes headers that are not allowed
	@echo Use \"make force\" to attempt the build anyway
	@echo
	@false
endif
	g++ main.cpp -g -I. -o app

.PHONY: force
force:
	g++ main.cpp -g -I. -o app


.PHONY: run
run:
	./app

.PHONY: test
test:
ifneq ($(DEP),)
	@echo
	@echo Your project includes headers that are not allowed
	@echo Use \"make force_test\" to attempt the test anyway
	@echo
	@false
endif
	g++ -g -I. test.cpp -o test
	clear && echo "Running all tests:" && ./test --output=color
	

.PHONY: force_test
force_test:
	g++ -g -I. test.cpp -o test
	clear && echo "Running all tests:" && ./test --output=color
	

.PHONY: pull
pull:
	@echo "There is nothing to pull in this project"


clean:
	rm -f app
	rm -f test
