#ifndef _SOUND_H_
#define _SOUND_H_

#include "Types.h"
#include "Component.h"

namespace GameEngine {

	class Sound : public Component {
	private:
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


	public:
		Sound();
		virtual ~Sound();

		virtual bool Init() override;

		virtual void Update(float dt) override;

		virtual void Render() override;

		virtual void CleanUp() override;

		bool SetSource(ALfloat pos[3], ALfloat vel[3], bool Looping);

		void PlaySoundClip();

		void loadWav(std::string filePath);

	};

}

#endif