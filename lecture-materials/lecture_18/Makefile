# UCM Makefile for C++ projects
# Angelo Kyrilov

NOT_ALLOWED = 'stl_vector|stl_list|stl_deque|std_stack|stl_queue|stl_set|stl_map|unordered_map|unordered_set'
DEP = $(shell g++ -M main.cpp | grep -E $(NOT_ALLOWED))

all:
ifneq ($(DEP),)
	@echo
	@echo Your project includes headers that are not allowed
	@echo Use \"make force\" to attempt the build anyway
	@echo
	@false
endif
	g++ main.cpp -g -o app

force:
	g++ main.cpp -g -o app

.PHONY: test
test:
ifneq ($(DEP),)
	@echo
	@echo Your project includes headers that are not allowed
	@echo Use \"make force_test\" to attempt the test anyway
	@echo
	@false
endif
	g++ -g test.cpp -o test
	clear && echo "Running all tests:" && ./test --output=color

.PHONY: force_test
force_test:
	g++ -g test.cpp -o test
	clear && echo "Running all tests:" && ./test --output=color

.PHONY: pull
pull:
ifeq ($(shell git rev-parse --is-inside-work-tree 2>/dev/null),true)
	@git reset --hard
	@git clean -fdx
	@git pull --ff-only
else
	@echo "No git repository found in the current directory"
endif

.PHONY: run
run:
	@g++ main.cpp -g -o app	
	@./app

.PHONY: clean
clean:
	rm -f app
	rm -f test

