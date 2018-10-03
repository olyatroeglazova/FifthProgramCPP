#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <vector>
#include "BinaryTree.h"

int main(){
	Tree* tree = new Tree(9);
	tree->output();
	cout << endl;

	tree->deleteLeaves();
	tree->output();
	cout << endl;

	tree->add(50, vector<int>());

	vector<int> v;
	v.push_back(1);
	tree->add(70, v);

	v.clear();
	v.push_back(0);
	tree->add(20, v);

	v.push_back(1);
	tree->add(33, v);

	v.pop_back();
	v.push_back(0);
	tree->add(10, v);
	
	v.clear();
	v.push_back(1);
	v.push_back(0);
	tree->add(60, v);

	v.pop_back();
	v.push_back(1);
	tree->add(100, v);
	tree->output();
	cout << endl;

	cout << "Count even: " << tree->countOfEvenNumbers() << endl;
	cout << endl;

	cout << "Check all positive is: " << tree->allNumbersIsPositive() << endl;
	cout << endl;

	tree->add(-1, v);
	tree->output();
	cout << endl;

	cout << "Check all positive is: " << tree->allNumbersIsPositive() << endl;
	cout << endl;

	cout << "Arithmetic mean: " << tree->arithmeticMeanOfAllNumbers() << endl;
	cout << endl;

	cout << "find -1, path: ";
	std::vector<int> v2 = tree->lookAtElem(-1);
	for (int i = 0; i< v2.size(); i++) {
		cout << v2[i] << " ";
	}
	cout << endl;
	cout << endl;

	system("pause");
	return 0;
}