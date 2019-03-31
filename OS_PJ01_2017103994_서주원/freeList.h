#pragma once
#include "block.h"

class freeList {
private:
	block* root;
public:
	freeList();
	void insertItem(block item);
	void deleteItem(int blockNum);
	bool isExist(int blockNum);
	void printFreeList();
	bool isEmpty();
	int getFirstBlockNum();
	bool isDelay();
};