#include "Font.h"

using namespace std;

Font::Font(const string& filename, int size)
{
	mSize = size;
	mFontFilename = filename;
	//mCourFont = al_load_ttf_font((mFontFilename).c_str(), mSize, 0);
	//assert(mCourFont);

	//----------SFML-----------------
	mCourFont.loadFromFile((mFontFilename).c_str());
}

Font::~Font()
{
	mSize = NULL;
	//al_destroy_font(mCourFont);
}