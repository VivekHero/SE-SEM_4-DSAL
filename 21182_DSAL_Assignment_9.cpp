// Reference - Abhishek Ulagadde (GitHub Link -- https://github.com/abhidada1624)
//============================================================================
// Name        : Assignment_9.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class Node{
	string key;
	string meaning;
	Node *left, *right;
	int ht;


public:
	Node(string k, string m){
		key = k;
		meaning = m;
		left = right = NULL;
		ht = 1;
	}
	friend class AVLTree;
};

class AVLTree{
public:
	Node *root;

	AVLTree(){
		root = NULL;
	}

	void makenull(){
		root = NULL;
	}

	int height(Node *temp){
		int lh,rh;
		if (temp == NULL){
			return 0;
		}
		if (temp->left == NULL){
			lh = 0;
		}
		else{
			lh = 1 + temp->left->ht;
		}
		if (temp->right == NULL){
			rh = 0;
		}
		else{
			rh = 1 + temp->right->ht;
		}
		if (lh > rh){
			return lh;
		}
		return rh;
	}

	int balanceFactor(Node *temp){
			int lh,rh;
			if (temp == NULL){
				return 0;
			}
			if (temp->left == NULL){
				lh = 0;
			}
			else{
				lh = 1 + temp->left->ht;
			}
			if (temp->right == NULL){
				rh = 0;
			}
			else{
				rh = 1 + temp->right->ht;
			}
			return (lh - rh);
	}

	Node *rotateleft(Node *curr){
		Node *temp;
		temp = curr->right;
		curr->right = temp->left;
		temp->left = curr;
		curr->ht = height(curr);
		temp->ht = height(temp);
		return (temp);
	}

	Node *rotateright(Node *curr){
		Node *temp;
		temp = curr->left;
		curr->left = temp->right;
		temp->right = curr;
		curr->ht = height(curr);
		temp->ht = height(temp);
		return temp;
	}

	Node *RR(Node *curr){
		curr = rotateleft(curr);
		return (curr);
	}
	Node *LL(Node *curr){
		curr = rotateright(curr);
		return (curr);
	}

	Node *LR(Node *curr){
		curr->left = rotateleft(curr);
		curr = rotateright(curr);
		return (curr);
	}

	Node *RL(Node *curr){
		curr->right = rotateright(curr->right);
		curr = rotateleft(curr);
		return (curr);
	}

	Node *insert(Node *temp, string k, string m){
		if (temp == NULL){
			Node *newNode = new Node(k, m);
			return newNode;
		}

		if (k < temp->key){
			temp->left = insert(temp->left, k, m);
		}
		else if (k > temp->key){
			temp->right = insert(temp->right, k , m);
		}
		else{
			return temp;
		}

		temp->ht = height(temp);
		int bf = balanceFactor(temp);

		// LL
		if (bf == 2 && k < temp->left->key){
			return rotateright(temp);
		}

		// RR
		if (bf == -2 && k > temp->right->key){
			return rotateleft(temp);
		}

		// LR
		if (bf == 2 && k > temp->left->key){
			temp->left = rotateleft(temp->left);
			return rotateright(temp);
		}

		// RL
		if (bf == -2 && k < temp->right->key){
			temp->right = rotateright(temp->right);
			return rotateleft(temp);
		}
		return temp;
	}

	Node *deletion(Node *r, string k){
		if (root == NULL){
			return r;
		}
		else if (k < r->key){
			r->left = deletion(r->left, k);
		}
		else if (k > r->key){
			r->right = deletion(r->right, k);
		}
		else{
			if (r->left == NULL || r->right == NULL){
				Node *temp;
				if (r->left){
					temp = r->left;
				}
				else{
					temp = r->right;
				}

				if (temp == NULL){
					temp = r;
					r = NULL;
				}
				else{
					root->key = temp->key;
				}
				delete temp;
			}

			else{
				Node *min = minNode(r->right);
				r->key = min->key;
				r->meaning = min->meaning;
				r->right = deletion(r->right, min->key);
			}
		}

		if (r == NULL){
			return r;
		}

		r->ht = height(r);
		int bf = balanceFactor(r);

		if (bf == 2 && balanceFactor(r->left) > 0){
			return rotateright(r);
		}

		if (bf == -2 && balanceFactor(r->right) <= 0){
			return rotateleft(r);
		}

		if (bf == 2 && balanceFactor(r->right) < 0){
			r->left = rotateleft(r->left);
			return rotateright(r);
		}

		if (bf == -2 && balanceFactor(r->right) > 0){
			r->right = rotateright(r->right);
			return rotateleft(r);
		}

		return r;
	}

