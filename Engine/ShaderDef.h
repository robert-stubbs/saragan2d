#ifndef _SHADER_DEF_H_
#define _SHADER_DEF_H_

class ShaderDef
{
	public:
		std::string vs_path;
		std::string fs_path;

		ShaderDef();
		ShaderDef(std::string vs, std::string fs);
		virtual ~ShaderDef();

		virtual void SetupShader() = 0;
		virtual void SetupAttributeLocations() = 0;
		virtual void SetupUniformLocations() = 0;

};

#endif