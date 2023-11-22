all: prog big_int_test

big_int_test: big_int_test.cc big_int.h
	g++ -O0 -g -std=c++2b -o big_int_test big_int_test.cc

prog: main.cc
	g++ -O0 -g -std=c++2b -o prog main.cc

clean:
	rm -rf prog big_int_test
