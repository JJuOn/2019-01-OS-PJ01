#include <iostream>
#include <ctime>
#include <windows.h>
#include "hashQueue.h"

using namespace std;
//hashQueue 기본 생성자
//input: 없음
//output: 초기화된 상태의 hashQueue
hashQueue::hashQueue() {
	this->modNum = 0;
}

//modNum이 주어진 hashQueue 생성자
//input: mod 연산의 operand
//output: modNum이 초기화되고, modNum에 따라 queue의 동적할당이 이루어진 hashQueue
hashQueue::hashQueue(int modNum) {
	this->modNum = modNum;
	//modNum의 개수만큼 queue를 동적할당 해준다
	this->queue = new block*[modNum];
	//동적할당 시켜준 queue안에서
	for (int i = 0; i < modNum; i++) {
		//queue들을 NULL로 초기화 시켜준다
		queue[i] = NULL;
	}
	//freeList를 초기화시켜준다
	freeList();
}

//hashQueue 소멸자
//input: 없음
//output: 모든 노드가 지워진 hashQueue
hashQueue::~hashQueue() {
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		//각각의 hashQueue 한 행씩 가리키게함
		blockPtr = queue[i];
		//hashQueue 한 행씩 삭제
		while (blockPtr != NULL) {
			block* temp = blockPtr->next;
			delete blockPtr;
			blockPtr = temp;
		}
		//마지막남은 block을 NULL
		queue[i] = NULL;
	}
	//hashQueue 전체 삭제
	delete[] queue;
}

//block을 찾아 해당 block의 pointer 형태로 반환해주는 메소드
//input: 반환여부인 exist, 찾을 block의 blockNum
//output: 찾은 block의 pointer
block* hashQueue::retrieveBlock(bool& exist,int blockNum) {
	//hashQueue에 접근하기 위해 block mod modNum으로 index를 구함
	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
	bool found = false;
	//아직 찾지않았고, 마지막 노드에 도달하기 전까지
	while (!found && blockPtr->next != NULL) {
		//blockPtr이 찾고자하는 block이라면
		if (blockPtr->blockNum == blockNum) {
			//찾았다고 해주고 반복문 탈출
			found = true;
			break;
		}
		//아직 못찾았으면 다음 노드로 이동
		blockPtr = blockPtr->next;
	}
	//마지막 노드가 찾고자 하는 block이라면
	if (blockPtr->blockNum == blockNum) {
		//찾았다고 해준다
		found = true;
	}
	//찾았다면
	if (found) {
		cout << "Block exists in hashQueue" << endl;
		exist = found;
		return blockPtr;
	}
	//못 찾았다면
	else {
		cout << "Block doesn't exists in hashQueue" << endl;
		exist = found;
		return NULL;
	}
}

//큐에 item 삽입하는 메소드
//input: 삽입할 block
//output: 새로운 아이템이 삽입된 hashQueue
void hashQueue::enQueue(block item) {
	//hashQueue에 접근하기 위해 blockNum mod modNum으로 index 계산
	int index = item.blockNum % this->modNum;
	//큐가 비어있다면
	if (this->queue[index] == NULL) {
		//새로운 block 생성
		queue[index] = new block;
		queue[index]->blockNum = item.blockNum;
		queue[index]->status = item.status;
		//삽입하고자하는 block의 status가 delay라면 freeList에 삽입, 또는 lock이 아니라면 50% 확률로(rand()%2에 의해) freeList에 삽입
		if (queue[index]->status == DELAY || (rand() % 2 && queue[index]->status != LOCK)) {
			this->free.insertItem(*queue[index]);
		}
	}
	//큐가 비어있지 않다면
	else {
		block* blockPtr;
		blockPtr = queue[index];
		//마지막 노드로 이동한다
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		//마지막 노드 다음에 새로운 block 생성
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
		//삽입하고자하는 block의 status가 delay라면 freeList에 삽입, 또는 lock이 아니라면 50% 확률로(rand()%2에 의해) freeList에 삽입
		if (blockPtr->status == DELAY || (rand() % 2 && blockPtr->status != LOCK)) {
			this->free.insertItem(*blockPtr);
		}
	}
}

//큐에서 해당 blockNum을 가진 block을 삭제하는 메소드
//input: 삭제한 block의 blockNum
//output: 해당 block이 삭제된 hashQueue
void hashQueue::deQueue(int blockNum) {
	//hashQueue에 접근하기 위해 blockNum mod modNum으로 index 계산
	int index = blockNum % modNum;
	block* blockPtr;
	blockPtr = queue[index];
	//삭제하고자 하는 block이 제일 앞에 있다면 삭제
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		queue[index] = blockPtr;
		delete temp;
		return;
	}
	//제일 앞에 있지 않다면
	//마지막노드 전까지
	while (blockPtr->next != NULL) {
		//현재 노드의 다음노드가 삭제하고자 하는 block이라면 삭제
		if (blockPtr->next->blockNum == blockNum) {
			block* temp;
			temp = blockPtr->next;
			blockPtr->next = blockPtr->next->next;
			delete temp;
			return;
		}
		//아직 못찾았다면 다음 노드로 이동
		blockPtr = blockPtr->next;
	}
}

