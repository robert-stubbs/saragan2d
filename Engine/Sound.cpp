#include "EnginePCH.h"
#include "Sound.h"


namespace GameEngine
{

	Sound::Sound()
	{
		m_type = "sound";
		m_soundHandle = "";
		isLoaded = false;
	}

	Sound::~Sound()
	{
		CleanUp();
	}

	bool Sound::Init()
	{
		//cErrorLogger::Log().WriteToConsole("> Initialized SoundItem\n");

		//Stores the sound data
		frequency = sampleRate;                                               //The Sample Rate of the WAVE file
		format = 0;                                                            //The audio format (bits per sample, number of channels)

		alGenBuffers(1, &buffer);                                                    //Generate one OpenAL Buffer and link to "buffer"
		alGenSources(1, &source);                                                   //Generate one OpenAL Source and link to "source"
		if (alGetError() != AL_NO_ERROR)
		{
			//cErrorLogger::Log().WriteToConsole("Error GenSource\n");
			return false;
		}

		//Figure out the format of the WAVE file
		if (bitsPerSample == 8)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO8;
			else if (channels == 2)
				format = AL_FORMAT_STEREO8;
		}
		else if (bitsPerSample == 16)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO16;
			else if (channels == 2)
				format = AL_FORMAT_STEREO16;
		}
		if (!format)
		{
			//cErrorLogger::Log().WriteToConsole("Wrong BitPerSample\n");
			return false;
		}

		alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer
		if (alGetError() != AL_NO_ERROR)
		{
			//cErrorLogger::Log().WriteToConsole("Error loading ALBuffer\n");
			return false;
		}


		//Source
		alSourcei(source, AL_BUFFER, buffer);                                 //Link the buffer to the source
		alSourcef(source, AL_PITCH, 1.0f);                                 //Set the pitch of the source
		alSourcef(source, AL_GAIN, 100.0f);


		// The distance that the source will be the loudest (if the listener is
		// closer, it won't be any louder than if they were at this distance)
		alSourcei(source, AL_REFERENCE_DISTANCE, (ALint)1.0);
		// The distance that the source will be the quietest (if the listener is
		// farther, it won't be any quieter than if they were at this distance)
		alSourcei(source, AL_MAX_DISTANCE, (ALint)FLT_MAX);


		//Sound setting variables
		ALfloat sourcePos[3] = { 0.0, 0.0, 0.0 };                                    //Position of the source sound
		ALfloat sourceVel[3] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound
		SetSource(sourcePos, sourceVel, false);

		isLoaded = true;
		return true;

	}

	void Sound::Update(float dt)
	{

	}

	void Sound::Render()
	{

	}

	void Sound::CleanUp()
	{
		delete[] buf;						//Delete the sound data buffer
		alDeleteSources(1, &source);		//Delete the OpenAL Source
		alDeleteBuffers(1, &buffer);		//Delete the OpenAL Buffer
		alcMakeContextCurrent(NULL);		//Make no context current
	}

	bool Sound::SetSource(ALfloat pos[3], ALfloat vel[3], bool Looping)
	{
		alSourcefv(source, AL_POSITION, pos);
		alSourcefv(source, AL_VELOCITY, vel);
		alSourcei(source, AL_LOOPING, Looping);
		return true;
	}

	void Sound::PlaySoundClip()
	{
		if (!isLoaded)
		{
			//cErrorLogger::Log().WriteToConsole("Not Loaded");
			return;
		}

		//PLAY 
		alSourcePlay(source);                                                       //Play the sound buffer linked to the source
		if (alGetError() != AL_NO_ERROR)
		{
			//cErrorLogger::Log().WriteToConsole("Error playing sound\n");
			return;
		}
	}

	void Sound::loadWav(std::string filePath)
	{

		//Loading of the WAVE file
		FILE* fp = NULL;                                                            //Create FILE pointer for the WAVE file
		fopen_s(&fp, filePath.c_str(), "rb");                                            //Open the WAVE file
		if (!fp) {
			//cErrorLogger::Log().WriteToConsole("Failed to open file\n");
			return;
		}

		//Check that the WAVE file is OK
		fread(type, sizeof(char), 4, fp);                                              //Reads the first bytes in the file
		if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
		{
			//cErrorLogger::Log().WriteToConsole("No RIFF\n");
			return;
		}

		fread(&size, sizeof(DWORD), 1, fp);                                           //Continue to read the file
		fread(type, sizeof(char), 4, fp);                                             //Continue to read the file
		if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
		{

			//cErrorLogger::Log().WriteToConsole("not WAVE\n");
			return;
		}

		fread(type, sizeof(char), 4, fp);                                              //Continue to read the file
		if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
		{

			//cErrorLogger::Log().WriteToConsole("not fmt\n");
			return;
		}

		//Now we know that the file is a acceptable WAVE file
		//Info about the WAVE data is now read and stored
		fread(&chunkSize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&bitsPerSample, sizeof(short), 1, fp);

		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
		{

			//cErrorLogger::Log().WriteToConsole("Missing DATA\n");
			return;
		}

		fread(&dataSize, sizeof(DWORD), 1, fp);                                        //The size of the sound data is read

		buf = new unsigned char[dataSize];												//Allocate memory for the sound data
		fread(buf, sizeof(BYTE), dataSize, fp);											//Read the sound data and display the 

		fclose(fp);
	}
}