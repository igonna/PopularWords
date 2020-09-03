#include "analyzeText.h"
analyzeText::analyzeText(void) : buff(nullptr), string_array(nullptr), arrQuaWords(nullptr), skipString(""){}
analyzeText::~analyzeText(void)
{
	if(buff)
		delete[] buff;
}

std::string analyzeText::getStringFromFile(std::string fileName)const
{
	std::ifstream ifile(fileName);
	std::string strDataFromFile;
	if(ifile)
	{
		std::ostringstream ss;
		ss << ifile.rdbuf();
		strDataFromFile = ss.str();
	}
	ifile.close();
	return strDataFromFile;
}
bool analyzeText::isSpecialCharacter(char ch)const
{
	std::string specialCharacters = 
		"\'\"\?\\\a\b\f\n\r\t\v!#$%&()*+./:;<=>?@[]^_-{}|~,0123456789";
	for(unsigned int step = 0; step < specialCharacters.size(); ++step)
		if(ch == specialCharacters[step])
			return true;
	return false;
}
bool analyzeText::isAsciiChar(char ch)const
{
	if(static_cast<int>(ch) >= 0 && static_cast<int>(ch) <= 127)
		return true;
	return false;
}
char analyzeText::asciiToLower(char ch)const
{
	if(static_cast<int>(ch) >= 65 && static_cast<int>(ch) <= 90)
		ch = tolower(ch);
	return ch;
}
std::string analyzeText::stringToLower(std::string str)const
{
	for(unsigned int step = 0; step < str.size(); ++step)
	{
		if(isAsciiChar(str[step]))
			str[step] = asciiToLower(str[step]);
	}
	return str;
}


std::string analyzeText::delExtraSymbols(std::string str)
{
	str = stringToLower(str);
	for(unsigned int character = 0; character < str.size(); ++character)
	{
		if(isSpecialCharacter(str[character]))
		{
			if(character > 1 && str[character - 1] == ' ')
				str[character] = ' ';
			if(str[character] == '\'')
				continue;
			str[character] = ' ';
		}
	}
	return str;
}

std::string analyzeText::delExtraSpaces(std::string str)
{
	unsigned int step = 0, count = 0;
	std::string tmp_str;
	tmp_str.resize(str.size());
	for(step = 0; step < str.size(); ++step)
	{
		if(!(str[step] == ' ' && str[step + 1] == ' '))
		{
			tmp_str[count] += str[step];
			++count;
		}
	}
	if(tmp_str[count - 1] == ' ')
		tmp_str.erase(count - 1);
	if(tmp_str[0] == ' ')
	{
		for(step = 0; step < tmp_str.size() - 1; ++step)
			tmp_str[step] = tmp_str[step + 1];
		tmp_str.erase(tmp_str.size() - 1);
	}
        return tmp_str;
}

unsigned int analyzeText::totalWords(std::string str)
{
	quantity_words = 0;
	for(unsigned int step = 0; step < str.size(); ++step)
	{
		if(str[step] == ' ')
			++quantity_words;
	}
	return ++quantity_words;
}

void analyzeText::fromStringToArray(const char* str, char** arr, unsigned int quantityWords, unsigned int wordSize)const
{
	unsigned int margin = 0;
	unsigned int numberOfWord;

	for (numberOfWord = 0; numberOfWord < quantityWords; ++numberOfWord)
	{
		for (unsigned int step = 0; step < wordSize; ++step)
		{
			if (str[margin + step] == ' ')
			{
				margin += step + 1;
				break;
			}
			arr[numberOfWord][step] = str[step + margin];
			arr[numberOfWord][step + 1] = '\0';
		}
	}
}


unsigned int analyzeText::theBiggestWordInString(std::string& str)const
{
	unsigned int theBiggestWord = 0;
	unsigned int thisWordSize = 0;
	unsigned int stringSize = str.size();
	for (unsigned int step = 0; step <= stringSize; ++step)
	{
		if (str[step] == ' ' || step == stringSize)
		{
			if(theBiggestWord < thisWordSize) theBiggestWord = thisWordSize;
			thisWordSize = 0;
			continue;
		}
		++thisWordSize;
	}
	return theBiggestWord;
}


std::string analyzeText::delExtraWords(char** arr, unsigned int* arrQuantityWords, unsigned int quantityWords)const
{
	std::string tmpStr;
	std::string wordsWithSizeOne[2] = {"i", "a"};
    	for(unsigned int wordNumber = 0; wordNumber < quantityWords; ++wordNumber)
    	{
        	tmpStr = arr[wordNumber];
        	if(arr[wordNumber] == skipString)
        	{
            		arrQuantityWords[wordNumber] = 0;
            		continue;
        	}
		arrQuantityWords[wordNumber] = delThisWordGetQuantity(tmpStr, arr, quantityWords);
	}
	for(unsigned int wordNumber = 0; wordNumber < quantityWords; ++wordNumber)
		if(strlen(arr[wordNumber]) == 1 && arr[wordNumber] != wordsWithSizeOne[0] && arr[wordNumber] != wordsWithSizeOne[1])
		{
			strcpy(arr[wordNumber], "");
			arrQuantityWords[wordNumber] = 0;
		}
	return skipString;
}