	Node *minNode(Node *root){
		Node *temp = root;
		while (temp->left != NULL){
			temp = temp->left;
		}
		return (temp);
	}

	Node *search(string s){
		Node *temp = root;
		while (temp != NULL){
			if (temp->key == s){
				return (temp);
			}
			else if (s < temp->key){
				temp = temp->left;
			}
			else{
				temp = temp->right;
			}
		}
		return NULL;
	}

	int comparisons(string s){
		Node *temp = root;
		int count = 0;
		while (temp != NULL){
			count++;
			if (temp->key == s){
				return count;
			}
			else if (temp->key > s){
				temp = temp->left;
			}
			else{
				temp = temp->right;
			}
		}
		return -1;
	}

	void update(string k, string newm){
		Node *temp = search(k);
		if (temp == NULL){
			cout << "Word is not present" << endl;
			return;
		}
		temp->meaning = newm;
	}

	void inorder(Node *root){
		if (root == NULL){
			return;
		}
		inorder(root->left);
		cout << root->key << " : " << root->meaning << endl;
		inorder(root->right);
	}

	void descending(Node *root){
		if (root == NULL){
			return;
		}
		descending(root->right);
		cout << root->key << " : " << root->meaning << endl;
		descending(root->left);
	}

	void preorder(Node *root){
		if (root == NULL){
			return;
		}
		cout << root->key << " : " << root->meaning << endl;
		preorder(root->left);
		preorder(root->right);
	}

	void postorder(Node *root){
		if (root == NULL){
			return;
		}
		postorder(root->left);
		postorder(root->right);
		cout << root->key << " : " << root->meaning << endl;
	}

	void addNode(string k, string m){
		root = insert(root, k, m);
	}

	void deleteNode(string k){
		root = deletion(root, k);
	}
};

int main(){
	AVLTree obj;
	int n;
	string k,m;
	int choice;

	do{
		cout << "----- MENU -----" << endl;
		cout << "1. Add word" << endl;
		cout << "2. Delete word" << endl;
		cout << "3. Update word's meaning" << endl;
		cout << "4. Display" << endl;
		cout << "5. Search a word" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice : " << endl;
		cin >> choice;

		switch(choice){
			case 1:{
				cout << "Enter the number of words to be inserted" << endl;
				cin >> n;
				for (int i = 0; i < n; i++){
					string word,meaning;
					cout << "Enter word: " << endl;
					cin >> word;
					cout << "Enter meaning" << endl;
					cin >> meaning;
					obj.addNode(word, meaning);
				}
				break;
			}

			case 2:{
				cout << "Enter the word to be deleted" << endl;
				cin >> k;
				obj.deleteNode(k);
				cout << "Word deleted " << endl;
				break;
			}
			case 3:{
				cout << "Enter the word to be updated : " << endl;
				cin >> k;
				cout << "Enter it's new meaning" << endl;
				cin >> m;
				obj.update(k, m);
				break;
			}
			case 4:{
				cout << "a. Ascending" << endl;
				cout << "b. Descending" << endl;
				cout << "c. Pre-order" << endl;
				cout << "d. Post-order" << endl;
				char ch;
				cout << "Enter your choice : " << endl;
				cin >> ch;
				if (ch == 'a'){
					cout << "Ascending" << endl;
					cout << "Key" << " Meaning" << endl;
					obj.inorder(obj.root);
				}
				else if (ch == 'b'){
					cout << "Descending" << endl;
					cout << "Key" << " Meaning" << endl;
					obj.descending(obj.root);
				}
				else if (ch == 'c'){
					cout << "Pre-order" << endl;
					cout << "Key" << " Meaning" << endl;
					obj.preorder(obj.root);
				}
				else if (ch == 'd'){
					cout << "Post-order" << endl;
					cout << "Key" << " Meaning" << endl;
					obj.postorder(obj.root);
				}
				break;
			}
			case 5:{
				cout << "Enter the word to be searched" << endl;
				cin >> k;
				int comp = obj.comparisons(k);
				if (comp == -1){
					cout << "Word is not present" << endl;
				}
				else{
					cout << "Number of comparisons required : " << comp << endl;
				}
				break;
			}

			case 6:{
				cout << "Thank you for visiting" << endl;
				exit(0);
				break;
			}

			default:{
				cout << "You have entered wrong choice" << endl;
			}
		}
	}while(choice != 6);

}
