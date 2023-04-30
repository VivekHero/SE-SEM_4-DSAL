/*
 * Linear_Probing(Assignment_4).cpp
 *
 *  Created on: 24-Mar-2023
 *      Author: Vivek Gotecha
 */

#include <iostream>
#include <string.h>
#define size 10
using namespace std;

class Node{
	long long int telephone;
	string name;


public:
	Node(){
		telephone = 0;
		name = "";
	}
	friend class HashTable;
};

class HashTable{
	Node data[10];
public:
	HashTable(){
		for (int i = 0; i < 10; i++){
			data[i].name = "";
			data[i].telephone = 0;
		}
	}

	int hashFunc(long long int key){
		return (key % 10);
	}

	void insert(long long int t, string n){
			int index = hashFunc(t);
			int temp = index;

			if (data[index].telephone == 0){
				data[index].telephone = t;
				data[index].name = n;
			}
			else{
				while (data[index].telephone != 0){
					if (index != 9){
						index += 1;
					}
					else{
						index = 0;
					}
					if (index == temp){
						cout << "Hash Table is Full" << endl;
						return;
					}
				}


				data[index].telephone = t;
				data[index].name = n;
			}
		}


	void insertwith(long long int t, string n){
		int index = t % 10;
		if (data[index].telephone == 0){
			data[index].telephone = t;
			data[index].name = n;
		}
		else if (data[index].telephone % size == index){
			insert(t,n);
		}
		else{
			int prev = index;
			while (data[index].telephone != 0){
				index++;
				index %= size;
				if (index == prev){
					cout << "Hash Table is Full" << endl;
					return;
				}
			}
			int temp = data[prev].telephone;
			string str = data[prev].name;
			data[prev].telephone = t;
			data[prev].name = n;
			data[index].telephone = temp;
			data[index].name = str;
		}
	}

	void comparisons(long long int t){
		int index = t%10;
		int count = 0;
		if (data[index].telephone == t){
			count += 1;
			cout << "The telephone number " << data[index].telephone<<" found at index " << index << endl;
			cout << "The number of comparisons made to search "<< data[index].telephone << " are "<< count << endl;
			return;
		}
		int temp = index;
		while (data[index].telephone != t){
			index += 1;
			index %= size;
			count++;
			 if(index==temp){
					cout << "The telephone number " << t << " is not found" << endl;
					count = 0;
					cout << "The number of comparisons made to search " << t << " are " << count << endl;

					return;
			}
		}
		cout << "The telephone number " << data[index].telephone<<" found at index " << index << endl;
		cout << "The number of comparisons made to search " <<data[index].telephone << " are " << (count + 1) << endl;
	}


	void search(long long int t){
		int index = hashFunc(t);
		int temp = index;

		if (data[index].telephone == t){
			cout << "Record found" << endl;
			cout << "\t Telephone Number \t Name" << endl;
			cout << "\t " << data[index].telephone << "\t " << data[index].name << endl;
		}
		else{
			while (data[index].telephone != t){
				if (index != 9){
					index += 1;
				}
				else{
					index = 0;
				}

				if (temp == index){
					cout << "Record Not found!!" << endl;
					break;
				}

			}
			if (data[index].telephone == t){
				cout << "Record found" << endl;
				cout << "\t Telephone Number \t Name" << endl;
				cout << "\t\t" << data[index].telephone << "\t\t" << data[index].name << endl;
				return;
			}

		}
	}

	void deleteRecord(long long int t){
			int index = hashFunc(t);
			int temp = index;
			if (data[index].telephone == t){
				data[index].name = "";
				data[index].telephone = 0;
				cout << "Record Deleted Successfully!!!" << endl;
			}
			else{

				while (data[index].telephone != t){
						if (index != 9){
							index += 1;
						}
						else{
							index = 0;
						}

						if (data[index].telephone == t){
							data[index].name = "";
							data[index].telephone = 0;
							cout << "Record Deleted Successfully!!!" << endl;
							return;
						}
						else if (temp == index){
							cout << "Record Not found!!" << endl;
							return;
						}

			  }
			  cout << "Record Not found!!" << endl;

		 }
		}

