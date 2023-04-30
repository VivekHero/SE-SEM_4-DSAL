//============================================================================
// Name        : Assignment_8(OBST).cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node {
	Node* left, * right;
	int data;
	int level;
public:
	Node() {
		level = 0;
		left = right = NULL;
		data = 0;
	}
	friend class OBST;
};

class OBST {
	int* keys;
	int* frequency;
	int totalKeys;
	Node* root;
	int totalCost;
public:
	OBST(int x) {
		totalCost = 0;
		root = NULL;
		totalKeys = x;
		keys = new int[totalKeys];
		frequency = new int[totalKeys];
		for (int i = 0; i < totalKeys; i++) {
			keys[i] = 0;
			frequency[i] = 0;
		}
	}

	void enterKeys_Frequency() {
		for (int i = 0; i < totalKeys; i++) {
			cout << "Enter the Key " << i + 1 << endl;
			cin >> keys[i];
			cout << "Enter the frequency of Key: " << i + 1 << endl;
			cin >> frequency[i];
		}
	}

	void sortDescending() {
		for (int i = totalKeys; i >= 0; i--) {
			for (int j = totalKeys; j > totalKeys - i; j--) {
				if (frequency[j] > frequency[j - 1]) {
					int t1 = frequency[j];
					frequency[j] = frequency[j - 1];
					frequency[j - 1] = t1;
					int t2 = keys[j];
					keys[j] = keys[j - 1];
					keys[j - 1] = t2;
				}
			}
		}
	}

	void add_node(int x) {
		Node* temp = new Node();
		temp->data = x;
		temp->left = NULL;
		temp->right = NULL;
		Node* current = root;
		if (root == NULL) {
			root = temp;
		}
		else {
			while (true) {
				if (x < current->data) {
					if (current->left != NULL) {
						current = current->left;
					}
					else {
						current->left = temp;
						break;
					}
				}
				else {
					if (current->right != NULL) {
						current = current->right;
					}
					else {
						current->right = temp;
						break;
					}

				}
			}
		}
	}

	void buildOBST() {
		sortDescending();
		for (int i = 0; i < totalKeys; i++) {
			int x = keys[i];
			add_node(x);
		}
		cout << "Tree is built" << endl;
		cout << "Pre-order traversal of tree : ";
		preorder(root);
		cout << endl;
	}

	int search(int x) {
		Node* temp = root;
		int level = 0;
		while (temp != NULL) {
			if (temp->data == x) {
				return level;
			}
			else if (temp->data > x) {
				temp = temp->left;
				level++;
			}
			else if (temp->data < x) {
				temp = temp->right;
				level++;
			}
		}
		return 0;
	}

	void calculateCost() {
		sortDescending();
		cout << "Keys	 Frequency	  Level	   Search Cost" << endl;
		for (int i = 0; i < totalKeys; i++) {
			int x = keys[i];
			int c1 = 0;
			int level = search(x);
			c1 = frequency[i] * (level + 1);
			level++;
			cout << keys[i] << "		   " << frequency[i] << "		 " << level - 1 << "		 " << c1 << endl;
			totalCost = totalCost + c1;
		}
		cout << "Total cost = " << totalCost << endl;
	}
	void preorder(Node* root) {
		if (root != NULL) {
			cout << root->data << " ";
			preorder(root->left);
			preorder(root->right);
		}
	}
};
int main() {
	int n;
	cout << "Enter total no of keys" << endl;
	cin >> n;
	OBST o1(n);
	char ch = 'y';
	bool buildTree = 0;
	bool inputGiven = 0;
	while (ch != 'n') {
		cout << "----- MENU -----" << endl;
		cout << "1. Provide keys and their frequency" << endl;
		cout << "2. Build Optimal Binary search tree (OBST)" << endl;
		cout << "3. Calculate search cost" << endl;
		cout << "----------" << endl;
		int choice;
		cout << "Enter your choice" << endl;
		cin >> choice;
		if (choice == 1) {
			if (inputGiven == 0) {
				inputGiven = 1;
				o1.enterKeys_Frequency();
			}
			else {
				cout << "Keys are already provided" << endl;
			}
		}
		else if (choice == 2) {
			o1.buildOBST();
			buildTree = 1;
		}
		else if (choice == 3) {
			if (buildTree == 0) {
				cout << "Tree hasn't build yet, build tree first" << endl;
			}
			else {
				o1.calculateCost();
			}
		}
		else {
			cout << "You have entered a wrong choice" << endl;
		}

		cout << "Do you want to continue (y/n) - " << endl;
		cin >> ch;
	}
	return 0;
}



