#include <iostream>
#include "freeList.h"

using namespace std;
//freeList ������
//input: ����
//output: �ʱ�ȭ�� ������ freeList
freeList::freeList() {
	root = NULL;
}

//freeList �Ҹ���
//input: ����
//output: ��� ��尡 ������ ������ freeList
freeList::~freeList() {
	block* blockPtr;
	blockPtr = root;
	while (blockPtr != NULL) {
		block* next = blockPtr->next;
		delete blockPtr;
		blockPtr = next;
	}
	root = NULL;
}

//item�� freeList�� �������ִ� �޼ҵ�
//input: ������ block type�� item
//output: �ش� block�� �߰��� ������ freeList
void freeList::insertItem(block item) {
	//freeList�� ����ִٸ�
	if (root == NULL) {
		//���� block�� ������ش�
		root = new block;
		root->blockNum = item.blockNum;
		root->status = item.status;
	}
	//freeList�� ������� �ʴٸ�
	else {
		block* blockPtr;
		blockPtr = root;
		//������ ������ �̵��� ��
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		//���� block�� ������ش�
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
	}
}

//�ش� blockNum�� ���� block�� freeList���� ���������ִ� �޼ҵ�
//input: ������ block�� blockNum
//output: �ش� block�� ������ ������ freeList
void freeList::deleteItem(int blockNum) {
	block* blockPtr;
	blockPtr = root;
	//�����ϰ��� �ϴ� block�� root�� �ִٸ�,
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		//�����Ѵ�
		delete temp;
		root = blockPtr;
		return;
	}
	//�����ϰ��� �ϴ� block�� root�� ���� �ʴٸ�
	//������ ��忡 �����ϱ� ������
	while (blockPtr->next != NULL) {
		//blockPtr�� ����Ű�� �ִ� ����� ������ �����ϰ��� �ϴ� block�� blockNum�̶��
		if (blockPtr->next->blockNum == blockNum) {
			block* temp;
			temp = blockPtr->next;
			blockPtr->next = blockPtr->next->next;
			//�����Ѵ�.
			delete temp;
			return;
		}
		blockPtr = blockPtr->next;
	}
}

//�ش� blockNum�� ���� block�� freeList�� �����ϴ��� ��ȯ���ִ� �޼ҵ�
//input: ã�� block�� blockNum
//output: block�� ���� ���� ��ȯ
bool freeList::isExist(int blockNum){
	block* blockPtr;
	blockPtr = root;
	bool found = false;
	//���� ã���� �ϴ� block�� ã�� �ʾҰ�, ������ ��忡 �����ϱ� �� ����,
	while (!found && blockPtr->next != NULL) {
		//���� ã�Ҵٸ� found�� true�� ǥ�����ְ� �ݺ����� Ż���Ѵ�
		if (blockPtr->blockNum == blockNum) {
			found = true;
			break;
		}
		//�ƴ϶�� ���� ���� �̵��Ѵ�
		blockPtr = blockPtr->next;
	}
	//������ ��尡 ã���� �ϴ� block�̶��
	if (blockPtr->blockNum == blockNum) {
		//ã�Ҵٰ� ���ش�
		found = true;
	}
	//�� ������ ������ ��带 ã�Ҵٸ�
	if (found) {
		cout << "Block exists in freeList" << endl;
	}
	//�� ������ ���������� ��带 ã�� ���ߴٸ�
	else {
		cout << "Block doesn't exist in freeList" << endl;
	}
	return found;
}

//freeList ��ü�� �ܼ�â�� ������ִ� �޼ҵ�
//input: ����
//output: �ܼ�â�� ���
void freeList::printFreeList() {
	block* blockPtr;
	blockPtr = root;
	cout << "freeList : ";
	//���� freeList�� ����ٸ�
	if (blockPtr == NULL) {
		cout << endl;
		return;
	}
	//freeList�� ���� �ʾҴٸ�
	//������ ��� ������
	while (blockPtr->next != NULL) {
		//blockNum(status)�������� ������ش�
		cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
		blockPtr = blockPtr->next;
	}
	//������ ��忡 ����������
	//blockNum(status)�������� ������ش�
	cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
}

//freeList�� ����� �� ������ִ� �޼ҵ�
//input: ����
//output: ����Ʈ�� ������� ��ȯ
bool freeList::isEmpty(){
	return root == NULL;

}

//freeList�� ù��° block�� blockNum�� ��ȯ���ִ� �޼ҵ�
//input: ����
//output: ù��° block�� blockNum
int freeList::getFirstBlockNum() {
	return root->blockNum;
}

//freeList���� delay������ block�� �ִ��� ��ȯ���ִ� �޼ҵ�
//input: ����
//output: delay�� block�� �ִ� �� ��ȯ
bool freeList::isDelay() {
	block* blockPtr;
	blockPtr = root;
	//blockPtr�� NULL�� �ƴҵ���
	while (blockPtr != NULL) {
		//delay������ block�� �ִٸ�
		if (blockPtr->status == DELAY) {
			//true��� return���ش�
			return true;
		}
		//���� ã�� ���ߴٸ� ���� block���� �̵��Ѵ�
		blockPtr = blockPtr->next;
	}
	return false;
}