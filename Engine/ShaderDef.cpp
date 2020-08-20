#include "EnginePCH.h"
#include "ShaderDef.h"

ShaderDef::ShaderDef()
{
}

ShaderDef::ShaderDef(std::string vs, std::string fs)
{
	vs_path = vs;
	fs_path = fs;
}

ShaderDef::~ShaderDef()
{
}