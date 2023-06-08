#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class HashTable{
    private:
    int empId;
    int location;
    public:
    HashTable(){
        empId = 0;
        location = -1;
    }

    void createHT();
    void showHT();
    int Hash(int);
    void insertHT(int, int);
    int searchHT();
    void deleteHT();

    void setEmpId(){
        cin >> empId;
    }

    int getEmpId(){
        return empId;
    }

}HT[10];

class DirectFile{
    private:
    char buffer[40], fname[40];
    int empId, count;
    string name, address;
    fstream file;
    HashTable HT;

    public:
    DirectFile(){
        empId = 0;
        count = 0;
        name = '\0';
        address = '\0';
        cout << "Enter name of file : ";
        cin >> fname; 
    }

    void writeFile();
    void readFile();
    void searchRecord();
    void deleteRecord();
};

void HashTable::createHT(){
    int i, tableSize = 10;
    for (i = 0; i < tableSize; i++){
        HT[i].empId = 0;
        HT[i].location = -1;       
    }
}

void HashTable::showHT(){
    int i, tableSize = 10;
    for (i = 0; i < tableSize; i++){
        cout << "\n " << i << " " << HT[i].empId << " " << HT[i].location;
    }
}

int HashTable::Hash(int empId){
    int tableSize = 10;
    return (empId % tableSize);
}

void HashTable::insertHT(int empId, int loc){
    int index, tableSize = 10;
    index = Hash(empId);

    if (HT[index].location == -1){
        HT[index].empId = empId;
        HT[index].location = loc;
    }
    else{
        int temp = index;
        do{
            index++;
            index %= tableSize;
            if (index == temp){
                cout << "Hash Table is Full" << endl;
                return;
            }
        }while(HT[index].location != -1);

        HT[index].empId = empId;
        HT[index].location = loc;
    }
}

int HashTable::searchHT(){
    int empId;
    int index,tableSize = 10;
    cout << "Enter the employee id to be searched" << endl;
    cin >> empId;
    index = Hash(empId);

    if (HT[index].empId == empId){
        return HT[index].location;
    }
    else{
        int temp = index;
        do{
            index++;
            index = index % tableSize;
            if (index == temp){
                return -1;
            } 
        }while(HT[index].empId != empId);

        return HT[index].location;
    }

}

void HashTable::deleteHT(){
    int empId;
    int index,tableSize = 10;
    cout << "Enter the employee id to be deleted" << endl;
    setEmpId();

    index = Hash(empId);

    if (HT[index].empId == getEmpId()){
        HT[index].empId = 0;
        HT[index].location = -1;
    }
    else{
        int temp = index;
        do{
            index++;
            index = index % tableSize;
            if (index == temp){
                cout << "The record to be deleted is not found" << endl;
                break;
            } 
        }while(HT[index].empId != getEmpId());

        HT[index].empId = 0;
        HT[index].location = -1;
    }

}


void DirectFile::writeFile(){
    file.open(fname, ios::app);

    if (!file){
           cout << "Error in Opening File" << endl;
    }
    else{
        cout << "Enter number of records : ";
        cin >> count;
        for (int i = 0; i < count; i++){
            cout << "Employee Id : ";
            cin >> empId;
            cout << "Name : ";
            cin >> name;
            cout << "Address : ";
            cin >> address;
            cout << "Location : " << file.tellp() << endl;
            HT.insertHT(empId, file.tellp());
            file << empId << " " << name << " " << address << endl;
        }
    }
    file.close();
}

void DirectFile::searchRecord(){
    file.open(fname, ios::in);
    if (!file){
        cout << "Error in Opening File" << endl;
    }
    else{
        int loc = HT.searchHT();
        if (loc == -1){
            cout << "Record not found!" << endl;
            return;
        }
        
        file.seekg(loc, ios::beg);
        file.getline(buffer, 40);
        cout << "Record Found" << endl << buffer << endl;
    }
    file.close();
}

void DirectFile::deleteRecord(){
    file.open(fname, ios::in);
    fstream temp;
    temp.open("tmp.txt", ios::out);
    if (!file){
        cout << "Error in Opening File" << endl;
    }
    else{
        fstream temp;
        temp.open("tmp.txt", ios::out);
        int flag = 0;
        HT.deleteHT();
     
        while (!file.eof()){
            file.getline(buffer, 40);
            int comp = int(((buffer[0] - 48)*10 + (buffer[1] - 48) ));
            if (comp == HT.getEmpId()){
                cout << "Record deleted successfully" << endl;
                flag = 1;
            }
            else{
                temp << buffer << endl;
            }
        }
    }

    file.close();
    temp.close();
    remove(fname);
    rename("tmp.txt", fname);
}

void DirectFile::readFile(){
    file.open(fname, ios::in);
    if (!file){
        cout << "Error in opening file" << endl;
    }
    else{
        int i = 0;
        while (!file.eof()){
            file.getline(buffer, 40);
            cout << "Record " << i << " : " << buffer << endl;
            i++;
        }
    }
    file.close();
    cout << "\n\nHash Table : " << endl;
    HT.showHT();
}

int main()
{

	DirectFile file;
    int choice;
    do{
        cout << "----- MENU -----" << endl;
        cout << "1. Write in the file" << endl;
        cout << "2. Read from the file" << endl;
        cout << "3. Search in the file" << endl;
        cout << "4. Delete a record from file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        switch(choice){
            case 1:{
               file.writeFile();
               break; 
            }
            case 2:{
                file.readFile();
                break;
            }
            case 3:{
                file.searchRecord();
                break;
            }
            case 4:{
                file.deleteRecord();
                file.readFile();
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
    }while (choice != 5);
	
	return 0;
}