#include "EnginePCH.h"
#include "SoundSystem.h"
#include "SoundItem.h"

#include "Component.h"
#include "cErrorLogger.h"

SoundSystem::SoundSystem(bool isui, bool isanim) : System(isui, isanim)
{
	SystemName = "AUDIO";

	//Now OpenAL needs to be initialized                                                      
	//And an OpenAL Context
	device = alcOpenDevice(NULL);                                               //Open the device
	if (!device)
	{
		Er->WriteToConsole("no sound device\n");
		return;
	}
	context = alcCreateContext(device, NULL);                                   //Give the device a context
	alcMakeContextCurrent(context);                                             //Make the context the current
	if (!context)
	{
		Er->WriteToConsole("no sound context\n");
		return;
	}

	ListenerPos Listener = { { 0.0, 0.0, 0.0 }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f, 0.0, 1.0, 0.0 } };
	SetListeners(Listener);

}


SoundSystem::~SoundSystem()
{
	CleanUp();
}

void SoundSystem::Init()
{

}


void SoundSystem::Update(float dt)
{
	//if (map_components.size() == 0) {
	//	AddSound("C:/Assets/Sound/Sound.wav", "test");
	//	PlaySoundClip("test");
	//}
}

void SoundSystem::CleanUp()
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {
		mapiter->second->CleanUp();
	}

	map_components.clear();

	//Destroy the OpenAL Context
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void SoundSystem::AddComponent(std::string handle)
{
	return;
}

void SoundSystem::AddSoundComponent(SoundItem* newSound)
{
	cComponent* comp = getComponent(newSound->m_handle);

	if (comp == nullptr)
	{
		std::shared_ptr<SoundItem> newSystem(newSound);
		map_components[newSound->m_handle] = newSystem;
	}

	return;
}

SoundItem* SoundSystem::getSoundComponent(std::string handle)
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {

		if (mapiter->first == handle) {
			return (SoundItem*)(mapiter->second.get());
		}
	}

	return nullptr;
}

cComponent* SoundSystem::getComponent(std::string handle)
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {

		if (mapiter->first == handle) {
			return mapiter->second.get();
		}
	}

	return nullptr;
}

void SoundSystem::RemoveComponent(std::string handle)
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {

		if (mapiter->first == handle) {
			mapiter->second->CleanUp();
		}
	}
}

void SoundSystem::AddSound(std::string filename, std::string instance_name)
{
	SoundItem* foo = new SoundItem();
	// # TODO add asset loading
	foo->loadWav(filename.c_str());

	if (foo->Init())
	{
		SoundItem* comp = this->getSoundComponent(instance_name);
		if (comp == nullptr)
		{
			std::shared_ptr<SoundItem> newSystem(foo);
			map_components[instance_name] = newSystem;
		}
	}
}

void SoundSystem::RemoveSound(std::string instance_name)
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {

		if (mapiter->first == instance_name) {
			mapiter->second->CleanUp();
		}
	}
}

void SoundSystem::PlaySoundClip(std::string name)
{

	ComponentPtr test = map_components[name];
	if (test) {
		SoundItem* foo = (SoundItem*)(test.get());
		if (foo && foo->isLoaded)
		{
			foo->PlaySoundClip();
		}
	}
}

bool SoundSystem::SetListeners(ListenerPos Listener)
{
	alListenerfv(AL_POSITION, &Listener.pos[0]);
	if (alGetError() != AL_NO_ERROR)
	{
		Er->WriteToConsole("Error playing sound\n");
		return false;
	}
	return true;
}

bool SoundSystem::SetListeners(glm::vec3 pos, glm::vec3 LookAt, glm::vec3 Orient)
{
	ListenerPos Listener = { { pos.x, pos.y, pos.z }, { 0.0f, 0.0f, 0.0f }, { LookAt.x, LookAt.y, LookAt.z, Orient.x, Orient.y, Orient.z } };
	return SetListeners(Listener);
}

bool SoundSystem::SetSource(std::string name, float pos[3], float vel[3], bool Looping)
{
	for (mapiter = map_components.begin(); mapiter != map_components.end(); mapiter++) {

		if (mapiter->first == name) {
			SoundItem* foo = (SoundItem*)(mapiter->second.get());
			foo->SetSource(pos, vel, Looping);
		}
	}
	return true;
}