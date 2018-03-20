#pragma once
#include "..\Source\BaseComponent.h"
#include <SFML\Audio.hpp>
#include <iostream>
#include <string>


class AudioComponent : public BaseComponent {
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	void playSound(const std::string& filename);
	void playMusic(const std::string& filename);

	
	std::string& filename;

	sf::SoundBuffer buffer;
	sf::Sound sound;
}