//hashQueue와 freeList 전체를 출력해주는 메소드
//input: 없음
//output: 해쉬큐의 모든 노드 출력
void hashQueue::printAll() {
	//이전에 출력되었던 내용 지우기
	system("cls");
	//status 표시
	cout << "0:LOCK 1:UNLOCK 2:DELAY 3:WRITE\n";
	//queue의 모든 행에 대하여
	for (int i = 0; i < modNum; i++) {
		cout << "hashQueue " << i << " : ";
		block* blockPtr;
		blockPtr = queue[i];
		//현재 노드가 NULL이 아닐때 까지
		if (blockPtr != NULL) {
			//마지막노드 전까지
			while (blockPtr->next != NULL) {
				//blockNum(status)형식으로 출력해준다
				cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
				//다음노드로 이동
				blockPtr = blockPtr->next;
			}
			//마지막 노드에서
			//blockNum(status)형식으로 출력해준다
			cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
		}
	}
	//freeList 출력
	this->free.printFreeList();
}

//임의로 버퍼를 생성해 주는 메소드
//input: 생성할 버퍼의 갯수
//output: 생성된 버퍼가 삽입된 hashQueue
void hashQueue::setRandomBuffers(int bufferNum) {
	block* temp;
	//bufferNum만큼 동적할당 해준다
	temp = new block[bufferNum];
	srand(time(0));
	for (int i = 0; i < bufferNum; i++) {
		//1~99사이의 수를 blockNum으로 해준다
		temp[i].blockNum = rand() % 99 + 1;
		//status는 lock,unlock,delay,write 네 가지중 하나를 랜덤으로 부여한다
		temp[i].status = rand() % 4;
		//중복된 blockNum을 생성하는것을 방지
		for (int j = 0; j < i; j++) {
			if (temp[i].blockNum == temp[j].blockNum) {
				i = i - 1;
				break;
			}
		}
	}
	/* 생성된 버퍼 확인
	for (int i = 0; i < bufferNum; i++) {
		cout << i + 1 << ":" << temp[i].blockNum << endl;
	}
	*/
	//생성한 노드들을 hashQueue에 삽입해준다
	for (int i = 0; i < bufferNum; i++) {
		this->enQueue(temp[i]);
	}
	delete[] temp;
}

//getBlk 알고리즘
//input: 사용하고자하는 block의 blockNum
//output: 사용하고자 하는 block 반환, scenario 반환
block hashQueue::getBlk(int blockNum,int& scenario) {
	bool found = false;
	bool exist = false;
	block* blockPtr=NULL;
	//block을 반환받지 않았을때까지 반복수행
	while (!found) {
		blockPtr = this->retrieveBlock(exist, blockNum);
		//block이 존재할 때(시나리오 1,5)
		if (exist) {

			//찾고자 하는 block이 LOCK 상태라면(시나리오 5)
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
			//그렇지 않으면 LOCK 상태로 만들어주고 block을 반환한다(시나리오 1)
			blockPtr->status = LOCK;
			free.deleteItem(blockNum);
			if (scenario == 0)
				scenario = 1;
			found = true;
		}
		//block이 존재하지 않을 때(시나리오 2,3,4)
		else {
			//freeList가 비어있다면 (시나리오 4)
			if (free.isEmpty()) {
				Sleep(3000);
				this->lockToDelay();
				if (scenario == 0)
					scenario = 4;
				continue;
			}
			//freeList에 DELAY 상태인 block이 있다면 (시나리오 3)
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
			//free buffer를 찾았을 때 (시나리오 2)
			//지울 block의 blockNum을 가져온다
			int deletedBlockNum = free.getFirstBlockNum();
			//freeList에서 해당 block를 삭제하고
			free.deleteItem(deletedBlockNum);
			//동시에 hashQueue에서도 삭제한다
			this->deQueue(deletedBlockNum);
			//사용하고자 하는 blockNum을 가진 block을 만들어주고
			block newBlock;
			newBlock.blockNum = blockNum;
			//LOCK 상태로 만들어 준 후
			newBlock.status = LOCK;
			//HashQueue에 삽입한다
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

//delay된 block들을 write상태로 바꿔주는 메소드
//input: 없음
//output: delay된 블록들의 상태가 write로 바뀜
void hashQueue::delayToWrite() {
	//모든 hashQueue의 행마다 진행한다
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//현재 blockPtr이 NULL이 아닐 때까지
		while (blockPtr != NULL) {
			//block이 DELAY 상태라면
			if (blockPtr->status == DELAY) {
				//WRITE 상태로 바꿔주고
				blockPtr->status = WRITE;
				//freeList에서 삭제한다
				free.deleteItem(blockPtr->blockNum);
			}
			blockPtr = blockPtr->next;
		}
	}
}

//write된 block들을 unlock상태로 바꿔주는 메소드
//input: 없음
//output: write된 블록들의 상태가 unlock로 바뀜
void hashQueue::writeToUnlock() {
	//모든 hashQueue의 행마다 진행한다
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//현재 blockPtr이 NULL이 아닐 때까지
		while (blockPtr != NULL) {
			//block이 WRITE 상태라면
			if (blockPtr->status == WRITE) {
				//UNLOCK 상태로 바꿔주고
				blockPtr->status = UNLOCK;
				//freeList에 삽입한다
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}

//lock된 block들을 delay상태로 바꿔주는 메소드
//input: 없음
//output: lock된 블록들의 상태가 delay로 바뀜
void hashQueue::lockToDelay() {
	//모든 hashQueue의 행마다 진행한다
	for (int i = 0; i < this->modNum; i++) {
		block* blockPtr;
		blockPtr = queue[i];
		//현재 blockPtr이 NULL이 아닐 때까지
		while (blockPtr != NULL) {
			//block이 LOCK 상태라면 50% 확률로
 			if (blockPtr->status == LOCK && rand()%2 ) {
				//DELAY 상태로 바꿔주고 
				blockPtr->status = DELAY;
				//freeList에 삽입한다
				free.insertItem(*blockPtr);
			}
			blockPtr = blockPtr->next;
		}
	}
}