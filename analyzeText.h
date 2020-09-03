#include "includes.h"

class analyzeText
{
private:
	char* buff;
	unsigned int quantity_words;
	std::string* string_array;
	unsigned int* arrQuaWords;
	std::string skipString;
public:
	analyzeText(void);
	~analyzeText(void);
	std::string getStringFromFile(std::string fileName)const;
	bool isSpecialCharacter(char ch)const;
	bool isAsciiChar(char ch)const;
	char asciiToLower(char ch)const;
	std::string delExtraSymbols(std::string);
	std::string delExtraSpaces(std::string);
	unsigned int totalWords(std::string);
	std::string stringToLower(std::string str)const;
	void fromStringToArray(const char*, char**, unsigned int, unsigned int)const;
	unsigned int theBiggestWordInString(std::string&)const;
	std::string delExtraWords(char**, unsigned int*, unsigned int)const;
	inline void swapStrings(char*, char*, unsigned int)const;
	inline void swapNumbers(unsigned int* a, unsigned int* b);
	inline void swapNumStr(unsigned int *a, unsigned int *b, char* str_1, char* str_2);
	inline void swapStringsWithoutSize(char* str_1, char* str_2);
	int partition(unsigned int* array, int low, int high, char** carr);
	void quickSort(unsigned int* array, int low, int high, char** carr);
	void synchronizedBubbleSort(char**, unsigned int*, unsigned int, unsigned int)const;
	inline void swapNumbers(unsigned int*, unsigned int*)const;
	unsigned int sizeOfMaxWord(char** arr, unsigned int quantityWords)const;
	unsigned int countEqualWords(std::string&, char**, unsigned int)const;
	unsigned int delThisWordGetQuantity(std::string&, char**, unsigned int)const;
	std::string outDataToFile(std::string fileName, char** arr, unsigned int array_size);
};
