#ifndef _SOUND_ITEM_H_
#define _SOUND_ITEM_H_

#include "Component.h"
namespace GameEngine
{
	class SoundItem : public Component
	{
	public:
		std::string m_soundHandle;

		ALuint source;
		ALuint buffer;
		ALuint frequency;
		ALenum format;

		bool isLoaded;

		char type[4];
		DWORD size;
		DWORD chunkSize;
		short formatType;
		short channels;
		DWORD sampleRate;
		DWORD avgBytesPerSec;
		short bytesPerSample;
		short bitsPerSample;
		DWORD dataSize;
		unsigned char* buf;


		SoundItem();
		~SoundItem();

		virtual bool Init();

		bool SetSource(ALfloat pos[3], ALfloat vel[3], bool Looping);

		void PlaySoundClip();

		void loadWav(std::string filePath);

		virtual void Update(float dt);
		virtual void Render();
		virtual void RenderAnim() {};
		virtual void RenderUI() {};
		virtual bool handleMessage(SystemMessage msg);

		virtual void CleanUp();
	};
}

#endif