#ifndef _C_FILE_SYSTEM_H_
#define _C_FILE_SYSTEM_H_

#include <string>
#include <map>

typedef struct
{
	std::string fileName;
	std::string fileData;
} packFile;

typedef struct 
{
	std::string packName;
	std::string packPath;
	bool loaded;
	std::map<std::string, packFile> files;

} package;

class cFileSystem
{
	std::map<std::string, package> packages;


	public:
		cFileSystem();
		cFileSystem(std::string dir);
		~cFileSystem();

		void LoadDirectory(std::string path);
		void LoadPackages(std::string Directory);

		std::string getFile(std::string pack, std::string Name);
};

#endif