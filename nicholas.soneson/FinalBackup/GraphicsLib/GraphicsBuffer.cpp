#include "GraphicsBuffer.h"

using namespace std;

GraphicsBuffer::GraphicsBuffer(const string& filename)
{
	//mBitmap = al_load_bitmap((filename).c_str());
	//mWidth = al_get_bitmap_width(mBitmap);
	//mHeight = al_get_bitmap_height(mBitmap);

	//----------------SFML----------------
	mTexture.loadFromFile((filename).c_str());
	mWidth = mTexture.getSize().x;
	mHeight = mTexture.getSize().y;
}

GraphicsBuffer::GraphicsBuffer()
{
	//mBitmap = NULL;
	mWidth = 0;
	mHeight = 0;
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color col)
{
	mWidth = width;
	mHeight = height;
	mTexture.create(width, height);
}

GraphicsBuffer::GraphicsBuffer(sf::Texture &bitmap)
{
	//mBitmap = bitmap;
	//mWidth = al_get_bitmap_width(mBitmap);
	//mHeight = al_get_bitmap_height(mBitmap);

	//-----------SFML----------
	mTexture = bitmap;
	mWidth = mTexture.getSize().x;
	mHeight = mTexture.getSize().y;
}

GraphicsBuffer::~GraphicsBuffer()
{
	mWidth = NULL;
	mHeight = NULL;
	//al_destroy_bitmap(mBitmap);
}