void analyzeText::swapStrings(char* str_1, char* str_2, unsigned int wordSize)const
{
	char* tmpStr = new char[wordSize];
	strcpy(tmpStr, str_1);
	strcpy(str_1, str_2);
	strcpy(str_2, tmpStr);
	delete[] tmpStr;
}

void analyzeText::swapNumbers(unsigned int* a, unsigned int* b)
{
	*a ^= *b;
	*b = *a ^ *b;
	*a ^= *b;
}


void analyzeText::swapNumStr(unsigned int *a, unsigned int *b, char* str_1, char* str_2)
{
	swapNumbers(a, b);
	swapStringsWithoutSize(str_1, str_2);
}

void analyzeText::swapStringsWithoutSize(char* str_1, char* str_2)
{
	char* tmp_str = new char[sizeof(str_1) + 1];
	strcpy(tmp_str, str_1);
	strcpy(str_1, str_2);
	strcpy(str_2, tmp_str);
	delete[] tmp_str;
}

int analyzeText::partition(unsigned int* array, int low, int high, char** carr)
{
	int pivot = array[high];
	int i = (low - 1);
	for (int j = low; j < high; ++j)
	{
		if (array[j] <= static_cast<unsigned int>(pivot))
		{
			++i;
			swapNumStr(&array[i], &array[j], carr[i], carr[j]);
		}
	}
	swapNumStr(&array[i + 1], &array[high], carr[i + 1], carr[high]);
	return (i + 1);
}

void analyzeText::quickSort(unsigned int* array, int low, int high, char** carr)
{
	if (low < high)
	{
		int pi = partition(array, low, high, carr);
		quickSort(array, low, pi - 1, carr);
		quickSort(array, pi + 1, high, carr);
	}
}

void analyzeText::synchronizedBubbleSort(char** arr, unsigned int* arrQuantityWords, unsigned int quantityWords, unsigned int wordSize)const
{
	char* tmpStr = new char[wordSize];
	for (unsigned int a = 0; a < quantityWords; ++a)
	{
    		for (unsigned int b = 0; b < quantityWords - 1; ++b)
    		{
    			if (arrQuantityWords[b] < arrQuantityWords[b + 1])
			{
				arrQuantityWords[b + 1] ^= arrQuantityWords[b];
				arrQuantityWords[b] = arrQuantityWords[b + 1] ^ arrQuantityWords[b];
				arrQuantityWords[b + 1] ^= arrQuantityWords[b];

				strcpy(tmpStr, arr[b]);
				strcpy(arr[b], arr[b + 1]);
				strcpy(arr[b + 1], tmpStr);
            		}
        	}
    	}
	delete[] tmpStr;
}


unsigned int analyzeText::sizeOfMaxWord(char** arr, unsigned int quantityWords)const
{
    unsigned int maxSize = 0;
    for (unsigned int step = 0; step < quantityWords; ++step)
        if (strlen(arr[0]) > strlen(arr[step]))
            maxSize = strlen(arr[0]);
        else
            maxSize = strlen(arr[step]);
    return maxSize + 1;
}


unsigned int analyzeText::countEqualWords(std::string& str, char** wordsArray, unsigned int wordsQuantity)const
{
	unsigned int wordCount = 0;
	for(unsigned int wordNumber = 0; wordNumber < wordsQuantity; wordNumber++)
	{
		if(str == wordsArray[wordNumber])
		{
			wordCount++;
		}
	}
	return wordCount;
}


unsigned int analyzeText::delThisWordGetQuantity(std::string& str, char** wordsArray, unsigned int wordsQuantity)const
{
	unsigned int hotWord = 0;
	for(unsigned int wordNumber = 0; wordNumber < wordsQuantity; ++wordNumber)
	{
		if(str == wordsArray[wordNumber])
		{
			++hotWord;
		}
		if(hotWord > 1)
		{
			if(str == wordsArray[wordNumber])
			{
				strcpy(wordsArray[wordNumber],  "");
			}
		}
	}
	return hotWord;
}

std::string analyzeText::outDataToFile(std::string fileName, char** arr, unsigned int array_size)
{
	fileName = delExtraSymbols(fileName);
	fileName = delExtraSpaces(fileName);
	unsigned int theBiggestWord = theBiggestWordInString(fileName) + 1;
	unsigned int tWords = totalWords(fileName);

	char** fileNameArr = new char*[tWords];
        for(unsigned int step = 0; step < tWords; ++step)
                fileNameArr[step] = new char[theBiggestWord];

	fromStringToArray(fileName.c_str(), fileNameArr, tWords, theBiggestWord);
	fileName = fileNameArr[0];
	fileName += ".pw.txt";
	std::ofstream ofile(fileName);
	if(!ofile)
	{
		std::cerr << "error file open" << std::endl;
		ofile.close();
		return "";
	}
	for(unsigned int step = 0; step < array_size; step++)
	{
		if(arr[step] == skipString)
			continue;
		ofile << arr[step] << std::endl;
	}
	ofile.close();
	for(unsigned int step = 0; step < tWords; ++step)
		delete[] fileNameArr[step];
	delete[] fileNameArr;
	return fileName;
}
