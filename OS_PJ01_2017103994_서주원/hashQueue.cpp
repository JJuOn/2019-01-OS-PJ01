#include <iostream>
#include <ctime>
#include <windows.h>
#include "hashQueue.h"

using namespace std;
//hashQueue �⺻ ������
//input: ����
//output: �ʱ�ȭ�� ������ hashQueue
hashQueue::hashQueue() {
	this->modNum = 0;
}

//modNum�� �־��� hashQueue ������
//input: mod ������ operand
//output: modNum�� �ʱ�ȭ�ǰ�, modNum�� ���� queue�� �����Ҵ��� �̷���� hashQueue
hashQueue::hashQueue(int modNum) {
	this->modNum = modNum;
	//modNum�� ������ŭ queue�� �����Ҵ� ���ش�
	this->queue = new block*[modNum];
	//�����Ҵ� ������ queue�ȿ���
	for (int i = 0; i < modNum; i++) {
		//queue���� NULL�� �ʱ�ȭ �����ش�
		queue[i] = NULL;
	}
	//freeList�� �ʱ�ȭ�����ش�
	freeList();
}

//hashQueue �Ҹ���
//input: ����
//output: ��� ��尡 ������ hashQueue
hashQueue::~hashQueue() {
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		//������ hashQueue �� �྿ ����Ű����
		blockPtr = queue[i];
		//hashQueue �� �྿ ����
		while (blockPtr != NULL) {
			block* temp = blockPtr->next;
			delete blockPtr;
			blockPtr = temp;
		}
		//���������� block�� NULL
		queue[i] = NULL;
	}
	//hashQueue ��ü ����
	delete[] queue;
}

//block�� ã�� �ش� block�� pointer ���·� ��ȯ���ִ� �޼ҵ�
//input: ��ȯ������ exist, ã�� block�� blockNum
//output: ã�� block�� pointer
block* hashQueue::retrieveBlock(bool& exist,int blockNum) {
	//hashQueue�� �����ϱ� ���� block mod modNum���� index�� ����
	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
	bool found = false;
	//���� ã���ʾҰ�, ������ ��忡 �����ϱ� ������
	while (!found && blockPtr->next != NULL) {
		//blockPtr�� ã�����ϴ� block�̶��
		if (blockPtr->blockNum == blockNum) {
			//ã�Ҵٰ� ���ְ� �ݺ��� Ż��
			found = true;
			break;
		}
		//���� ��ã������ ���� ���� �̵�
		blockPtr = blockPtr->next;
	}
	//������ ��尡 ã���� �ϴ� block�̶��
	if (blockPtr->blockNum == blockNum) {
		//ã�Ҵٰ� ���ش�
		found = true;
	}
	//ã�Ҵٸ�
	if (found) {
		cout << "Block exists in hashQueue" << endl;
		exist = found;
		return blockPtr;
	}
	//�� ã�Ҵٸ�
	else {
		cout << "Block doesn't exists in hashQueue" << endl;
		exist = found;
		return NULL;
	}
}

//ť�� item �����ϴ� �޼ҵ�
//input: ������ block
//output: ���ο� �������� ���Ե� hashQueue
void hashQueue::enQueue(block item) {
	//hashQueue�� �����ϱ� ���� blockNum mod modNum���� index ���
	int index = item.blockNum % this->modNum;
	//ť�� ����ִٸ�
	if (this->queue[index] == NULL) {
		//���ο� block ����
		queue[index] = new block;
		queue[index]->blockNum = item.blockNum;
		queue[index]->status = item.status;
		//�����ϰ����ϴ� block�� status�� delay��� freeList�� ����, �Ǵ� lock�� �ƴ϶�� 50% Ȯ����(rand()%2�� ����) freeList�� ����
		if (queue[index]->status == DELAY || (rand() % 2 && queue[index]->status != LOCK)) {
			this->free.insertItem(*queue[index]);
		}
	}
	//ť�� ������� �ʴٸ�
	else {
		block* blockPtr;
		blockPtr = queue[index];
		//������ ���� �̵��Ѵ�
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		//������ ��� ������ ���ο� block ����
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
		//�����ϰ����ϴ� block�� status�� delay��� freeList�� ����, �Ǵ� lock�� �ƴ϶�� 50% Ȯ����(rand()%2�� ����) freeList�� ����
		if (blockPtr->status == DELAY || (rand() % 2 && blockPtr->status != LOCK)) {
			this->free.insertItem(*blockPtr);
		}
	}
}

