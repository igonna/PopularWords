analyzeText.o: analyzeText.cpp analyzeText.h
	g++ -g -Wall -c analyzeText.cpp -o analyzeText.o
PopularWords: main.cpp analyzeText.o
	g++ -g -Wall -pthread main.cpp analyzeText.o -o PopularWords
