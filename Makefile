all: ngram test



ngram: ngramsearcher.cpp *.hpp
	g++ -o $@ $< -Wall -ljsoncpp

test: test.cpp *.hpp
	g++ -o $@ $< -Wall -ljsoncpp -g && ./test

valgrind: ngram
	valgrind ./ngram  --show-reachable=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -v
