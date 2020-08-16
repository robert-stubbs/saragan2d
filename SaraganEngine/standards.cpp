#include "EnginePCH.h"


int ConvertCharToInt(char *text)
{
	std::string number;
	number.append(text);
	int output = 0;

	output = atoi(number.c_str());


	return output;
}

int GetRandomNumber(int start, int end)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(start, end); // define the range
	return distr(eng);
}