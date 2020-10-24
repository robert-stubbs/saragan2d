#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

namespace GameEngine
{
	class FileManager
	{
		public:
			FileManager();
			virtual ~FileManager();

			static std::string textFileRead(const char* fileName);
			static std::vector<std::string> ReadFile(const char* fileName);
	};
}

#endif