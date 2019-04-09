#pragma once
#include "block.h"
//HashQueue�� ��������� �� freeList ����.
class freeList {
private:
	//freeList�� root�� �����ϴ� linkedList.
	block* root;
public:
	//freeList�� ������
	freeList();
	//freeList�� �Ҹ���
	~freeList();
	//item�� freeList�� �������ִ� �޼ҵ�
	void insertItem(block item);
	//�ش� blockNum�� ���� block�� freeList���� ���������ִ� �޼ҵ�
	void deleteItem(int blockNum);
	//�ش� blockNum�� ���� block�� freeList�� �����ϴ��� ��ȯ���ִ� �޼ҵ�
	bool isExist(int blockNum);
	//freeList ��ü�� �ܼ�â�� ������ִ� �޼ҵ�
	void printFreeList();
	//freeList�� ����� �� ������ִ� �޼ҵ�
	bool isEmpty();
	//freeList�� ù��° block�� blockNum�� ��ȯ���ִ� �޼ҵ�
	int getFirstBlockNum();
	//freeList���� delay������ block�� �ִ� �� ��ȯ���ִ� �޼ҵ�
	bool isDelay();
};