#include "LanguageSelect.h"

using namespace std;

LanguageSelect::LanguageSelect(const string& languageKeysFile)
{
	ifstream inputKeys(languageKeysFile);

	int itr = 0;

	if (inputKeys.good())
	{
		while (!inputKeys.eof())
		{
			string key;
			getline(inputKeys, key);
			if (key != "")
			{
				//mLanguageKeys[itr] = key;
				mLanguageKeys.push_back(key);
			}

			itr++;
		}
	}

	inputKeys.close();
}

void LanguageSelect::loadLanguageFromFile(const string& filename)
{
	ifstream inputFile(filename);

	mLanguageTable.clear();

	if (inputFile.good())
	{
		while (!inputFile.eof())
		{
			string key;
			string value;
			getline(inputFile, key);
			getline(inputFile, value);
			if (key != "")
			{
				mLanguageTable[key] = value;
			}
		}
	}

	inputFile.close();
}

string LanguageSelect::getWordAtKeysIndex(int position)
{
	return mLanguageTable[mLanguageKeys[position]];
}