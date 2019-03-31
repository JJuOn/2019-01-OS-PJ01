#pragma once
#include "block.h"
#include "freeList.h"
class hashQueue {
private:
	int modNum;
	//int bufferNum;
	block** queue;
	freeList free;
public:
	hashQueue();
	hashQueue(int modNum);
	~hashQueue();
	block* retrieveBlock(bool& found,int blockNum);
	void enQueue(block item);
	void deQueue(int blockNum);
	void printAll();
	void setRandomBuffers(int bufferNum);
	block getBlk(int blockNum);
	void delayToWrite();
	void writeToUnlock();
	void lockToDelay();
};