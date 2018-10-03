#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <vector>

using namespace std;

class Tree
{
private:
	struct TreeElem
	{
		int info;
		TreeElem* left;
		TreeElem* right;

		TreeElem() {}
		TreeElem(int x, TreeElem* pLeft = nullptr, TreeElem* pRight = nullptr) : info(x), left(pLeft), right(pRight) {}
	};
	TreeElem* root;

	void add(int x, std::vector<int> positions, TreeElem* root)
	{
		if (!root) {
			throw "Узел не найден";
		}
		if (root->right == nullptr && positions.size() == 1 && positions[0] == 1) {
			root->right = new TreeElem(x);
			return;
		}
		if (root->left == nullptr && positions.size() == 1 && positions[0] == 0) {
			root->left = new TreeElem(x);
			return;
		}
		if (positions.empty()) {
			root->info = x;
			return;
		}
		if (positions.size() == 1 && positions[0] == 1) {
			add(x, vector<int>(), root->right);
		}
		if (positions.size() == 1 && positions[0] == 0) {
			add(x, vector<int>(), root->left);
		}
		int next = positions.front();
		if (next != 0 && next != 1) {
			throw "Недопустимое число";
		}
		positions.erase(positions.begin());
		if (next == 1) {
			add(x, positions, root->right);
		}
		if (next == 0) {
			add(x, positions, root->left);
		}
	}

	friend std::ostream &operator<<(std::ostream &os, TreeElem* root)
	{
		if (root == nullptr) { return os; }
		os << root->info << " ";
		os << root->left;
		os << root->right;
		return os;
	}

	int countOfEvenNumbers(TreeElem* root)
	{
		if (!root) { return 0; }
		return (root->info % 2 == 0 ? 1 : 0) + countOfEvenNumbers(root->right) + countOfEvenNumbers(root->left);
	}

	bool allNumbersIsPositive(TreeElem* root)
	{
		if (!root) {
			return true;
		}
		return root->info > 0 && allNumbersIsPositive(root->left) && allNumbersIsPositive(root->right);
	}

	void deleteLeaves(TreeElem*& root)
	{
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			root = nullptr;
			return;
		}
		if (root->right != nullptr) {
			deleteLeaves(root->right);
		}

		if (root->left != nullptr) {
			deleteLeaves(root->left);
		}
	}

	int size(TreeElem* root) {
		if (!root) {
			return 0;
		}
		return 1 + size(root->right) + size(root->left);
	}

	int sum(TreeElem* root) {
		if (!root) {
			return 0;
		}
		return root->info + sum(root->right) + sum(root->left);
	}

	std::vector<int> lookAtElem(TreeElem*& root, int x, std::vector<int> v)
	{
		if (!root) { return std::vector<int>(); }
		if (root->info == x) { return v; }
		v.push_back(0);
		std::vector<int> v2 = lookAtElem(root->left, x, v);
		if (v2.empty()) {
			v.pop_back();
		}
		else {
			return v2;
		}

		v.push_back(1);
		v2 = lookAtElem(root->right, x, v);
		if (v2.empty()) {
			v.pop_back();
		}
		else {
			return v2;
		}
		return std::vector<int>();
	}

	void deleteAll(TreeElem* root) {
		if (!root) { return; }
		deleteAll(root->left);
		deleteAll(root->right);
		delete root;
	}

	TreeElem* copyTree(TreeElem* root) {
		if (!root) { return nullptr; }
		TreeElem* newElem = new TreeElem(root->info);
		newElem->left = copyTree(root->left);
		newElem->right = copyTree(root->right);
		return newElem;
	}
public:
	Tree() {
		root = new TreeElem();
	}

	Tree(int x) {
		root = new TreeElem(x);
	}

	Tree(Tree& tree) : Tree()
	{
		*this = tree;
	}

	~Tree() {
		deleteAll(root);
	}

	Tree& operator= (Tree& tree) {
		if (this == &tree) { return *this; }
		delete this->root;
		this->root = copyTree(tree.root);
		return *this;
	}

	void add(int x, std::vector<int> positions) {
		if (!root) {
			if (positions.empty()) {
				root = new TreeElem(x);
				return;
			}
			throw "Tree is not exist";
		}
		add(x, positions, root);
	}

	void output() {
		if (!root) {
			cout << "tree is empty" << endl;
			return;
		}
		cout << root;
		cout << endl;
	}

	int countOfEvenNumbers() {
		return countOfEvenNumbers(root);
	}

	bool allNumbersIsPositive() {
		return allNumbersIsPositive(root);
	}

	void deleteLeaves() {
		if (!root) {
			delete root;
			return;
		}
		deleteLeaves(root);
	}

	int getSum() {
		return sum(root);
	}

	int getSize() {
		return size(root);
	}

	double arithmeticMeanOfAllNumbers() { 
		double sum = getSum();
		int quantity = getSize();
		return sum / quantity;
	}

	std::vector<int> lookAtElem(int x) {
		return lookAtElem(root, x, std::vector<int>());
	}
};