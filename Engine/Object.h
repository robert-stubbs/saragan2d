#ifndef _OBJECT_H
#define	_OBJECT_H


namespace GameEngine
{
	class Object
	{
	public:

		bool hasUpdate;
		std::string shader_name;
		bool isLoaded;

		Object();
		~Object();
		virtual void Init();
		virtual void Update(float dt);
		virtual void GenerateBuffers() {};
		virtual bool Render();
		virtual void CleanUp();

	};
}

#endif