#include "includes.h"
#include "analyzeText.h"
auto STime = std::chrono::steady_clock::now();
inline void initSTime(void)
{
	STime = std::chrono::steady_clock::now();
}
inline void showETime(void)
{
	auto ETime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = ETime - STime;
	std::cout << std::fixed << std::setprecision(2);
//	std::cout << "\t(" << elapsed_seconds.count() << "s)." << std::endl;
	std::cout << std::endl;
}
int main(int argc, const char** argv)
{
	//processing argv values
	if(argc != 2)
	{
		std::cerr << "few files" << std::endl;
		std::cout << "./PopularWords --help" << std::endl;
		return 1;
	}
	if(std::string(argv[1]) == "--help")
	{
		std::cout << "./PopularWords [file name]" << std::endl;
		return 0;
	}
	//determine the start time of the program
	auto timeOfStart = std::chrono::steady_clock::now();
	//Creating data
	std::cout << "Creating data. Step (1/12).";
	initSTime();
	std::ofstream ofile;
	std::string str;
	analyzeText textAnalyser;
	showETime();

	//processing string
	std::cout << "Getting string from file. Step (2/12).";
	initSTime();
	str = textAnalyser.getStringFromFile(argv[1]);
	showETime();
	std::cout << "Removing extra symbols. Step (3/12).";
	initSTime();
	str = textAnalyser.delExtraSymbols(str);
	showETime();
	std::cout << "Removing extra spaces. Step (4/12).";
	initSTime();
	str = textAnalyser.delExtraSpaces(str);
	showETime();
	
	//counting data for allocting memory
	std::cout << "Counting total words. Step (5/12).";
	initSTime();
	unsigned int array_size = textAnalyser.totalWords(str);
	showETime();
	std::cout << "Searching the biggest word. Step (6/12).";
	initSTime();
	unsigned int word_size = textAnalyser.theBiggestWordInString(str) + 1;
	showETime();

	//allocating memory for array which will be using for copy string to array
	std::cout << "Allocating memory. Step (7/12).";
	initSTime();
	char** arr = new char*[array_size];
	for(unsigned int step = 0; step < array_size; ++step)
		arr[step] = new char[word_size];

	//allocating memory for array which will be using for count same words
	unsigned int* arrQuantityWords = new unsigned int[array_size];
	for(unsigned int step = 0; step < array_size; ++step)
		arrQuantityWords[step] = 0;
	showETime();

	//copying string to array
	std::cout << "Converting string to array. Step (8/12).";
	initSTime();
	textAnalyser.fromStringToArray(str.c_str(), arr, array_size, word_size);
	showETime();

	//removing extra words
	std::cout << "Removing extra words. Step (9/12).";
	initSTime();	
	textAnalyser.delExtraWords(arr, arrQuantityWords, array_size);
	showETime();

	//sorting array
	std::cout << "Sorting words. Step (10/12).";
	initSTime();
	textAnalyser.synchronizedBubbleSort(arr, arrQuantityWords, array_size, word_size);
//	textAnalyser.quickSort(arrQuantityWords, 0, array_size - 1, arr);
	showETime();

	//output array to file
	std::cout << "Outputing data to file. Step (11/12).";
	initSTime();
	std::string nameOfOutputFile = textAnalyser.outDataToFile(argv[1], arr, array_size);
	showETime();

	//cleaning memory
	std::cout << "Cleaning memory. Step (12/12).";
	initSTime();
	for(unsigned int step = 0; step < array_size; ++step)
		delete[] arr[step];
	delete[] arr;
	delete[] arrQuantityWords;
	showETime();

	//output user info
	std::cout << std::endl << "Complete." << std::endl;
	std::cout << "Output file: " << nameOfOutputFile << std::endl;
	auto timeOfEnd = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = timeOfEnd - timeOfStart;
	std::cout << "Total spent time: " << elapsed_seconds.count() << "s" << std::endl;
	return 0;
}
