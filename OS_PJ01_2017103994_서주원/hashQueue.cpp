#include <iostream>
#include <ctime>
#include "hashQueue.h"

using namespace std;

hashQueue::hashQueue() {
	this->modNum = 0;
}

hashQueue::hashQueue(int modNum) {
	this->modNum = modNum;
	//this->bufferNum = bufferNum;
	this->queue = new block*[modNum];
	for (int i = 0; i < modNum; i++) {
		queue[i] = NULL;
	}
	freeList();
}

hashQueue::~hashQueue() {

}

block* hashQueue::retrieveBlock(bool& exist,int blockNum) {

	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
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
		cout << "Block exists in hashQueue" << endl;
		exist = found;
		return blockPtr;
	}
	else {
		cout << "Block doesn't exists in hashQueue" << endl;
		exist = found;
		return NULL;
	}
}

void hashQueue::enQueue(block item) {
	int index = item.blockNum % this->modNum;
	if (this->queue[index] == NULL) {
		queue[index] = new block;
		queue[index]->blockNum = item.blockNum;
		queue[index]->status = item.status;
		if (queue[index]->status == DELAY) {
			this->free.insertItem(*queue[index]);
		}
	}
	else {
		block* blockPtr;
		blockPtr = queue[index];
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
		if (blockPtr->status == DELAY || (rand() % 2 && blockPtr->status != LOCK)) {
			this->free.insertItem(*blockPtr);
		}
	}
}

void hashQueue::deQueue(int blockNum) {
	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		queue[index] = blockPtr;
		delete temp;
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

void hashQueue::printAll() {
	for (int i = 0; i < modNum; i++) {
		cout << "hashQueue " << i << " : ";
		block* blockPtr;
		blockPtr = queue[i];
		if (blockPtr != NULL) {
			while (blockPtr->next != NULL) {
				cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
				blockPtr = blockPtr->next;
			}
			cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
		}
	}
	this->free.printFreeList();
}

void hashQueue::setRandomBuffers(int bufferNum) {
	block* temp;
	temp = new block[bufferNum];
	srand(time(0));
	for (int i = 0; i < bufferNum; i++) {
		temp[i].blockNum = rand() % 99 + 1;
		temp[i].status = rand() % 3;
		for (int j = 0; j < i; j++) {
			if (temp[i].blockNum == temp[j].blockNum) {
				i = i - 1;
				break;
			}
		}
	}
	for (int i = 0; i < bufferNum; i++) {
		cout << i + 1 << ":" << temp[i].blockNum << endl;
	}
	for (int i = 0; i < bufferNum; i++) {
		this->enQueue(temp[i]);
	}
	delete[] temp;
}

block hashQueue::getBlk(int blockNum) {
	bool found = false;
	bool exist = false;
	block* blockPtr=NULL;
	while (!found) {
		blockPtr = this->retrieveBlock(exist, blockNum);
		if (exist) {
			if (blockPtr->status==LOCK) {
				//_sleep(3000);
				this->lockToDelay();
				cout << endl;
				this->printAll();
				cout << endl;
				continue;
			}
			blockPtr->status = LOCK;
			free.deleteItem(blockNum);
			found = true;
		}
		else {
			if (free.isEmpty()) {
				//_sleep(3000);
				this->lockToDelay();
				continue;
			}
			if (free.isDelay()) {
				this->delayToWrite();
				cout << endl;
				this->printAll();
				cout << endl;
				this->writeToUnlock();
				continue;
			}
			int deletedBlockNum = free.getFirstBlockNum();
			free.deleteItem(deletedBlockNum);
			this->deQueue(deletedBlockNum);
			block newBlock;
			newBlock.blockNum = blockNum;
			newBlock.status = LOCK;
			this->enQueue(newBlock);
		}
		cout << endl;
		this->printAll();
		cout << endl;
	}
	return *blockPtr;
}

void hashQueue::delayToWrite() {
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		while (blockPtr != NULL) {
			if (blockPtr->status == DELAY) {
				blockPtr->status = WRITE;
				free.deleteItem(blockPtr->blockNum);
			}
			blockPtr = blockPtr->next;
		}
	}
}

void hashQueue::writeToUnlock() {
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		while (blockPtr != NULL) {
			if (blockPtr->status == WRITE) {
				blockPtr->status = UNLOCK;
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}

void hashQueue::lockToDelay() {
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		while (blockPtr != NULL) {
			if (blockPtr->status == LOCK && rand()%2 ) {
				blockPtr->status = DELAY;
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}