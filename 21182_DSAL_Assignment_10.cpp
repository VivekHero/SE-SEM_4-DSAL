/*
 * A10_Final.cpp
 *
 *  Created on: 19-May-2023
 *      Author: Vivek Gotecha
 */

#include <iostream>
using namespace std;

class Heap{
	int *arr;
	int n;
public:
	Heap(int x){
		n = x;
		arr = new int[n];
	}

	void swap(int *a, int *b){
		int temp = *a;
		*a = *b;
		*b = temp;
	}
	void input(){
		cout << "Enter data to be inserted in an array:" << endl;
		for(int i = 0; i < n; i++){
			cout << "Enter element " << i + 1 << " : ";
			cin >> arr[i];
		}
	}

	void heapify(int n, int i){
		int largest = i;
		int left = (2 * i) + 1;
		int right = (2 * i) + 2;

		if (left < n && arr[left] > arr[largest]){
			largest = left;
		}

		if (right < n && arr[right] > arr[largest]){
			largest = right;
		}

		if (largest != i){
			display();
			swap(&arr[i], &arr[largest]);
			heapify(n, largest);
		}
	}
	void heap_sort(int n){
		for (int i = (n/2) - 1; i >= 0; i--){
			heapify(n, i);
		}
		display();
		cout << "After Sort: " << endl;
		display();
		for (int i = n -1; i >= 0; i--){
			swap(&arr[0], &arr[i]);
			heapify(i, 0);
		}
	}

	void display(){
		for (int i = 0; i < n; i++){
			cout << arr[i] << " ";
		}
		cout << endl << endl;
	}

};

class MinHeap{
	int *arr;
	int n;
public:
	MinHeap(int x){
		n = x;
		arr = new int[n];
	}

	void swap(int *a, int *b){
		int temp = *a;
		*a = *b;
		*b = temp;
	}
	void input(){
		cout << "Enter data to be inserted in an array:" << endl;
		for(int i = 0; i < n; i++){
			cout << "Enter element " << i + 1 << " : ";
			cin >> arr[i];
		}
	}

	void heapify(int n, int i){
		int smallest = i;
		int left = (2 * i) + 1;
		int right = (2 * i) + 2;

		if (left < n && arr[left] < arr[smallest]){
			smallest = left;
		}

		if (right < n && arr[right] < arr[smallest]){
			smallest = right;
		}

		if (smallest != i){
			display();
			swap(&arr[i], &arr[smallest]);
			heapify(n, smallest);
		}
	}
	void heap_sort(int n){
		for (int i = (n/2) - 1; i >= 0; i--){
			heapify(n, i);
		}
		display();
		cout << "After Sort: " << endl;
		display();
		for (int i = n -1; i >= 0; i--){
			swap(&arr[0], &arr[i]);
			heapify(i, 0);
		}
	}

	void display(){
		for (int i = 0; i < n; i++){
			cout << arr[i] << " ";
		}
		cout << endl << endl;
	}

};

int main(){
	int n;
	cout << "Enter Number of total elements: ";
	cin >> n;
	Heap obj(n);
	int choice;

	do{
		cout << "----- MENU -----" << endl;
		cout << "1. Insert elements " << endl;
		cout << "2. Sort elements using heap sort and display in each pass" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice - " << endl;
		cin >> choice;
		switch(choice){
			case 1:{
				obj.input();
				break;
			}
			case 2:{
				obj.heap_sort(n);
				cout << "After performing heap sort: ";
				obj.display();
				break;
			}
			case 3:{
				cout << "Thank you" << endl;
				exit(0);
			}
			default:{
				cout << "You have entered wrong choice" << endl;
			}
		}
	}while(choice != 3);

	return 0;
}

