#pragma once
#include "block.h"
//HashQueue의 멤버변수로 들어갈 freeList 선언.
class freeList {
private:
	//freeList는 root로 시작하는 linkedList.
	block* root;
public:
	//freeList의 생성자
	freeList();
	//freeList의 소멸자
	~freeList();
	//item을 freeList에 삽입해주는 메소드
	void insertItem(block item);
	//해당 blockNum을 가진 block을 freeList에서 삭제시켜주는 메소드
	void deleteItem(int blockNum);
	//해당 blockNum을 가진 block이 freeList에 존재하는지 반환해주는 메소드
	bool isExist(int blockNum);
	//freeList 전체를 콘솔창에 출력해주는 메소드
	void printFreeList();
	//freeList가 비었는 지 출력해주는 메소드
	bool isEmpty();
	//freeList의 첫번째 block의 blockNum을 반환해주는 메소드
	int getFirstBlockNum();
	//freeList에서 delay상태인 block이 있는 지 반환해주는 메소드
	bool isDelay();
};