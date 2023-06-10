/* Reference - Shubham Panchal (GitHub -- @shubham0204) */
 * A11.cpp
 *
 *  Created on: 05-Jun-2023
 *      Author: Vivek Gotecha
 */

#include <iostream>
#include<fstream>
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
	Student s;

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

	void writeRecords(){
		fout.open(filename, ios::app);
		if (!fout){
			cout << "Error in opening file" << endl;
			return;
		}

		s.setData();
		fout.write(reinterpret_cast<char*>(&s), sizeof(s));
		fout.close();
	}

	void printRecords(){
		fin.open(filename);
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		cout<<"\nRoll No\t Student Name \tDivision \tAddress" << endl;
		fin.read(reinterpret_cast<char*>(&s), sizeof(s));
		while (!fin.eof()){
            s.getData();
			fin.read(reinterpret_cast<char*>(&s), sizeof(s));
			
		}
		fin.close();
	}

	void searchRecord(int rollNumber){
		fin.open(filename);
		bool isFound = false;
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		while (!fin.eof()){
			fin.read(reinterpret_cast<char*>(&s), sizeof(s));
			if (s.getRollNumber() == rollNumber){
				isFound = true;
			}
		}
		if (!isFound){
			cout << "Record not found!" << endl;
		}
        else{
            cout << "Record found" << endl;
            s.getData();
        }
		fin.close();
	}

	void deleteRecord(int rollNumber){
		fin.open(filename);
		ofstream temp;
		temp.open("temp.txt");
		if (!fin){
			cout << "Error in opening file" << endl;
			return;
		}
		int flag = 0;
		fin.read(reinterpret_cast<char*>(&s), sizeof(s));
		while (!fin.eof()){
			if (s.getRollNumber() == rollNumber){
				cout << "Record deleted successfully" << endl;
				flag = 1;
			}
			else{
				temp.write(reinterpret_cast<char*>(&s), sizeof(s));
			}
			fin.read(reinterpret_cast<char*>(&s), sizeof(s));
		}

		if (flag == 0){
			cout << "Student whose roll number is " << rollNumber << " not found" << endl;
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
    bool writeRecord = false;
	do{
		cout << "----- MENU -----" << endl;
		cout << "1. Write records into file" << endl;
		cout << "2. Display records" << endl;
		cout << "3. Search record" << endl;
		cout << "4. Delete a record" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;
		switch(choice){
			case 1:{
				fobj.writeRecords();
                writeRecord = true;
				break;
			}
			case 2:{
                if (!writeRecord){
                    cout << "First write the record and then display" << endl;
                    fobj.writeRecords();
                    writeRecord = true; 
                }
                else{
                    fobj.printRecords();
                }
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
