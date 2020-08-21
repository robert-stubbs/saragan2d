#include "EnginePCH.h"

#include "cIni.h"
namespace GameEngine
{
	cIni::cIni(std::string FileName)
	{
		LoadIni(FileName);
	}

	cIni::~cIni()
	{
		Parents.clear();
	}

	bool cIni::LoadIni(std::string FileName)
	{
		std::string buffer;
		std::ifstream fp(FileName);

		std::string LastParent;
		Parents.clear();

		if (fp.is_open())
		{
			std::string Line;
			char item[256];
			while (fp.getline(item, 256))
			{
				Line = item;
				size_t aIndex = Line.rfind("[");
				if (aIndex != std::string::npos)
				{
					std::string Name;
					size_t iIndex = Line.rfind("[");
					size_t lIndex = Line.rfind("]");
					if (iIndex != std::string::npos && lIndex != std::string::npos)
					{
						Name = Line.substr(iIndex + 1, lIndex - 1);
						Parent newParent;
						newParent.Name = Name;
						LastParent = Name;
						Parents[Name] = newParent;
					}
				}
				else {
					if (Line.length() > 0)
					{
						std::string first;
						std::string last;
						size_t iIndex = Line.rfind("=");

						first = Line.substr(0, iIndex);
						last = Line.substr(iIndex + 1, Line.length());

						Option newOption;
						newOption.Name = first;
						newOption.Value = last;
						Parents[LastParent].Options[first] = newOption;
					}
				}
			}
		}
		fp.close();

		return true;
	}

	int cIni::GetIntOption(std::string ParentName, std::string Value, int Default)
	{
		if (Parents.find(ParentName) != Parents.end())
		{
			Parent p = Parents[ParentName];

			if (p.Options.find(Value) != p.Options.end())
			{
				Option item = p.Options[Value];
				std::string Val = item.Value;

				if (Val.length())
				{
					int resp = atoi(Val.c_str());
					return resp;
				}
			}
		}
		return Default;
	}

	std::string cIni::GetstringOption(std::string ParentName, std::string Value, std::string Default)
	{
		if (Parents.find(ParentName) != Parents.end())
		{
			Parent p = Parents[ParentName];

			if (p.Options.find(Value) != p.Options.end())
			{
				Option item = p.Options[Value];
				std::string Val = item.Value;

				if (Val.length())
				{
					return Val;
				}
			}
		}
		return Default;
	}
}