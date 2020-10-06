#ifndef _C_SOUND_SYSTEM_H_
#define _C_SOUND_SYSTEM_H_

//https://www.openal.org/downloads/


#include "AL\al.h"
#include "AL\alc.h"

#include "System.h"

namespace GameEngine {
	class Sound;

	struct ListenerPos
	{
		ALfloat pos[3];
		ALfloat vel[3];
		ALfloat orient[6];
	};

	class SoundSystem : public System
	{
	public:

		ALCdevice* device;
		ALCcontext* context;

		SoundSystem(bool isui = false, bool isanim = false);
		~SoundSystem();

		virtual void Init();
		virtual void Update(float dt);

		virtual void Render() {};

		virtual void CleanUp();

		virtual void AddSoundComponent(Sound* newSound);
		virtual Sound* getSoundComponent(std::string handle);

		virtual void AddComponent(std::string handle);
		virtual Component* getComponent(std::string handle);
		virtual void RemoveComponent(std::string handle);

		void AddSound(std::string filename, std::string instance_name);
		void RemoveSound(std::string instance_name);

		void PlaySoundClip(std::string name);
		bool SetListeners(ListenerPos Listener);
		bool SetListeners(glm::vec3 pos, glm::vec3 LookAt, glm::vec3 Orient);

		bool SetSource(std::string name, float pos[3], float vel[3], bool Looping);
	};
}

#endif
