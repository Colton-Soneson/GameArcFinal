#include "SoundSystem.h"

using namespace std;

void SoundSystem::playSingleSound(OurSound* theSound)
{
	if (mSoundsOff == false)
	{
		theSound->playSound();
	}
}

void SoundSystem::playSingleSound(const string& filename)
{
	if (mSoundsOff == false)
	{
		mSoundBuffer.loadFromFile(filename);
		mSound.setBuffer(mSoundBuffer);
		mSound.play();
	}
	
}

void SoundSystem::playSingleSound(OurSoundBuffer& theSoundBuffer)
{
	if (mSoundsOff == false)
	{
		mSound.setBuffer(theSoundBuffer.getSoundBuffer());
		mSound.play();
	}
}

void SoundSystem::playSingleSound()
{
	if (mSoundsOff == false)
	{
		mSound.play();
	}
}

void SoundSystem::setSoundBuffer(const string& filename)
{
	mSoundBuffer.loadFromFile(filename);
	mSound.setBuffer(mSoundBuffer);
}


