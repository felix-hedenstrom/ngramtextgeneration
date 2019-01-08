all: ngram



ngram: ngramsearcher.cpp *.hpp
	g++ -o $@ $< -Wall -ljsoncpp -g

test: ngram
	./filler

valgrind: ngram
	valgrind ./filler  --track-origins=yes --leak-check=ful
