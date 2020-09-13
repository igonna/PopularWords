#include "includes.h"
#include "analyzeText.h"

#define LINUX
//#define WINDOWS
#ifdef LINUX
#define CLEAN_WINDOW_COMMAND "clear"
#endif
#ifdef WINDOWS
#define CLEAN_WINDOW_COMMAND
#endif

void stateOutput(std::string* str, bool* isContinue);
auto STime = std::chrono::steady_clock::now();
void initSTime(void);
void showETime(void);

int main(int argc, const char** argv)
{	
	std::string stateString = "Processing";
        bool isOutputThreadContinue = true;
        std::thread thread_1(stateOutput, &stateString, &isOutputThreadContinue);
	
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
	stateString = "Creating data. step(1/10)";
	std::ofstream ofile;
	std::string str;
	analyzeText textAnalyser;

	//processing string
	stateString = "Getting string from file. step(2/10)";
	str = textAnalyser.getStringFromFile(argv[1]);
	stateString = "Removing extra symbols. step(3/10)";
	str = textAnalyser.delExtraSymbols(str);
	stateString = "Removing extra spaces. step(4/10)";
	str = textAnalyser.delExtraSpaces(str);
	
	//counting data for allocting memory
	stateString = "Counting total words. step(5/10)";
	unsigned int array_size = textAnalyser.totalWords(str);
	stateString = "Searching the biggest word. step(6/10)";
	unsigned int word_size = textAnalyser.theBiggestWordInString(str) + 1;

	//allocating memory for array which will be using for copy string to array
	stateString = "Allocating memory. step(7/10)";
	char** arr = new char*[array_size];
	for(unsigned int step = 0; step < array_size; ++step)
		arr[step] = new char[word_size];

	//allocating memory for array which will be using for count same words
	unsigned int* arrQuantityWords = new unsigned int[array_size];
	for(unsigned int step = 0; step < array_size; ++step)
		arrQuantityWords[step] = 0;

	//copying string to array
	stateString = "Converting string to array. step(8/10)";
	textAnalyser.fromStringToArray(str.c_str(), arr, array_size, word_size);

	//removing extra words
	stateString = "Removing extra words. step(9/10)";	
	textAnalyser.delExtraWords(arr, arrQuantityWords, array_size);

	//sorting array
	stateString = "Sorting words. step(10/10)";
	textAnalyser.synchronizedBubbleSort(arr, arrQuantityWords, array_size, word_size);
//	textAnalyser.quickSort(arrQuantityWords, 0, array_size - 1, arr);

	//output array to file
	std::string nameOfOutputFile = textAnalyser.outDataToFile(argv[1], arr, array_size);

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
void clearWindowPrintWait(std::string* str, std::string str_2)
{
        using namespace std::chrono_literals;
        system(CLEAN_WINDOW_COMMAND);
        std::cout << *str << str_2 << std::endl;
        std::this_thread::sleep_for(1s);
}
void stateOutput(std::string* str, bool* isContinue)
{
        using namespace std::chrono_literals;
        while(*isContinue)
        {
                clearWindowPrintWait(str, " .");
                clearWindowPrintWait(str, " ..");
                clearWindowPrintWait(str, " ...");
        }
}

void initSTime(void)
{
        STime = std::chrono::steady_clock::now();
}

inline void showETime(void)
{
        auto ETime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = ETime - STime;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\t(" << elapsed_seconds.count() << "s)." << std::endl;
//      std::cout << std::endl;
}
