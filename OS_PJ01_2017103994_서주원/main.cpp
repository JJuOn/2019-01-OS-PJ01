#include <iostream>
#include <ctime>
#include "block.h"
#include "hashQueue.h"

using namespace std;

int main() {
	int modNum;
	int bufferNum;
	cout << "Enter mod number : ";
	cin >> modNum;
	cout << "Enter buffer number : ";
	cin >> bufferNum;
	hashQueue HQ(modNum);
	HQ.setRandomBuffers(bufferNum);
	HQ.printAll();
	int blockNum;
	cout << "Enter a block number which you want use : ";
	cin >> blockNum;
	block result;
	cout << endl;
	HQ.printAll();
	cout << endl;
	result = HQ.getBlk(blockNum);
	cout << "Get block which has number " << result.blockNum << endl;
	return 0;
}
