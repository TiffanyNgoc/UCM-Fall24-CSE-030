all:
	g++ main.cpp -g -I. -o app

.PHONY: run
run:
	@g++ main.cpp -g -I. -o app
	@./app

.PHONY: pull
pull:
	echo There is nothing to pull in this project

.PHONY: test
test:
	g++ -I. test.cpp -o test
	clear && echo "Running all tests:" && ./test --output=color
	@rm -f test_all

.PHONY: clean
clean:
	rm -f app
	rm -f test
