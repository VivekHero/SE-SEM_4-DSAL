//============================================================================
// Name        : Assignment2.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <stack>
#include <queue>
using namespace std;
#define max 50



class Node{
	int data;
	Node *left,*right;

public:
	Node(int d){
		data = d;
		left = right = NULL;
	}
	friend class BinaryTree;

};

class Stack{
	int top;
	Node *arr[max];

public:
	Stack(){
		top = -1;
	}

	bool isEmpty(){
		if (top == -1){
			return true;
		}
		return false;
	}

	bool isFull(){
		if (top == max - 1){
			return true;
		}
		return false;
	}

	void push(Node * obj){
		if (isFull()){
			cout << "Stack is full" << endl;
		}
		else{
			top++;
			arr[top] = obj;
		}
	}

	Node * pop(){
		Node *rn;
		if (!isEmpty()){
		  rn = arr[top];
		  top--;
		  return rn;
		}
		else{
			cout << "Stack is empty" << endl;
		}
		return NULL;
	}

	Node *topofStack(){
		return arr[top];
	}

};

class Queue{
	int front,rear;
	Node * arr[max];
public:
	Queue(){
		front = rear = -1;
	}

	bool isEmpty(){
		if (front == -1 && rear == -1){
			return true;
		}
		return false;
	}

	bool isFull(){
		if ((front == 0 && rear == max - 1) || (front == rear + 1)){
			return true;
		}
		return false;
	}

	void enqueue(Node * obj){
		if (isFull()){
			cout << "The queue is full" << endl;

		}
		else if (isEmpty()){
			front = rear = 0;
			arr[rear] = obj;
		}
		else{
			rear++;
			arr[rear] = obj;
		}
	}

	Node * dequeue(){
		if (isEmpty()){
			cout << "The queue is empty" << endl;
			cout << "Nothing to remove" << endl;
			return NULL;
		}
		else{
			Node * temp = arr[front];
			front++;
			return temp;
		}
	}

	Node *getfront(){
		return arr[front];
	}
};

class BinaryTree{
public:
	Node *root;

public:
	// Recursive 1
	Node *buildTree(Node *root){
		int data;
		cout << "Enter the data: " << endl;
		cin >> data;
		root = new Node(data);

		if (root->data == -1){
			return NULL;
		}

		cout << "Enter the left of " << root->data << " : " << endl;
		root->left = buildTree(root->left);
		cout << "Enter the right of " << root->data << " : " << endl;
		root->right = buildTree(root->right);

		return root;
	}

	// Recursive 2
	Node * build(Node *root){
		int data;
		char ch;
		cout << "Enter the data: " << endl;
		cin >> data;
		root = new Node(data);

		cout << "Do you want to enter in the left of " << root->data << " ?" << endl;
		cin >> ch;

		if (ch == 'y' || ch == 'Y'){
			cout << "Enter the left of " << root->data << " : " << endl;
			root->left = build(root->left);
		}


		cout << "Do you want to enter in the right of " << root->data << " ?" << endl;
		cin >> ch;
		if (ch == 'y' || ch == 'Y'){
			cout << "Enter the right of " << root->data << " : " << endl;
			root->right = build(root->right);
		}



		return root;
	}

	Node * copytree(Node *root){
		if (root == NULL){
			return NULL;
		}

		Node *copy = new Node(root->data);
		copy->left = copytree(root->left);
		copy->right = copytree(root->right);
		return copy;
	}

//	Node * operator = (Node *root){
//		root = copytree(root);
//		return root;
//	}

	Node *operator = (BinaryTree &obj){
		obj.root = this->root;
		return obj.root;
	}


