#include "EnginePCH.h"
#include "FileManager.h"

namespace GameEngine
{
	FileManager::FileManager()
	{

	}

	FileManager::~FileManager()
	{

	}

	std::string FileManager::textFileRead(const char* fileName)
	{
		std::string fileString = std::string(); // A string for storing the file contents
		std::string line = std::string(); // A string for holding the current line

		std::ifstream file(fileName); // Open an input stream with the selected file
		if (file.is_open()) { // If the file opened successfully
			while (!file.eof()) { // While we are not at the end of the file
				getline(file, line); // Get the current line
				fileString.append(line); // Append the line to our file string
				fileString.append("\n"); // Appand a new line character
			}
			file.close(); // Close the file
		}

		return fileString; // Return our string
	}

	std::vector<std::string> FileManager::ReadFile(const char* fileName)
	{
		std::vector<std::string> result = std::vector<std::string>();
		std::string line = std::string(); // A string for holding the current line

		std::ifstream file(fileName); // Open an input stream with the selected file
		if (file.is_open()) { // If the file opened successfully
			while (!file.eof()) { // While we are not at the end of the file
				getline(file, line); // Get the current line
				result.push_back(line); // Append the line to our file string
			}
			file.close(); // Close the file
		}
		return result;
	}
}