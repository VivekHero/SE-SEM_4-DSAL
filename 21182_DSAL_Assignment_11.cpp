// Reference -  Shubham Panchal (GitHub Link -- https://github.com/shubham0204)
//============================================================================
// Name        : Assignment_11.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<fstream>
#include <string>
#include <ios>
#include <vector>
#include <cstring>
#define m 10
using namespace std;

class Student{
	int rollNumber;
	string name;
	char division;
	string address;

public:
	Student(){
		rollNumber = 0;
		name = "";
		division = ' ';
		address = "";
	}
	Student(int r, string n, char d, string a){
		rollNumber = r;
		name = n;
		division = d;
		address = a;
	}

	int getRollNumber(){
		return rollNumber;
	}

	void setData(){
		cout << "Enter the roll number of student" << endl;
		cin >> rollNumber;
		cout << "Enter the name of the student" << endl;
		cin >> name;
		cout << "Enter the division in which student is studying : " << endl;
		cin >> division;
		cout << "Enter the address of the student" << endl;
		cin >> address;
	}

	void getData(){
		cout << "Roll Number- " << rollNumber << endl;
		cout << "Name- " << name << endl;
		cout << "Division- " << division << endl;
		cout << "Address- " << address << endl;
	}
	friend class SequentialFile;
};

class SequentialFile{
	char filename[15];
	fstream fin;
	fstream fout;
	int n;
public:
	SequentialFile(char f[15]){
		strcpy(filename, f);
	}

	void setN(){
		cout << "Enter number of records to be added : " << endl;
		cin >> n;
	}
	int getN(){
		return n;
	}
	void writeRecords(Student s[]){
		fout.open(filename, ios::out);
		if (!fout){
			cout << "Error in opening file" << endl;
			return;
		}
		fout << "Roll,Name,Division,Address" << endl;
		for (int i = 0; i < n; i++){
			fout << s[i].rollNumber << "," << s[i].name << "," << s[i].division << "," << s[i].address << endl;
		}
		fout.close();
	}

	void printRecords(){
		fin.open(filename, ios::in);
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		while (!fin.eof()){
			string record;
			fin >> record;
			cout << record << endl;
		}
		fin.close();
	}

	void searchRecord(int rollNumber){
		fin.open(filename, ios::in);
		bool isFound = false;
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		while (!fin.eof()){
			string record;
			fin >> record;

			int comp = int(((record[0] - 48)*10 + (record[1] - 48) ));

			if (  comp == rollNumber){
				cout << "Record found" << endl;
				cout << record << endl;
				isFound = true;
				break;
			}

		}
		if (!isFound){
			cout << "Record not found!" << endl;
		}
		fin.close();
	}

	void deleteRecord(int rollNumber){
		fin.open(filename, ios::in);
		vector <string> lines;
		ofstream temp;
		temp.open("temp.txt");
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		int flag = 0;
		while (!fin.eof()){
			string record;
			fin >> record;
			int comp = int(((record[0] - 48)*10 + (record[1] - 48) ));
			if (comp == rollNumber){
				cout << "Record deleted successfully" << endl;
				flag = 1;
			}
			else{
				temp << record << endl;
				lines.push_back(record);
			}
		}

		if (flag == 0){
			cout << "Record not found " << endl;
		}
		fin.close();
		temp.close();
		remove(filename);
		rename("temp.txt", filename);
	}
};

int main(){
	char file[15];
	cout << "Enter the sequential file name" << endl;
	cin >> file;
	SequentialFile fobj(file);
	int roll, choice;
	do{
		cout << "----- MENU -----" << endl;
		cout << "1. Write records into file" << endl;
		cout << "2. Display records" << endl;
		cout << "3. Search record" << endl;
		cout << "4. Delete a record" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;
		switch(choice){
			case 1:{
				fobj.setN();
				int size = fobj.getN();
				Student sobj[size];
				for (int i = 0; i < size; i++){
					cout << "Enter data for Record number " << i + 1 << " - " << endl;
					sobj[i].setData();
				}
				fobj.writeRecords(sobj);
				break;
			}
			case 2:{
				fobj.printRecords();
				break;
			}
			case 3:{
				cout << "Enter the roll number to be searched" << endl;
				cin >> roll;
				fobj.searchRecord(roll);
				break;
			}
			case 4:{
				cout << "Enter the roll number to be deleted " << endl;
				cin >> roll;
				fobj.deleteRecord(roll);
				break;
			}
			case 5:{
				cout << "Thank you for visiting" << endl;
				exit(0);
				break;
			}
			default:{
				cout << "You have entered wrong choice" << endl;
			}
		}
	}while(choice != 5);

	return 0;
}
