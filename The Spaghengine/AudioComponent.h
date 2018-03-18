#pragma once
#include "..\Source\BaseComponent.h"
#include <SFML\Audio.hpp>

class AudioComponent : public BaseComponent {
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	sf::SoundBuffer buffer;
	sf::Sound sound;
}