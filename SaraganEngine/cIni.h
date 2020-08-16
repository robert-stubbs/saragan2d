#ifndef _C_INI_H_
#define _C_INI_H_

#include <string>
#include <map>

class cIni
{
	public:
		cIni(std::string FileName);
		~cIni();

		struct Option
		{
			std::string Name;
			std::string Value;
		};

		struct Parent
		{
			std::string Name;
			std::map < std::string, Option > Options;

		};

		std::map < std::string, Parent > Parents;

		bool LoadIni(std::string FileName);

		int GetIntOption(std::string ParentName, std::string Value, int Default);
		std::string GetstringOption(std::string ParentName, std::string Value, std::string Default);

};


#endif