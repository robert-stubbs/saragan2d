#include "EnginePCH.h"

#include "cErrorLogger.h"

cErrorLogger* cErrorLogger::Er = nullptr;

void cErrorLogger::CreateConsole()
{
	//FreeConsole();
	if(!AllocConsole())
	{

		MessageBox(NULL, TEXT("Error With ErrorLogger"), TEXT("Error 0x00000001"), MB_OK);

	}else{

		hIn = GetStdHandle(STD_INPUT_HANDLE);
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		hError = GetStdHandle(STD_ERROR_HANDLE);		
		

		myfile.open("ErrorLogger.txt", std::ios::out | std::ios::app);

		Er = this;
	}	
}

void cErrorLogger::WriteToConsole(const char* writetext, bool newline)
{
	if (newline) {
		std::string addNewLine = writetext;
		addNewLine += "\n";
		const char* newline = addNewLine.c_str();

		WriteConsoleA(hOut, newline, (DWORD)strlen(newline), &len, NULL);
		if (myfile.is_open())
		{
			myfile << writetext << std::endl;
		}
	}
	else {
		WriteConsoleA(hOut, writetext, (DWORD)strlen(writetext), &len, NULL);
		if (myfile.is_open())
		{
			myfile << writetext << std::endl;
		}
	}
}

void cErrorLogger::WriteToConsole(std::string writetext)
{
	return WriteToConsole(writetext.c_str());
}

void cErrorLogger::WriteToConsole(int number)
{
	char buffer [50];
	sprintf_s(buffer, "%d ", number);
    const size_t mylen = strlen(buffer);
	WriteConsoleA(hOut, buffer, (DWORD)mylen, &len, NULL);

	if (myfile.is_open())
	{
		myfile << buffer;
	}
}

void cErrorLogger::WriteToConsole(float number)
{
	char buffer [50];
	sprintf_s(buffer, "%f ", number);
    const size_t mylen = strlen(buffer);
	WriteConsoleA(hOut, buffer, (DWORD)mylen, &len, NULL);

	if (myfile.is_open())
	{
		myfile << buffer;
	}
}

void cErrorLogger::WriteToConsole(double number)
{
	char buffer [50];
	sprintf_s(buffer, "%f ", number);
   const size_t mylen = strlen(buffer);
	WriteConsoleA(hOut, buffer, (DWORD)mylen, &len, NULL);

	if (myfile.is_open())
	{
		myfile << buffer;
	}
}

void cErrorLogger::ClearConsole()
{
	system("cls");
}

void cErrorLogger::DestroyConsole()
{
	myfile.close();	
	// Release the console
	FreeConsole();
}

cErrorLogger& cErrorLogger::GetErrorLogger()
{
	if (!Er || Er == nullptr)
	{
		Er = new cErrorLogger();
		Er->CreateConsole();
	}

	return *Er;
}