//ť���� �ش� blockNum�� ���� block�� �����ϴ� �޼ҵ�
//input: ������ block�� blockNum
//output: �ش� block�� ������ hashQueue
void hashQueue::deQueue(int blockNum) {
	//hashQueue�� �����ϱ� ���� blockNum mod modNum���� index ���
	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
	//�����ϰ��� �ϴ� block�� ���� �տ� �ִٸ� ����
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		queue[index] = blockPtr;
		delete temp;
		return;
	}
	//���� �տ� ���� �ʴٸ�
	//��������� ������
	while (blockPtr->next != NULL) {
		//���� ����� ������尡 �����ϰ��� �ϴ� block�̶�� ����
		if (blockPtr->next->blockNum == blockNum) {
			block* temp;
			temp = blockPtr->next;
			blockPtr->next = blockPtr->next->next;
			delete temp;
			return;
		}
		//���� ��ã�Ҵٸ� ���� ���� �̵�
		blockPtr = blockPtr->next;
	}
}

//hashQueue�� freeList ��ü�� ������ִ� �޼ҵ�
//input: ����
//output: �ؽ�ť�� ��� ��� ���
void hashQueue::printAll() {
	//������ ��µǾ��� ���� �����
	system("cls");
	//status ǥ��
	cout << "0:LOCK 1:UNLOCK 2:DELAY 3:WRITE\n";
	//queue�� ��� �࿡ ���Ͽ�
	for (int i = 0; i < modNum; i++) {
		cout << "hashQueue " << i << " : ";
		block* blockPtr;
		blockPtr = queue[i];
		//���� ��尡 NULL�� �ƴҶ� ����
		if (blockPtr != NULL) {
			//��������� ������
			while (blockPtr->next != NULL) {
				//blockNum(status)�������� ������ش�
				cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
				//�������� �̵�
				blockPtr = blockPtr->next;
			}
			//������ ��忡��
			//blockNum(status)�������� ������ش�
			cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
		}
	}
	//freeList ���
	this->free.printFreeList();
}

//���Ƿ� ���۸� ������ �ִ� �޼ҵ�
//input: ������ ������ ����
//output: ������ ���۰� ���Ե� hashQueue
void hashQueue::setRandomBuffers(int bufferNum) {
	block* temp;
	//bufferNum��ŭ �����Ҵ� ���ش�
	temp = new block[bufferNum];
	srand(time(0));
	for (int i = 0; i < bufferNum; i++) {
		//1~99������ ���� blockNum���� ���ش�
		temp[i].blockNum = rand() % 99 + 1;
		//status�� lock,unlock,delay,write �� ������ �ϳ��� �������� �ο��Ѵ�
		temp[i].status = rand() % 4;
		//�ߺ��� blockNum�� �����ϴ°��� ����
		for (int j = 0; j < i; j++) {
			if (temp[i].blockNum == temp[j].blockNum) {
				i = i - 1;
				break;
			}
		}
	}
	/* ������ ���� Ȯ��
	for (int i = 0; i < bufferNum; i++) {
		cout << i + 1 << ":" << temp[i].blockNum << endl;
	}
	*/
	//������ ������ hashQueue�� �������ش�
	for (int i = 0; i < bufferNum; i++) {
		this->enQueue(temp[i]);
	}
	delete[] temp;
}

