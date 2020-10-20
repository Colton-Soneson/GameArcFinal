#include "SoundBuffer.h"

using namespace std;

OurSoundBuffer::OurSoundBuffer(const string& filename)
{
	mSoundBuffer.loadFromFile(filename);
}