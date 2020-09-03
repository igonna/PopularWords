analyzeText.o: analyzeText.cpp analyzeText.h
	g++ -g -Wall -c analyzeText.cpp -o analyzeText.o
PopularWords.out: main.cpp analyzeText.o
	g++ -g -Wall main.cpp analyzeText.o -o PopularWords.out
