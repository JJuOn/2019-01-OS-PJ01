#pragma once
//block의 status를 표시하기 위한 열거형 정의
enum status { LOCK, UNLOCK, DELAY, WRITE };
//linkedList의 한 노드에 해당하는 block 정의
struct block
{
	//block의 번호, 초기값은 0으로 지정
	int blockNum=0;
	//block의 상태, 값에 따라 LOCK,UNLOCK,DELAY,WRITE의 상태를 가짐.
	int status;
	//linkedList에서 다음 노드를 가리키는 block 포인터.
	block* next=NULL;
};