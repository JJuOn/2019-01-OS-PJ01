#pragma once
//block�� status�� ǥ���ϱ� ���� ������ ����
enum status { LOCK, UNLOCK, DELAY, WRITE };
//linkedList�� �� ��忡 �ش��ϴ� block ����
struct block
{
	//block�� ��ȣ, �ʱⰪ�� 0���� ����
	int blockNum=0;
	//block�� ����, ���� ���� LOCK,UNLOCK,DELAY,WRITE�� ���¸� ����.
	int status;
	//linkedList���� ���� ��带 ����Ű�� block ������.
	block* next=NULL;
};