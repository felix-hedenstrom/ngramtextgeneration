all: ngram test

.PHONY:
	valgrind test

ngram: ngramsearcher.cpp *.hpp
	g++ -o $@ $< -Wall -ljsoncpp

test: test.out
	./test.out

test.out: test.cpp *.hpp
	g++ -o $@ $< -Wall -g

%.o: %.cpp %.hpp
	g++ -o $@ -c -g $<


valgrind: test
	valgrind --show-reachable=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
