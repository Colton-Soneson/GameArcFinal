#pragma once
#include <map>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iostream>


using namespace std;

class LanguageSelect
{
public:
	LanguageSelect(const string& languageKeysFile);
	~LanguageSelect() {};

	void loadLanguageFromFile(const string& fileName);

	map<string, string> getLanguageTable() { return mLanguageTable; };

	string getWordAtKeysIndex(int position);

private:

	vector<string> mLanguageKeys;
	map<string, string> mLanguageTable;

};