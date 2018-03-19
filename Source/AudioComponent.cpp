#include "AudioComponent.h"

void  AudioComponent::Awake()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound.wav"))
	{
		//Error
	}

}


void  AudioComponent::Update()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound.wav"))
	{
		//Error
	}

}