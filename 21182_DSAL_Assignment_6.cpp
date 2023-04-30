//============================================================================
// Name        : Assignment_6.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node{
    string data;
    Node* down;
    Node* right;
    int visited;
    public:
    Node(string x){
        data = x;
        down = NULL;
        right = NULL;
        visited = 0;
    }
    friend class Graph;
    friend class Stack;
    friend class Queue;
};

class Stack{
    Node* top;
    public:
    Stack(){
        top = NULL;
    }

    void push(string data){
        Node* new_node = new Node(data);
        if (top == NULL){
            top = new_node;
            return;
        }
        else{
            new_node->down = top;
            top = new_node;
            return;
        }
    }

    Node* pop(){
        if (top == NULL){
            return NULL;
        }
        else{
            Node* temp = top;
            top = top->down;
            temp->down = NULL;
            return temp;
        }
    }

    bool is_empty(){
        if (top == NULL){
            return true;
        }
        return false;
    }

    bool search(string data){
        Node* temp = top;
        while (temp->down != NULL){
            if (temp->data == data){
                return true;
            }
            temp = temp->down;
        }
        return false;
    }

    friend class Graph;

};

class Queue{
    Node* front;
    Node* rear;

    public:
    Queue(){
        front = rear = NULL;
    }
    void enqueue(string data){
        Node* new_node = new Node(data);
        if (front == NULL){
            front = new_node;
            rear = new_node;
            return;
        }
        else{
            rear->right = new_node;
            rear = rear->right;
            return;
        }
    }

    Node* dequeue(){
        if (front == NULL){
            return NULL;
        }
        else if (front == rear){
            Node* temp = front;
            front = NULL;
            rear = NULL;
            return temp;
        }
        else{
            Node* temp = front;
            front = front->right;
            return temp;
        }
    }

    bool empty(){
        if (front == NULL && rear == NULL){
            return true;
        }
        return false;
    }

    bool search(string data){
        Node* temp = front;
        while (front != rear){
            if (temp->data == data){
                return true;
            }
            temp = temp->right;
        }
        return false;
    }
    friend class Graph;
};

class Graph{
    public:
    Node* head;
    public:
    Graph(){
        head = NULL;
    }

    void insert(string data, string adj){
        if (head == NULL){
            Node* new_data = new Node(data);
            new_data->right = new Node(adj);
            new_data->down = new Node(adj);
            new_data->down->right = new Node(data);
            head = new_data;
            return;
        }
        else{
            Node* data_temp = search_down(data);
            if (data_temp == NULL){
                Node* new_data = new Node(data);
                new_data->right = new Node(adj);
                Node* temp = head;
                while (temp->down != NULL){
                    temp = temp->down;
                }
                temp->down = new_data;

                if (search_down(adj) == NULL){
                    new_data->down = new Node(adj);
                    new_data->down->right = new Node(data);
                }
                else{
                    Node* temp = search_down(adj);
                    while (temp->right != NULL){
                        temp = temp->right;
                    }
                    temp->right = new Node(data);
                }
                return;
            }
            else{
                Node* adj_temp = search_right(data_temp, adj);
                if (adj_temp == NULL){
                    Node* temp = data_temp;
                    while (temp->right != NULL){
                        temp = temp->right;
                    }
                    temp->right = new Node(adj);
                    if (search_down(adj) == NULL){
                        Node* temp1 = head;
                        while (temp1->down != NULL){
                            temp1 = temp1->down;
                        }
                        temp1->down = new Node(adj);
                        temp1->down->right = new Node(data);
                        return;
                    }
                    else{
                        Node* temp1 = search_down(adj);
                        while (temp1->right != NULL){
                            temp1 = temp1->right;
                        }
                        temp1->right = new Node(data);
                        return;
                    }
                    return;
                }
                else{
                    cout << "Already Present! Error" << endl;
                    return;
                }
            }
        }
    }

    void DFS(Node* r){
        clear_visit_status();
        Stack s;
        Node* temp = r;
        mark_as_visited(temp->data);
        s.push(temp->data);
        while (!s.is_empty()){
            Node* temp1 = s.pop();
            cout << temp1->data << "->";
            Node* anchor = search_down(temp1->data);
            while (anchor != NULL){
                if (anchor->visited == 0){
                    s.push(anchor->data);
                    mark_as_visited(anchor->data);
                }
                anchor = anchor->right;
            }
        }
    }

    void BFS(Node* r){
        clear_visit_status();
        Queue q;
        Node* temp = r;
        mark_as_visited(temp->data);
        q.enqueue(temp->data);
        while (!q.empty()){
            Node* temp1 = q.dequeue();
            cout << temp1->data << "->";
            Node* anchor = search_down(temp1->data);
            while (anchor != NULL){
                if (anchor->visited == 0){
                    q.enqueue(anchor->data);
                    mark_as_visited(anchor->data);
                }
                anchor = anchor->right;
            }
        }
    }

    void mark_as_visited(string data){
        Node* temp = head;
        Node* temp1 = NULL;
        while (temp != NULL){
            temp1 = temp;
            while (temp1 != NULL){
                if (temp1->data == data){
                    temp1->visited = 1;
                }
                temp1 = temp1->right;
            }
            temp = temp->down;
        }
    }

    void clear_visit_status(){
        Node* temp1 = NULL;
        Node* temp = head;
        while (temp != NULL){
            temp1 = temp;
            while (temp1 != NULL){
                temp1->visited = 0;
                temp1 = temp1->right;
            }
            temp = temp->down;
        }
    }

    void display(){
        Node* temp1 = NULL;
        Node* temp2 = head;
        while (temp2 != NULL){
            temp1 = temp2;
            while (temp1 != NULL){
                if (temp1->right != NULL){
                    cout << temp1->data << "->";
                }
                else{
                    cout << temp1->data << "-" << endl;
                }
                temp1 = temp1->right;
            }
            cout << "|" << endl;
            temp2 = temp2->down;
        }
    }

    Node* search_down(string data){
        Node* temp = head;
        while (temp != NULL){
            if (temp->data == data){
                return temp;
            }
            temp = temp->down;
        }
        return NULL;
    }

    Node* search_right(Node* r, string data){
        Node* temp = r;
        while (temp != NULL){
            if (temp->data == data){
                return temp;
            }
            temp = temp->right;
        }
        return NULL;
    }

    void choice(){
        int x = 1;

        while (x == 1){
            cout << endl << "1 - Insert landmarks near College" << endl;
            cout << "2 - Display landmarks" << endl;
            cout << "3 - DFS" << endl;
            cout << "4 - BFS" << endl;
            cout << "5 - Exit" << endl;x
            cout << endl << "Enter choice - " << endl;
            int choice;
            cin >> choice;
            switch(choice){
                case 1:{
                    cout << "Enter data" << endl;
                    string data;
                    cin >> data;
                    cout << "Enter adjacent node - " << endl;
                    string adj;
                    cin >> adj;
                    insert(data, adj);
                    break;
                }
                case 2:{
                    display();
                    cout << endl;
                    break;
                }
                case 3:{
                    cout << "Enter source node-" << endl;
                    string data1;
                    cin >> data1;
                    Node* r = search_down(data1);
                    DFS(r);
                    cout << endl;
                    break;
                    
                }
                case 4:{
                    cout << "Enter source node-" << endl;
                    string data2;
                    cin >> data2;
                    Node* r1 = search_down(data2);
                    BFS(r1);
                    cout << endl;
                    break;
                }
                case 5:{
                    x = 2;
                    break;
                }
            }
        }
    }
};

int main(){
    Graph g;
    g.choice();
}
