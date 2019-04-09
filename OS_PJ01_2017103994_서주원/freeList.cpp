#include <iostream>
#include "freeList.h"

using namespace std;
//freeList 생성자
//input: 없음
//output: 초기화된 상태의 freeList
freeList::freeList() {
	root = NULL;
}

//freeList 소멸자
//input: 없음
//output: 모든 노드가 삭제된 상태의 freeList
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

//item을 freeList에 삽입해주는 메소드
//input: 삽입할 block type의 item
//output: 해당 block이 추가된 상태의 freeList
void freeList::insertItem(block item) {
	//freeList가 비어있다면
	if (root == NULL) {
		//새로 block을 만들어준다
		root = new block;
		root->blockNum = item.blockNum;
		root->status = item.status;
	}
	//freeList가 비어있지 않다면
	else {
		block* blockPtr;
		blockPtr = root;
		//마지막 노드까지 이동한 후
		while (blockPtr->next != NULL) {
			blockPtr = blockPtr->next;
		}
		//새로 block을 만들어준다
		blockPtr->next = new block;
		blockPtr = blockPtr->next;
		blockPtr->blockNum = item.blockNum;
		blockPtr->status = item.status;
	}
}

//해당 blockNum을 가진 block을 freeList에서 삭제시켜주는 메소드
//input: 삭제할 block의 blockNum
//output: 해당 block이 삭제된 상태의 freeList
void freeList::deleteItem(int blockNum) {
	block* blockPtr;
	blockPtr = root;
	//삭제하고자 하는 block이 root에 있다면,
	if (blockPtr->blockNum == blockNum) {
		block* temp;
		temp = blockPtr;
		blockPtr = blockPtr->next;
		//삭제한다
		delete temp;
		root = blockPtr;
		return;
	}
	//삭제하고자 하는 block이 root에 있지 않다면
	//마지막 노드에 도달하기 전까지
	while (blockPtr->next != NULL) {
		//blockPtr이 가리키고 있는 노드의 다음이 삭제하고자 하는 block의 blockNum이라면
		if (blockPtr->next->blockNum == blockNum) {
			block* temp;
			temp = blockPtr->next;
			blockPtr->next = blockPtr->next->next;
			//삭제한다.
			delete temp;
			return;
		}
		blockPtr = blockPtr->next;
	}
}

//해당 blockNum을 가진 block이 freeList에 존재하는지 반환해주는 메소드
//input: 찾을 block의 blockNum
//output: block의 존재 여부 반환
bool freeList::isExist(int blockNum){
	block* blockPtr;
	blockPtr = root;
	bool found = false;
	//아직 찾고자 하는 block을 찾지 않았고, 마지막 노드에 도달하기 전 까지,
	while (!found && blockPtr->next != NULL) {
		//만약 찾았다면 found를 true로 표시해주고 반복문을 탈출한다
		if (blockPtr->blockNum == blockNum) {
			found = true;
			break;
		}
		//아니라면 다음 노드로 이동한다
		blockPtr = blockPtr->next;
	}
	//마지막 노드가 찾고자 하는 block이라면
	if (blockPtr->blockNum == blockNum) {
		//찾았다고 해준다
		found = true;
	}
	//위 과정을 수행해 노드를 찾았다면
	if (found) {
		cout << "Block exists in freeList" << endl;
	}
	//위 과정을 수행했지만 노드를 찾지 못했다면
	else {
		cout << "Block doesn't exist in freeList" << endl;
	}
	return found;
}

//freeList 전체를 콘솔창에 출력해주는 메소드
//input: 없음
//output: 콘솔창에 출력
void freeList::printFreeList() {
	block* blockPtr;
	blockPtr = root;
	cout << "freeList : ";
	//만약 freeList가 비었다면
	if (blockPtr == NULL) {
		cout << endl;
		return;
	}
	//freeList가 비지 않았다면
	//마지막 노드 전까지
	while (blockPtr->next != NULL) {
		//blockNum(status)형식으로 출력해준다
		cout << blockPtr->blockNum << '(' << blockPtr->status << "),";
		blockPtr = blockPtr->next;
	}
	//마지막 노드에 도달했을때
	//blockNum(status)형식으로 출력해준다
	cout << blockPtr->blockNum << '(' << blockPtr->status << ")\n";
}

//freeList가 비었는 지 출력해주는 메소드
//input: 없음
//output: 리스트가 비었는지 반환
bool freeList::isEmpty(){
	return root == NULL;

}

//freeList의 첫번째 block의 blockNum을 반환해주는 메소드
//input: 없음
//output: 첫번째 block의 blockNum
int freeList::getFirstBlockNum() {
	return root->blockNum;
}

//freeList에서 delay상태인 block이 있는지 반환해주는 메소드
//input: 없음
//output: delay된 block이 있는 지 반환
bool freeList::isDelay() {
	block* blockPtr;
	blockPtr = root;
	//blockPtr이 NULL이 아닐동안
	while (blockPtr != NULL) {
		//delay상태인 block이 있다면
		if (blockPtr->status == DELAY) {
			//true라고 return해준다
			return true;
		}
		//아직 찾지 못했다면 다음 block으로 이동한다
		blockPtr = blockPtr->next;
	}
	return false;
}