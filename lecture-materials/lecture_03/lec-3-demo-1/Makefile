# UCM Makefile for C++ projects
# Angelo Kyrilov


all:
	g++ main.cpp -g -o app

.PHONY: test
test:
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
	@./app

.PHONY: clean
clean:
	@rm -f app
	@rm -f test

