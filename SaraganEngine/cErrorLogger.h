#ifndef _C_ERROR_LOGGER_H_
#define _C_ERROR_LOGGER_H_

#include <windows.h>
#include <iostream>	
#include <fstream>

class cErrorLogger
{
protected:

    HANDLE hIn;
    HANDLE hOut;
    HANDLE hError;
    DWORD len;
	std::ofstream myfile;

public:

	//use stl and allocConsole and Write to file functions
	void CreateConsole();
	void WriteToConsole(const char* writetext, bool newline = true);
	void WriteToConsole(std::string writetext);
	void WriteToConsole(int number);
	void WriteToConsole(float number);
	void WriteToConsole(double number);

	void ClearConsole();
	void DestroyConsole();
		
	static cErrorLogger* Er;

	static inline cErrorLogger& Log() { return GetErrorLogger(); }
	static cErrorLogger& GetErrorLogger();

};

#endif