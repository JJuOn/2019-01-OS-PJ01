#pragma once
#include "block.h"
#include "freeList.h"
//hashQueue
class hashQueue {
private:
	//mod연산 operand
	int modNum;
	//block들이 담길 테이블
	block** queue;
	//freeList
	freeList free;
public:
	//hashQueue 기본 생성자
	hashQueue();
	//modNum이 주어진 hashQueue 생성자 
	hashQueue(int modNum);
	//hashQueue 소멸자
	~hashQueue();
	//block를 찾아 해당 block의 pointer 형태로 반환해주는 메소드
	block* retrieveBlock(bool& exist,int blockNum);
	//큐에 item 삽입하는 메소드
	void enQueue(block item);
	//큐에서 해당 blockNum을 가진 block를 삭제하는 메소드
	void deQueue(int blockNum);
	//hashQueue와 freeList 전체를 출력해주는 메소드
	void printAll();
	//임의로 버퍼를 생성해주는 메소드
	void setRandomBuffers(int bufferNum);
	//getBlk 알고리즘
	block getBlk(int blockNum,int& scenario);
	//delay된 block들을 write상태로 바꿔주는 메소드
	void delayToWrite();
	//write된 block들을 unlock상태로 바꿔주는 메소드
	void writeToUnlock();
	//lock된 block들을 delay된 상태로 바꿔주는 메소드
	void lockToDelay();
};