#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{
	//Nothing needed
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clear();
}

void GraphicsBufferManager::createAndManage(const string& bufferKey, const string& bufferFile)
{
	GraphicsBuffer* buffer = NULL;

	//Find if the key already exists
	map<string, GraphicsBuffer*>::iterator iter = mBufferMap.find(bufferKey);

	//Check if the bufferKey is in the map and if not, add it to the end
	if (iter == mBufferMap.end())
	{
		buffer = new GraphicsBuffer(bufferFile);
		mBufferMap[bufferKey] = buffer;
	}
}

void GraphicsBufferManager::deleteBuffer(GraphicsBuffer* buffer)
{
	map<string, GraphicsBuffer*>::iterator iter;

	//Iterate through the map, if the buffer is found, delete it
	for (iter = mBufferMap.begin(); iter != mBufferMap.end(); iter++)
	{
		if (buffer == iter->second)
		{
			delete buffer;
			mBufferMap.erase(iter);
			return;
		}
	}
}

void GraphicsBufferManager::deleteBuffer(const string& bufferKey)
{
	//figure out if it exists already
	map<string, GraphicsBuffer*>::iterator iter = mBufferMap.find(bufferKey);

	if (iter != mBufferMap.end())//found
	{
		delete iter->second;
		mBufferMap.erase(iter);
	}
}

void GraphicsBufferManager::clear()
{
	map<string, GraphicsBuffer*>::iterator iter;

	//Iterate through map and delete all GraphicsBuffer*
	for (iter = mBufferMap.begin(); iter != mBufferMap.end(); iter++)
	{
		GraphicsBuffer* buffer = iter->second;
		delete buffer;
	}

	mBufferMap.clear();
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(const string& bufferKey)
{
	map<string, GraphicsBuffer*>::const_iterator iter = mBufferMap.find(bufferKey);

	if (iter != mBufferMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}