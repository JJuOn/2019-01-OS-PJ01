#include <iostream>
#include <ctime>
#include "block.h"
#include "hashQueue.h"

using namespace std;

int main() {
	//modNum: hashing 할때 mod 연산의 operand
	//bufferNum: 생성할 buffer의 개수
	//blockNum: 찾을 block의 blockNum
	//scenario: getblk가 어떤 시나리오에서 진행되었는지
	int modNum,bufferNum,blockNum,scenario;
	//result: getblk를 통해 받은 block
	block result;
	cout << "Enter mod number : ";
	cin >> modNum;
	cout << "Enter buffer number (1~99) : ";
	cin >> bufferNum;
	hashQueue HQ(modNum);
	HQ.setRandomBuffers(bufferNum);
	HQ.printAll();
	cout << "Enter a block number which you want use (-1 to quit) : ";
	cin >> blockNum;
	cout << endl;
	while (blockNum != -1) {
		scenario = 0;
		HQ.printAll();
		cout << endl;
		result = HQ.getBlk(blockNum, scenario);
		cout << "Get block which has number " << result.blockNum << " in scenario " << scenario << endl;
		cout << "Enter a block number which you want use (-1 to quit) : ";
		cin >> blockNum;
		cout << endl;
	}
	return 0;
}
