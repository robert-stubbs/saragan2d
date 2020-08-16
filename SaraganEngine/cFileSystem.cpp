#include "EnginePCH.h"

#include "cFileSystem.h"


cFileSystem::cFileSystem()
{
	LoadPackages("/");
}

cFileSystem::cFileSystem(std::string dir)
{
	LoadDirectory(dir);
}

cFileSystem::~cFileSystem()
{
}

void cFileSystem::LoadDirectory(std::string path)
{
	//namespace fs = boost::filesystem;
	//fs::path Dir(path);
	//fs::directory_iterator end_iter;
	//typedef std::multimap<std::time_t, fs::path> result_set_t;
	//result_set_t result_set;

	//bool exists = fs::exists(Dir);
	//bool isDir = fs::is_directory(Dir);

	//if (exists && isDir)
	//{
	//	for (fs::directory_iterator dir_iter(Dir); dir_iter != end_iter; ++dir_iter)
	//	{
	//		if (fs::is_regular_file(dir_iter->status()))
	//		{
	//			fs::path this_file(dir_iter->path());
	//			
	//			if (this_file.extension() == ".rar" || dir_iter->path().extension() == ".tar")
	//			{
	//				// found rar extension
	//				package newPack;
	//				newPack.loaded = false;
	//				newPack.packPath = this_file.string();
	//				newPack.packName = this_file.filename().string();
	//				packages[newPack.packName] = newPack;
	//				Er->WriteToConsole("Asset Found: ");
	//				Er->WriteToConsole(dir_iter->path().string().c_str());
	//				Er->WriteToConsole("\n");
	//			} 
	//		} else {
	//			// it is a directory?
	//			LoadDirectory(dir_iter->path().string());
	//		}
	//	}
	//}
}

void cFileSystem::LoadPackages(std::string Directory)
{
	// Create path as start directory
	std::stringstream ss;
	//ss << ApplicationDirectory << "\\" << Directory;
	//ss >> Directory;

	LoadDirectory(Directory);

}

std::string cFileSystem::getFile(std::string pack, std::string Name)
{
	std::string fullPackName = pack;
	package this_pack;
	bool found = false;

	for (std::map<std::string, package>::iterator it = packages.begin(); it != packages.end(); it++)
	{
		std::string packname = it->first;
		std::size_t foundPack = packname.find(pack);
		if (foundPack != std::string::npos)
		{
			found = true;
			fullPackName = packname;
			this_pack = it->second;
		}
	}

	if (found)
	{
		//if (!this_pack.loaded)
		//{
		//	//packageManager load files
		//	PackageManager* pm = new PackageManager("", this_pack.packPath);
		//	pm->LoadPackage();
		//	pm->ReadPackage();

		//	if ((int)pm->Files.size() > 0)
		//	{
		//		for (std::map<std::string, std::string>::iterator it = pm->Files.begin(); it != pm->Files.end(); it++)
		//		{
		//			packFile newFile;
		//			newFile.fileName = it->first;
		//			newFile.fileData = it->second;
		//			this_pack.files[newFile.fileName] = newFile;
		//		}
		//		this_pack.loaded = true;
		//		packages[fullPackName] = this_pack;
		//	}

		//}

		for (std::map<std::string, packFile>::iterator it = this_pack.files.begin(); it != this_pack.files.end(); it++)
		{
			std::string fileName = it->first;
			std::size_t found = fileName.find(Name);
			if (found != std::string::npos)
			{
				return it->second.fileData;
			}
		}
	}

	return "";
}