#pragma once
#include "block.h"
#include "freeList.h"
//hashQueue
class hashQueue {
private:
	//mod���� operand
	int modNum;
	//block���� ��� ���̺�
	block** queue;
	//freeList
	freeList free;
public:
	//hashQueue �⺻ ������
	hashQueue();
	//modNum�� �־��� hashQueue ������ 
	hashQueue(int modNum);
	//hashQueue �Ҹ���
	~hashQueue();
	//block�� ã�� �ش� block�� pointer ���·� ��ȯ���ִ� �޼ҵ�
	block* retrieveBlock(bool& exist,int blockNum);
	//ť�� item �����ϴ� �޼ҵ�
	void enQueue(block item);
	//ť���� �ش� blockNum�� ���� block�� �����ϴ� �޼ҵ�
	void deQueue(int blockNum);
	//hashQueue�� freeList ��ü�� ������ִ� �޼ҵ�
	void printAll();
	//���Ƿ� ���۸� �������ִ� �޼ҵ�
	void setRandomBuffers(int bufferNum);
	//getBlk �˰���
	block getBlk(int blockNum,int& scenario);
	//delay�� block���� write���·� �ٲ��ִ� �޼ҵ�
	void delayToWrite();
	//write�� block���� unlock���·� �ٲ��ִ� �޼ҵ�
	void writeToUnlock();
	//lock�� block���� delay�� ���·� �ٲ��ִ� �޼ҵ�
	void lockToDelay();
};