	void preorder(Node *root){
		if (root == NULL){
			return;
		}
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);


	}

	void inorder(Node *root){
		if (root == NULL){
			return;
		}
		inorder(root->left);
		cout << root->data << "  ";
		inorder(root->right);
	}
	void postorder(Node *root){
			if (root == NULL){
				return;
			}
			postorder(root->left);
			postorder(root->right);
			cout << root->data << " ";
	}

	void mirror(Node *root){
		if (root == NULL){
			return;
		}
		Node *ptr;
		mirror(root->left);
		mirror(root->right);
		ptr = root->left;
		root->left = root->right;
		root->right = ptr;
	}

	int heightRecursive(Node *root){
		if (root == NULL){
			return 0;
		}
		int left_height = heightRecursive(root->left);
		int right_height = heightRecursive(root->right);

		if (left_height > right_height){
			return (left_height + 1);
		}
		else{
			return (right_height + 1);
		}
	}

	int leaves_r(Node *root){
		if (root == NULL){
			return 0;
		}
		else if (root->left == NULL && root->right == NULL){
			return 1;
		}
		else{
			return (leaves_r(root->left) + leaves_r(root->right));
		}
	}

	int totalInternal_r(Node *root){
		 if (root == NULL || (root->left == NULL && root->right == NULL)){
		        return 0;
		  }
		  int l_i = totalInternal_r(root->left);
		  int r_i = totalInternal_r(root->right);
		  int ans = l_i + r_i + 1;
		  return ans;
	}

	void delete_r(Node *root){
		if (root == NULL){
			return;
		}
		delete_r(root->left);
		delete_r(root->right);

		cout << "\n Deleting node: " << root->data;
		delete root;
	}
	/***********
	 * RECURSIVE ENDS
	 */


	/* ITERATIVE STARTS*/

	  Node * CreateNode(int data){
	        Node * newNode = new Node(data);

	        if (!newNode){
	            cout << "Memory error" << endl;
	            return NULL;
	        }
	        return newNode;
	   }


	Node * insert(Node *root, int data){
		if (root == NULL){
			root = CreateNode(data);
			return root;
		}

		queue <Node*> q;
		q.push(root);

		while(!q.empty()){
			Node *temp = q.front();
			q.pop();

			cout << "Enter the left and right of " << temp->data << endl;

			if (temp->left!= NULL){
				q.push(temp->left);
			}
			else{
				temp->left = CreateNode(data);
			}

			if (temp->right != NULL){
				q.push(temp->right);
			}
			else{
				temp->right = CreateNode(data);
			}
		}
		return NULL;

	}
	void inorder_iterative(Node *root){
			Stack sobj;
			while (true){

				while (root != NULL){
					sobj.push(root);
					root = root->left;
				}
				if (sobj.isEmpty()){
					return;
				}
				root = sobj.pop();
				cout << root->data << " -> ";
				root = root->right;
		}
	}

	void iterative_preorder(Node *root){
		stack <Node *> st;
		st.push(root);
		while (!st.empty()){
			Node *temp = st.top();
			st.pop();
			cout << temp->data << " -> ";
			if (temp->right){
				st.push(temp->right);
			}
			if (temp->left){
				st.push(temp->left);
			}
		}
	}
	void iterative_postorder(Node *root){
			if (root == NULL){
				return;
			}
			Stack s;
			Stack s1;
			Node *temp = root;

			while (!s.isEmpty()|| temp != NULL){
				if (temp != NULL){
					if (temp->right != NULL){
						s1.push(temp->right);
					}
					s.push(temp);
					temp = temp->left;
				}
				else{
					temp = s.topofStack();
					if (!s1.isEmpty() && temp->right == s1.topofStack()){
						temp = s1.pop();
					}
					else{
						cout << temp->data << " -> ";
						s.pop();
						temp = NULL;
					}
				}
			}
		}

	int height_iterative(Node *root){
		if (root == NULL){
			return 0;
		}
		queue <Node *> q;
		q.push(root);
		int h = 0;
		while (!q.empty()){
			h++;
			for (int i = 0; i < q.size(); i++){
				Node *temp = q.front();
				q.pop();
				if (temp->left){
					q.push(temp->left);
				}
				if (temp->right){
					q.push(temp->right);
				}
			}
		}
		return h;
	}

	int calculateLeafNodes(Node *root){
		int count = 0;
		queue <Node *> q;
		q.push(root);

		while (!q.empty()){
			Node *temp = q.front();
			q.pop();

			if (temp->left == NULL && temp->right == NULL){
				count++;
			}

			if (temp ->left){
				q.push(temp->left);
			}
			if (temp->right){
				q.push(temp->right);
			}
		}
		return count;
	}

	int calculateInternalNodes(Node *root){
		int count = 0;
		queue <Node *> q;
		q.push(root);

		while (!q.empty()){
			Node *temp = q.front();
			q.pop();

			if ((temp->left != NULL && temp->right != NULL) || (temp->left == NULL && temp->right != NULL) || (temp->left != NULL && temp->right == NULL)){
				count++;
			}
			if (temp->left){
				q.push(temp->left);
			}
			if (temp->right){
				q.push(temp->right);
			}
		}

		return count;
	}

	void swaptree_iter(Node *root){
		queue <Node *> q;
		q.push(root);

		while (!q.empty()){
			Node *temp = q.front();
			q.pop();
			Node *store = temp->left;
			temp->left = temp->right;
			temp->right = store;

			if (temp->left){
				q.push(temp->left);
			}
			if (temp->right){
				q.push(temp->right);
			}
		}
	}

	void levelOrderDisplay(Node *root){
		queue <Node *> q;
		q.push(root);
		q.push(NULL);

		while (!q.empty()){
			Node *temp = q.front();
			q.pop();

			if (temp == NULL){
				cout << endl;
				if (!q.empty()){
					q.push(NULL);
				}
			}
			else{
				cout << temp->data << " ";
				if (temp->left){
					q.push(temp->left);

				}
				if (temp->right){
					q.push(temp->right);
				}
			}

		}
	}



	void deletetree_iter(Node *root){
		queue <Node *> q;
		q.push(root);

		while (!q.empty()){
			Node *temp = q.front();
			q.pop();

			if (temp->left){
				q.push(temp->left);
			}
			if (temp->right){
				q.push(temp->right);
			}
			delete temp;
		}
		root = NULL;
	}

	void display(Node *root){
		if (root == NULL){
			cout << "Binary Tree is empty" << endl;
			return;
		}
		cout << "-- PREORDER TRAVERSAL--" << endl;
		preorder(root);
		cout << endl;
		cout << "-- INORDER TRAVERSAL--" << endl;
		inorder(root);
		cout << endl;
		cout << "--POSTORDER TRAVERSAL--" << endl;
		postorder(root);
		cout << endl;

		cout << "In-order iteratively" << endl;
		inorder_iterative(root);
		cout << endl;

		cout << "Pre-order iteratively" << endl;
//		preorder_iterative(root);
		iterative_preorder(root);
		cout << endl;

		cout << "Post-order iteratively" << endl;
//		postorder_iterative(root);
		iterative_postorder(root);
		cout << endl;

	}


};

