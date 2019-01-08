all: ngram test



ngram: ngramsearcher.cpp *.hpp
	g++ -o $@ $< -Wall -ljsoncpp


test: test.cpp *.hpp
	g++ -o $@ $< -Wall -g

%.o: %.cpp %.hpp
	g++ -o $@ -c -g $<


valgrind: test
	valgrind --show-reachable=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
