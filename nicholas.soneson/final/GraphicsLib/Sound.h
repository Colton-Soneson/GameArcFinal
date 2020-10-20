#pragma once

#include "Trackable.h"

#include <SFML/Audio.hpp>

using namespace std;

class OurSound : public Trackable
{
public:

	friend class OurSoundBuffer;
	friend class SoundSystem;

	OurSound(OurSoundBuffer* soundBuffer);
	~OurSound() {};

	void playSound();
	sf::Sound getSound() { return mSound; };

private:

	sf::Sound mSound;
};