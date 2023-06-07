/*
 * Separate_Chaining(Assignment_5).cpp
 *
 *  Created on: 24-Mar-2023
 *      Author: Vivek Gotecha
 */

#include <iostream>
#include <string.h>
#include <cmath>
#define size 10
using namespace std;

class HashNode{
public:
	string key, value;
	HashNode *next;
	HashNode(string k, string v){
		key = k;
		value = v;
		next = NULL;
	}
	friend class LinkedList;
	friend class HashTable;
};

class LinkedList{
	HashNode *head;
public:
	LinkedList(){
		head = NULL;
	}

	void insert_at_end(string k, string v){
		HashNode *newNode = new HashNode(k, v);
		if (head == NULL){
			head = newNode;
		}
		else
		{
			HashNode *temp = head;
			int duplicateKeyFound = 0;
			do {
				if (temp->key == k){
					cout << "Duplicate key " << k << " found!!" << endl;
					cout << "Replacing old value " << temp->value << " with new value " << v << endl;
					temp->value = v;
					duplicateKeyFound=1;
					break;
				}
				if (temp->next != NULL){
					temp = temp->next;
					if (temp->key == k){
						cout << "Duplicate key " << k << " found!!" << endl;
						cout << "Replacing old value " << temp->value << " with new value " << v << endl;
						temp->value = v;
						duplicateKeyFound=1;
						break;
					}
				}
			}while (temp->next != NULL);

			if (duplicateKeyFound != 1){
				temp->next = newNode;
			}

		}
	}

	int searchLL(string k, int index){
		HashNode *temp;
		int i = 0, flag = 1;
		temp = head;
		if (head == NULL){
			cout << "Nothing to be searched" << endl;
			cout << "Linked List Array at this index is null" << endl;
			return -1;
		}
		else{
			if (head->key == k){
				cout << "If Key = " << k << " is present then it will be stored in Hash Table Bucket = "<< index + 1 << endl;
				cout << "Item found at location : " << i + 1;
				flag = 0;
				return index;
			}
			else{
				while (temp->next != NULL){
					if (temp->key == k){
						cout << "If Key = " << k << " is present then it will be stored in Hash Table Bucket = "<< index + 1 << endl;
						cout << "Item found at location : " << i + 1<< endl;
						cout << "Key = " << k << " Value = " << temp->value << endl;
						flag = 0;
						return index;
					}
					else{
						flag = 1;
					}
					i++;
					temp = temp->next;
					if (temp->key == k){
						cout << "If Key = " << k << " is present then it will be stored in Hash Table Bucket = "<< index + 1 << endl;
						cout << "Item found at location : " << i + 1 << endl;
						cout << "Key = " << k << " Value = " << temp->value << endl;
						flag = 0;
						return index;
					}
				}
				return -1;
			}

			if (flag != 0){
				cout << "Item is not found" << endl;
				return -1;
			}
		}
	}
	void displayLL(){
		if (head == NULL){
			cout << "\t NULL" << endl;
			return;
		}
		else{
			HashNode *temp = head;
			while (temp != NULL){
				cout << "\t" <<  temp->key << " : " << temp->value << " -> ";
				temp = temp->next;
			}
			cout << endl;

		}
	}

	void deleteLL(string k){
		cout << k << endl;
		if (head == NULL){
			cout << "Nothing to be deleted" << endl;
		}
		else{
			HashNode *temp = head;
			HashNode *temp1 = NULL;
			while (temp != NULL){
				if (temp->key == k){
					if (temp == head){
						head = head->next;
						delete temp;
						temp = head;
					}
					else{
						temp1->next = temp->next;
						delete temp;
						temp = temp1->next;
					}
				}
				else{
					temp1 = temp;
					temp = temp->next;
				}
			}

			if (temp == NULL){
				cout << "Key not found" << endl;
			}
		}
	}
};
class HashTable{
	LinkedList LL[size];
public:
	HashTable(){
	}

	int hashFunc(string key){
		int sum = 0;
		for (int i = 0; i < key.length(); i++){
			sum += int(key[i]);
		}
		return (sum % size);
	}

	void insert(string key, string value){
		int index = hashFunc(key);
		cout << "index = " <<index << endl;
		LL[index].insert_at_end(key, value);
	}

	void search(string key){
		int index = hashFunc(key);
		LL[index].searchLL(key, index);
	}

	void deleteKey(string key){
		int index = hashFunc(key);
		if (LL[index].searchLL(key, index) != -1){
			LL[index].deleteLL(key);
			cout << "Deleted successfully" << endl;

		}
	}

	void display(){
		cout << "The hash Table contents is as follows : " << endl;
		for (int i = 0; i < size; i++){
			cout << "\t" << "[" << i << "]";
			LL[i].displayLL();
		}
	}

};
int main(){
	HashTable h1;
	string word, meaning, key;
	int choice, n;
	do{
		cout << "\n***** DICTIONARY MENU *****" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Search" << endl;
		cout << "4. Delete" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;

		if (choice == 1){
			cout << "Enter the total number of words to be inserted in the dictionary" << endl;
			cin >> n;
			for (int x=0; x<n; x++){
				cout << "Enter word : " << endl;
				cin >> word;
				cout << "Enter the word's meaning" << endl;
				cin >> meaning;
				h1.insert(word, meaning);
			}
		}
		else if (choice == 2){
			h1.display();
		}
		else if (choice == 3){
			cout << "Enter key to found : " << endl;
			cin >> key;
			h1.search(key);
		}
		else if (choice == 4){
			cout << "Enter key to be deleted : " << endl;
			cin >> key;
			h1.deleteKey(key);
		}
		else if (choice == 5){
			cout << "Thank you for visiting" << endl;
			exit(0);
		}
	}while (choice != 5);


	return 0;
}


