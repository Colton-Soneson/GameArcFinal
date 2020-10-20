#pragma once
#include <vector>
#include <map>
#include "GraphicsBuffer.h"

using namespace std;

class GraphicsBufferManager : public Trackable
{
	friend class Game;

public:

	GraphicsBuffer* getBuffer(const string& bufferKey);

	void createAndManage(const string& bufferKey, const string& bufferFile); //adds a GraphicsBuffer to mBufferMap
	void deleteBuffer(GraphicsBuffer* buffer); //delete the given GraphicsBuffer from mBufferMap
	void deleteBuffer(const string& bufferKey); //delete a GraphicsBuffer from mBufferMap using the given key
	void clear();

private:

	//Private so only Game can make a GraphicsBufferManager
	GraphicsBufferManager();
	~GraphicsBufferManager();

	map<string, GraphicsBuffer*> mBufferMap;
};