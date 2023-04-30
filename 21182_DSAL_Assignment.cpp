//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

class Node{
	int data;
	Node *left;
	Node *right;

public:
	Node(int val){
		data = val;
		left = NULL;
		right = NULL;
	}

	friend class BinaryTree;
};

class BinaryTree{
	int x;
	int n;
	int flag;
public:
	Node *root;
	Node *tem;
	BinaryTree(){
		root = NULL;
	}


	Node *insert( Node *temp , int in_data)
	 {
	  if( temp == NULL )
	  {
	   temp = new Node(in_data);
	  }
	  else if( temp->data > in_data)
	  {
	   temp->left = insert(temp->left , in_data);
	  }
	  else
	  {
	   temp->right = insert( temp->right , in_data);
	  }
	  return temp;
	 }

	void input()
	 {
		  cout<<"Enter number of elements in the BST : ";
		  cin>>n;
		  for(int i = 0 ; i < n ; i++)
		  {
		   cout<<"Number = ";
		   cin>>x;
		   root = insert(root , x);
		  }
	 }

	int minvalue(Node *&root){
		Node *temp = root;
		while (temp->left != NULL){
			temp = temp->left;
		}
		cout << "Minimum Value = " <<  temp->data << endl;
		return temp->data;
	}

	void smallest(Node *root){
		if (root != NULL){
			if (root->left == NULL){
				cout << root->data << endl;
				tem = root;
			}
			else{
				smallest(root->left);
			}
		}
		else{
			cout << "Empty Binary Search Tree" << endl;
		}
	}

	int maxvalue(Node *&root){
		Node *temp = root;
		while (temp->right != NULL){
			temp = temp->right;
		}
		cout << "Maximum Value = " <<  temp->data << endl;
		return temp->data;
	}

	void mirror(Node *root){
		if (root == NULL){
			return;
		}
		else{
			Node *ptr;
			mirror(root->left);
			mirror(root->right);
			ptr = root->left;
			root->left = root->right;
			root->right = ptr;
		}
	}



	void inorder(Node *root){
		if (root == NULL){
			return;
		}
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}

	void preorder(Node *root){
		if (root == NULL){
			return;
		}
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);
	}

	void postorder(Node *root){
		if (root == NULL){
			return;
		}
		postorder(root->left);
		postorder(root->right);
		cout << root->data << " ";
	}

	void levelorderdisplay(Node *root){
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

	int search(Node *root, int val){
		if (root != NULL){
			if (root->data == val){
				cout << ":-- RECORD FOUND --:" << endl;
				return 1;
			}

			else if (val < root->data){
				this->search(root->left, val);
			}
			else if (val > root->data){
				this->search(root->right, val);
			}
		}

		else {
			return 0;
		}
	}

	void display(){
		cout << endl << "--- INORDER TRAVERSAL ---" << endl;
		inorder(root);
		cout << endl << "--- PREORDER TRAVERSAL ---" << endl;
		preorder(root);
		cout << endl << "--- POSTORDER TRAVERSAL ---" << endl;
		postorder(root);
	}



	int depth(Node *root){
		if (root == NULL){
			return 0;
		}
		return (max((depth(root->left)), (depth(root->right))) + 1);
	}

	Node *deleteNode(Node *root, int data){
		if (root == NULL){
			return NULL;
		}
		if (data < root->data){
			root->left = deleteNode(root->left, data);
		}
		else if (data > root->data){
			root->right = deleteNode(root->right, data);
		}
		else{
			if (root->left == NULL && root->right == NULL){
				root = NULL;
				return NULL;
			}
			else if (root->left == NULL){
				Node *temp = root->right;
				root = NULL;
				return temp;
			}
			else if (root->right == NULL){
				Node *temp = root->left;
				root = NULL;
				return temp;
			}
			smallest(root->right);
			Node *temp = tem;
			root->data = temp->data;

			root->right = deleteNode(root->right, temp->data);
		}
		return root;

	}

	int comparisons(Node *root, int d){
	    if (root == NULL){
	        return 0;
	    }
	    else{
	        Node *temp = root;
	        int count = 0;
	        while (temp != NULL){
	            count++;
	            if (temp->data == d){
	               // count++;
	                cout << d << " found in the BST" << endl;
	                return count;
	            }
	            else if (d < temp->data){
	                temp = temp->left;
	            }
	            else if (d > temp->data){
	                temp = temp->right;
	            }
	        }
	        cout << "Element not found in the BST"<< endl;
	        return -1;
	    }
	}

};

int main(){
	 BinaryTree obj;
	 int choice;
	 char ans = 'y';

	 do{
		 cout << "1. Input the number of elements/ Insert new Node : " << endl;
		 cout << "2. Display the Binary Search Traversal Techniques: " << endl;
		 cout << "3. Find the number of nodes in longest path (depth): " << endl;
		 cout << "4. Minimum Value in the Binary Search Tree: " << endl;
		 cout << "5. Maximum value in the Binary Search Tree: " << endl;
		 cout << "6. Change the role of the left and right pointers are swapped: " << endl;
		 cout << "7. Search the particular element: " << endl;
		 cout << "8. Delete an particular element from the BST: " << endl;
		 cout << "9. Display Level Order Display" << endl;
		 cout << "10. Exit from the program" << endl;

		 cout << "Enter your choice: " << endl;
		 cin >> choice;

		 switch(choice){
		 case 1:
			 obj.input();
			 break;
		 case 2:
			 obj.display();
			 break;
		 case 3:
			 cout << "Depth: ";
			 cout << endl << obj.depth(obj.root) << endl;
			 break;
		 case 4:
			 obj.minvalue(obj.root);
			 break;
		 case 5:
			 obj.maxvalue(obj.root);
			 break;
		 case 6:
			 obj.mirror(obj.root);
			 cout << "The binary search tree traversals after changing the roles: " << endl;
			 obj.display();
			 obj.mirror(obj.root);
			 break;
		 case 7:{
			 int a = 0;
			 int searchElement;
			 cout << "Enter the value to be searched in the Binary Search Tree: " << endl;
			 cin >> searchElement;
			 a = obj.search(obj.root, searchElement);

			 if (a == 0){
				 cout << "Element not " << searchElement << " found" << endl;
			 }
			 else {
				 cout << "Success" << endl;
				 cout << "Element " << searchElement << " found" << endl;
			 }
			 cout << "The number of comparisons required to search the element " << searchElement << " are" << obj.comparisons(obj.root, searchElement) << endl;

			 break;
		 }

		 case 8:{
			 int deleteItem;
			 cout << "Before Deleting the element from the BST: " << endl;
			 obj.display();
			 cout << "Enter the item to be deleted: " << endl;
			 cin >> deleteItem;
			 obj.root = obj.deleteNode(obj.root,deleteItem);
			 cout << "After deleting the element, the various BST traversals are: ";
			 obj.display();
			 break;
		 }

		 case 9:{
			 obj.levelorderdisplay(obj.root);
			 break;
		 }

		 case 10:
			 cout << "Successfully exited from the program" << endl;
			 exit(0);
			 break;
		 default:
			 cout << "Invalid Choice Entered" << endl;
			 cout << "Please Re-enter" << endl;
			 cin >> choice;
		 }
		 cout << "Do you want to continue ? (y/n) " << endl;
		 cin >> ans;


	 }while(ans == 'y');
	 return 0;
}