//getBlk �˰���
//input: ����ϰ����ϴ� block�� blockNum
//output: ����ϰ��� �ϴ� block ��ȯ, scenario ��ȯ
block hashQueue::getBlk(int blockNum,int& scenario) {
	bool found = false;
	bool exist = false;
	block* blockPtr=NULL;
	//block�� ��ȯ���� �ʾ��������� �ݺ�����
	while (!found) {
		blockPtr = this->retrieveBlock(exist, blockNum);
		//block�� ������ ��(�ó����� 1,5)
		if (exist) {

			//ã���� �ϴ� block�� LOCK ���¶��(�ó����� 5)
			if (blockPtr->status==LOCK) {
				Sleep(3000);
				this->lockToDelay();
				cout << endl;
				this->printAll();
				cout << endl;
				if (scenario == 0)
					scenario = 5;
				continue;
			}
			//�׷��� ������ LOCK ���·� ������ְ� block�� ��ȯ�Ѵ�(�ó����� 1)
			blockPtr->status = LOCK;
			free.deleteItem(blockNum);
			if (scenario == 0)
				scenario = 1;
			found = true;
		}
		//block�� �������� ���� ��(�ó����� 2,3,4)
		else {
			//freeList�� ����ִٸ� (�ó����� 4)
			if (free.isEmpty()) {
				Sleep(3000);
				this->lockToDelay();
				if (scenario == 0)
					scenario = 4;
				continue;
			}
			//freeList�� DELAY ������ block�� �ִٸ� (�ó����� 3)
			if (free.isDelay()) {
				Sleep(3000);
				this->delayToWrite();
				cout << endl;
				this->printAll();
				cout << endl;
				Sleep(3000);
				this->writeToUnlock();
				if (scenario == 0)
					scenario = 3;
				continue;
			}
			//free buffer�� ã���� �� (�ó����� 2)
			//���� block�� blockNum�� �����´�
			int deletedBlockNum = free.getFirstBlockNum();
			//freeList���� �ش� block�� �����ϰ�
			free.deleteItem(deletedBlockNum);
			//���ÿ� hashQueue������ �����Ѵ�
			this->deQueue(deletedBlockNum);
			//����ϰ��� �ϴ� blockNum�� ���� block�� ������ְ�
			block newBlock;
			newBlock.blockNum = blockNum;
			//LOCK ���·� ����� �� ��
			newBlock.status = LOCK;
			//HashQueue�� �����Ѵ�
			this->enQueue(newBlock);
			if (scenario == 0)
				scenario = 2;
		}
		cout << endl;
		this->printAll();
		cout << endl;
	}
	return *blockPtr;
}

//delay�� block���� write���·� �ٲ��ִ� �޼ҵ�
//input: ����
//output: delay�� ��ϵ��� ���°� write�� �ٲ�
void hashQueue::delayToWrite() {
	//��� hashQueue�� �ึ�� �����Ѵ�
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//���� blockPtr�� NULL�� �ƴ� ������
		while (blockPtr != NULL) {
			//block�� DELAY ���¶��
			if (blockPtr->status == DELAY) {
				//WRITE ���·� �ٲ��ְ�
				blockPtr->status = WRITE;
				//freeList���� �����Ѵ�
				free.deleteItem(blockPtr->blockNum);
			}
			blockPtr = blockPtr->next;
		}
	}
}

//write�� block���� unlock���·� �ٲ��ִ� �޼ҵ�
//input: ����
//output: write�� ��ϵ��� ���°� unlock�� �ٲ�
void hashQueue::writeToUnlock() {
	//��� hashQueue�� �ึ�� �����Ѵ�
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//���� blockPtr�� NULL�� �ƴ� ������
		while (blockPtr != NULL) {
			//block�� WRITE ���¶��
			if (blockPtr->status == WRITE) {
				//UNLOCK ���·� �ٲ��ְ�
				blockPtr->status = UNLOCK;
				//freeList�� �����Ѵ�
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}

//lock�� block���� delay���·� �ٲ��ִ� �޼ҵ�
//input: ����
//output: lock�� ��ϵ��� ���°� delay�� �ٲ�
void hashQueue::lockToDelay() {
	//��� hashQueue�� �ึ�� �����Ѵ�
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//���� blockPtr�� NULL�� �ƴ� ������
		while (blockPtr != NULL) {
			//block�� LOCK ���¶�� 50% Ȯ����
 			if (blockPtr->status == LOCK && rand()%2 ) {
				//DELAY ���·� �ٲ��ְ� 
				blockPtr->status = DELAY;
				//freeList�� �����Ѵ�
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}