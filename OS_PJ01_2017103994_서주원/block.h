#pragma once
enum status { LOCK, UNLOCK, DELAY, WRITE };
struct block
{
	int blockNum=0;
	int status;
	block* next=NULL;
};