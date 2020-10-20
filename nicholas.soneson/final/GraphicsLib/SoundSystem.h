#pragma once

#include <SFML/Audio.hpp>

#include "SoundBuffer.h"
#include "Sound.h"

#include "Trackable.h"

#include <vector>

using namespace std;

class SoundSystem : public Trackable
{
public:

	SoundSystem() {};
	~SoundSystem() {};

	void playSingleSound(OurSound* theSound);

	void playSingleSound(const string& fileName);

	void playSingleSound(OurSoundBuffer& theSoundBuffer);

	void playSingleSound();

	void setSoundBuffer(const string& filename);

	void turnSoundOff(bool active) { mSoundsOff = active; }

private:

	bool mSoundsOff = false;
	sf::Sound mSound;
	sf::SoundBuffer mSoundBuffer;
};