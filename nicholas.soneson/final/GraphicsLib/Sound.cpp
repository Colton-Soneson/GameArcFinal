#include "Sound.h"
#include "SoundBuffer.h"

using namespace std;

OurSound::OurSound(OurSoundBuffer* buffer)
{
	mSound.setBuffer(buffer->getSoundBuffer());
}

void OurSound::playSound()
{
	mSound.play();
}