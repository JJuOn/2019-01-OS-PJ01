#include <iostream>
#include "freeList.h"

using namespace std;

freeList::freeList() {
	root = NULL;
}

void freeList::insertItem(block item) {
	if (root == NULL) {
		root = new block;
		root->blockNum = item.blockNum;
		root->status = item.status;
	}
	else {
		block* blockPtr;
		blockPtr = root;
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
	}
}


void freeList::deleteItem(int blockNum) {
	block* blockPtr;
	blockPtr = root;
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		delete temp;
		root = blockPtr;
		return;
	}
	while (blockPtr->next != NULL) {
		if (blockPtr->next->blockNum == blockNum) {
			block* temp;
			temp = blockPtr->next;
			blockPtr->next = blockPtr->next->next;
			delete temp;
			return;
		}
		blockPtr = blockPtr->next;
	}
}

bool freeList::isExist(int blockNum){
	block* blockPtr;
	blockPtr = root;
	bool found = false;
	while (!found && blockPtr->next != NULL) {
		if (blockPtr->blockNum == blockNum) {
			found = true;
			break;
		}
		blockPtr = blockPtr->next;
	}
	if (blockPtr->blockNum == blockNum) {
		found = true;
	}
	if (found) {
		cout << "Block exists in freeList" << endl;
	}
	else {
		cout << "Block doesn't exist in freeList" << endl;
	}
	return found;
}

void freeList::printFreeList() {
	block* blockPtr;
	blockPtr = root;
	cout << "freeList : ";
	if (blockPtr == NULL) {
		cout << endl;
		return;
	}
	while (blockPtr->next != NULL) {
		cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
		blockPtr = blockPtr->next;
	}
	cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
}

bool freeList::isEmpty(){
	return root == NULL;

}

int freeList::getFirstBlockNum() {
	return root->blockNum;
}

bool freeList::isDelay() {
	block* blockPtr;
	blockPtr = root;
	while (blockPtr != NULL) {
		if (blockPtr->status == DELAY) {
			return true;
		}
		blockPtr = blockPtr->next;
	}
	return false;
}