int main(){
	BinaryTree b1, b2;
	b1.root = b1.build(b1.root);
	int choice1, choice2;
	do{
		cout << "*********************MENU*********************" << endl;
		cout << "1. Recursive: " << endl;
		cout << "2. Iterative: " << endl;
		cout << "3. Copying the tree to another binary tree object" << endl;
		cout << "4. Exit from the program" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice1;

		if (choice1 == 1){
			do{
				cout << "1. Perform in-order recursively" << endl;
				cout << "2. Perform pre-order recursively" << endl;
				cout << "3. Perform post-order recursively" << endl;
				cout << "4. Change the roles of left and right pointers (Swapped)" << endl;
				cout << "5. Find the height of tree recursively" << endl;
				cout << "6. Count number of leaves recursively" << endl;
				cout << "7. Count number of internal nodes recursively" << endl;
				cout << "8. Erase all nodes in binary tree recursively" << endl;
				cout << "9. Exit from recursive" << endl;
				cout << "Enter your choice: " << endl;
				cin >> choice2;
				if (choice2 == 1){
					b1.inorder(b1.root);
					cout << endl;
				}
				else if (choice2 == 2){
					b1.preorder(b1.root);
					cout << endl;
				}
				else if (choice2 == 3){
					b1.postorder(b1.root);
					cout << endl;
				}
				else if (choice2 == 4){
					b1.mirror(b1.root);
					cout << "After changing the roles of left and right sub trees" << endl;
					b1.display(b1.root);
					b1.mirror(b1.root);
					cout << endl;
				}
				else if (choice2 == 5){
					cout << "Height of the tree is : " << b1.heightRecursive(b1.root);
					cout << endl;
				}
				else if (choice2 == 6){
					cout << "Number of leaves are =  " << b1.leaves_r(b1.root);
					cout << endl;
				}
				else if (choice2 == 7){
					cout << "Number of internal nodes are = " << b1.totalInternal_r(b1.root);
					cout << endl;
				}
				else if (choice2 == 8){
					cout << "Deleting the tree recursively" << endl;
					b1.delete_r(b1.root);
					cout << endl;
				}
				else if (choice2 == 9){
					cout << "Recursive ends" << endl;
					break;
				}
				else {
					cout << "Invalid choice" << endl;
					cout << "Please re-enter" << endl;
					cin >> choice2;
				}
			}while(choice2 != 9);
		}

		else if (choice1 == 2){
				do{
					cout << "1. Perform in-order iteratively" << endl;
					cout << "2. Perform pre-order iteratively" << endl;
					cout << "3. Perform post-order iteratively" << endl;
					cout << "4. Change the roles of left and right pointers (Swapped)" << endl;
					cout << "5. Find the height of tree iteratively" << endl;
					cout << "6. Count number of leaves iteratively" << endl;
					cout << "7. Count number of internal nodes iteratively" << endl;
					cout << "8. Erase all nodes in binary tree iteratively" << endl;
					cout << "9. Exit" << endl;
					cout << "Enter your choice: " << endl;
					cin >> choice2;
					if (choice2 == 1){
						b1.inorder_iterative(b1.root);
						cout << endl;
					}
					else if (choice2 == 2){
						b1.iterative_preorder(b1.root);
						cout << endl;
					}
					else if (choice2 == 3){
						b1.iterative_postorder(b1.root);
						cout << endl;
					}
					else if (choice2 == 4){
						b1.mirror(b1.root);
						cout << "After changing the roles of left and right sub trees" << endl;
						b1.display(b1.root);
						b1.mirror(b1.root);
						cout << endl;
					}
					else if (choice2 == 5){
						cout << "Height of the tree is : " << b1.height_iterative(b1.root);
						cout << endl;
					}
					else if (choice2 == 6){
						cout << "Number of leaves are =  " << b1.calculateLeafNodes(b1.root);
						cout << endl;
					}
					else if (choice2 == 7){
						cout << "Number of internal nodes are = " << b1.calculateInternalNodes(b1.root);
						cout << endl;
					}
					else if (choice2 == 8){
						cout << "Deleting the tree iteratively" << endl;
						b1.deletetree_iter(b1.root);
						cout << endl;
					}
					else if (choice2 == 9){
						cout << "Iterative ends" << endl;
						break;
					}
					else {
						cout << "Invalid choice" << endl;
						cout << "Please re-enter" << endl;
						cin >> choice1;
					}
				}while(choice2 != 10);
			}

		else if (choice1 == 3){
			b1 = b2;
			cout << "Copying contents to another object b2" << endl;
			b2.levelOrderDisplay(b2.root);
			cout << endl;
		}

		else if (choice1 == 4){
			cout << "Thank you for visiting" << endl;
			exit(0);
		}
		else{
			cout << "Invalid choice entered" << endl;
			cout << "Please re-enter your choice: " << endl;
			cin >> choice1;
		}

	}while(choice1 != 4);
	return 0;
}



