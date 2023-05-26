//============================================================================
// Name        : Assignment_12.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#define size 10

using namespace std;

class Student{
	int roll;
	string name;
	string address;

public:
	Student(){
		roll = 0;
		name = "";
		address = "";
	}

	void setdata(int r, string n, string a){
		roll = r;
		name = n;
		address = a;
	}

	int getRoll(){
		return roll;
	}

	string getName(){
		return name;
	}

	string getAddress(){
		return address;
	}
	friend class Direct_File;
};


class Direct_File{
	string filename;
	int hashtable[size];

public:
	Direct_File(string f){
		filename = f;
		for (int i = 0; i < size; i++){
			hashtable[i] = -1;
		}
	}

	int hashIndex(int key){
		return key % size;
	}

	void insert(Student *s){
		ofstream fout;
		fout.open(filename, ios::app);
		if (!fout.is_open()){
			cout << "Cannot open file" << endl;
			return;
		}
		fout.seekp(0, ios::end);
		int address = fout.tellp();
		int index = hashIndex(s->getRoll());
		int temp = index;
		if (hashtable[index] == -1){
			cout << address << endl;
			hashtable[index] = address;
		}
		else{
			while (hashtable[index] != -1){
				if (index != 9){
					index += 1;
				}
				else{
					index = 0;
				}

				if (index == temp){
					cout << "\nHash Table is Full" << endl;
					return;
				}
			}
			hashtable[index] = address;
		}
		fout << s->getRoll() << " " << s->getName() << " " << s->getAddress() << " " << "end" << " ";
		fout.close();
	}

	void search(int key){
		int index = hashIndex(key);
		ifstream fin(filename, ios::in);
		int address;
		int temp = index;
		if (!fin.is_open()){
			cout << "Cannot open file" << endl;
		}
		int r = 0;
		string n = "";
		string a = "";
		if (hashtable[index] == -1){
			cout << "D" << endl;
			return;
		}

		else{
			address = hashtable[index];
			fin.seekg(address, ios::beg);
			fin >> r;
			if (r == key){
				cout << "Data found at address : " << address << endl;
				cout << "Roll No. : " << r;
				fin >> n >> a;
				cout << "\tName : " << n << "\tAddress : " << a << endl;
				return;
			}
			else{
				while (true){
					address = hashtable[index];
					fin.seekg(address, ios::beg);
					fin >> r;
					if (r == key){
						cout << "Data found at address : " << address << endl;
						cout << "Roll No. : " << r;
						fin >> n >> a;
						cout << "\tName : " << n << "\tAddress : " << a << endl;
						return;
					}

					if (index != 9){
						index += 1;
					}
					else{
						index = 0;
					}

					if (index == temp){
						cout << "Data not found" << endl;
						return;
					}
				}
			}
		}
	}

	void readfromfile(){
		ifstream fin(filename, ios::in);
		if (!fin.is_open()){
			cout << "Cannot open file" << endl;
			return;
		}
		int i = 0;
		string n = "";
		string a = "";
		string e = "";
		cout << "-----------------------------------------------" << endl;
		cout << left << setw(10) << "ROLL NO." << setw(13) << "NAME" << setw(10) << "ADDRESS" << endl
			 << fixed << showpoint;
		cout << "------------------------------------------------" << endl;
		while (fin >> i >> n >> a >> e){
			cout << left << setw(10) << i << setw(13) << n << setw(10) << a << endl;
		}
		cout << "------------------------------------------------" << endl;
		fin.close();
	}
};


int main(){
	Direct_File obj("file.txt");
	int n, choice;
	do{
		cout << "----- MENU -----" << endl;
		cout << "1. Insert Records" << endl;
		cout << "2. Display Records" << endl;
		cout << "3. Search a record" << endl;
		cout << "4. Exit" <<< endl;
		cout << "Enter your choice" << endl;
		cin >> choice;
		switch(choice){
			case 1:{
				cout << "Enter the number of student records to be inserted - " << endl;
				cin >> n;
				Student s[n];
				string name, address;
				int r;
				for (int i = 0; i < n; i++){
					cout << "Enter Roll Number- " << endl;
					cin >> r;
					cout << "Enter Name- " << endl;
					cin >> name;
					cout << "Enter Address- " << endl;
					cin >> address;
					s[i].setdata(r, name, address);
					obj.insert(&s[i]);
				}
				break;
			}
			case 2:{
				obj.readfromfile();
				break;
			}
			case 3:{
				int r;
				cout << "Enter the roll number of student whose record needs to be searched" << endl;
				cin >> r;
				obj.search(r);
				break;
			}
			case 4:{
				cout << "Thank you for visiting" << endl;
				exit(0);
				break;
			}
			default:{
				cout << "You have entered wrong choice" << endl;
			}
		}
	}while(choice != 4);

	return 0;
}



