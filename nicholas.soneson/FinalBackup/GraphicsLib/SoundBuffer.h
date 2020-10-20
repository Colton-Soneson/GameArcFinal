#pragma once

#include "Trackable.h"

#include <SFML/Audio.hpp>

using namespace std;

class OurSoundBuffer : public Trackable
{
public:
	
	friend class OurSound;
	friend class SoundSystem;

	OurSoundBuffer(const string& filename);
	~OurSoundBuffer() {};

	sf::SoundBuffer getSoundBuffer() { return mSoundBuffer; };

private:

	string mFilename;

	sf::SoundBuffer mSoundBuffer;
};