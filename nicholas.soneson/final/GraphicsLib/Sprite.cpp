#include "Sprite.h"
#include "GraphicsBuffer.h"


using namespace std;

Sprite::Sprite(GraphicsBuffer* buffer, int sourceLocX, int sourceLocY, int width, int height)
{
	mWidth = width;
	mHeight = height;
	mSourceLocX = sourceLocX;
	mSourceLocY = sourceLocY;
	mGraphicsBuffer = buffer;
	mSprite.setTexture(buffer->mTexture);
}

Sprite::~Sprite()
{
	mWidth = NULL;
	mHeight = NULL;
	mSourceLocX = NULL;
	mSourceLocY = NULL;
	//delete mGraphicsBuffer;
}