	void display(){
		cout << "Hash Index \tMobile Number \tName" << endl;
		for (int i = 0; i < 10; i++){
			cout << i << " \t\t" << data[i].telephone << "\t\t" << data[i].name << "\t\t" << endl;
		}
	}
};

int main()
{
	HashTable h1,h2;
	long long int t;
	string n;
	int choice1, choice2;

	do{
		cout << "1. Insert Without replacement" << endl;
		cout << "2. Insert With Replacement" << endl;
		cout << "3. Display both the hash tables" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice to choose between with and without replacement" << endl;
		cin >> choice1;

		if (choice1 == 1){
			do {
					cout << "1. Insert" << endl;
					cout << "2. Search" << endl;
					cout << "3. Delete" << endl;
					cout << "4. Display" << endl;
					cout << "5. Comparisons" << endl;
					cout << "6. Exit from without replacement insertion" << endl;
					cout << "Enter your choice: " << endl;
					cin >> choice2;

					if (choice2 == 1){
						cout << "Enter name: " << endl;
						cin >> n;
						cout << "Enter telephone number: " << endl;
						cin >> t;
						h1.insert(t,n);
					}
					else if (choice2 == 2){
						cout << "Enter telephone number which needs to be searched: " << endl;
						cin >> t;
						h1.search(t);
					}
					else if (choice2 == 3){
						cout << "Enter telephone number which needs to be deleted: " << endl;
						cin >> t;
						h1.deleteRecord(t);

					}
					else if (choice2 == 4){
						cout << "The telephone records stored in hash table are as follows: " << endl;
						h1.display();
					}
					else if (choice2 == 5){
						cout << "Enter telephone number to compute comparisons required : " << endl;
						cin >> t;
						h1.comparisons(t);
					}
					else if (choice2 == 6){
						cout << "Exit from without replacement insertion" << endl;
						break;
					}
					else{
						cout << "Invalid choice entered.Please re-enter your choice." << endl;
					}
				}while (choice2 != 6);
		}

		else if (choice1 == 2){
					do {
							cout << "1. Insert With Replacement" << endl;
							cout << "2. Search" << endl;
							cout << "3. Delete" << endl;
							cout << "4. Display" << endl;
							cout << "5. Comparisons" << endl;
							cout << "6. Exit from without replacement" << endl;
							cout << "Enter your choice: " << endl;
							cin >> choice2;

							if (choice2 == 1){
								cout << "Enter name: " << endl;
								cin >> n;
								cout << "Enter telephone number: " << endl;
								cin >> t;
								h2.insertwith(t,n);
							}
							else if (choice2 == 2){
								cout << "Enter telephone number which needs to be searched: " << endl;
								cin >> t;
								h2.search(t);
							}
							else if (choice2 == 3){
								cout << "Enter telephone number which needs to be deleted: " << endl;
								cin >> t;
								h1.deleteRecord(t);

							}
							else if (choice2 == 4){
								cout << "The telephone records stored in hash table are as follows: " << endl;
								h2.display();
							}
							else if (choice2 == 5){
								cout << "Enter telephone number to compute comparisons required : " << endl;
								cin >> t;
								h2.comparisons(t);
							}
							else if (choice2 == 6){
								cout << "Exit from replacement insertion" << endl;
								break;
							}
							else{
								cout << "Invalid choice entered.Please re-enter your choice." << endl;
							}
						}while (choice2 != 6);
		}
		else if (choice1 == 3){
			cout << "First hash table (Linear Probing without replacement)" << endl;
			h1.display();
			cout << "Second hash table (Linear Probing with replacement)" << endl;
			h2.display();
		}
		else if (choice1 == 4){
			cout << "Thank you for visiting" << endl;
			exit(0);
		}
	}while(choice1 != 4);


	return 0;
}

