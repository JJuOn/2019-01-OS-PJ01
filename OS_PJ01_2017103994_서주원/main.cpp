#include <iostream>
#include <ctime>
#include "block.h"
#include "hashQueue.h"

using namespace std;

int main() {
	//modNum: hashing �Ҷ� mod ������ operand
	//bufferNum: ������ buffer�� ����
	//blockNum: ã�� block�� blockNum
	//scenario: getblk�� � �ó��������� ����Ǿ�����
	int modNum,bufferNum,blockNum,scenario;
	//result: getblk�� ���� ���� block
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
