//============================================================================
// Name        : Assignment_7.cpp
// Author      : Vivek Gotecha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#define MAX 5
#define infinity 9999
using namespace std;

class Graph{
	int data[MAX][MAX];
	int n;
	string *cities;

public:
	Graph(int x){
		n = x;
		cities = new string[n];
	}

	void readgraph();
	void displaygraph();
	int prims(Graph &);
	void choice();
};

void Graph::readgraph(){
	int i,j;
	for (int i = 0; i < n; i++){
		cout << "Enter the " << i + 1 << " source city : " << endl;
		cin >> cities[i];
		for (int j = 0; j < n; j++){
			cout << "Enter the " << j + 1 << " destination city : " << endl;
			cin >> cities[j];
			cout << endl << "Enter the cost between cities: ";
			cin >> data[i][j];
		}
	}
}


void Graph::displaygraph(){
	int i,j;

	for (int i = 0; i < n; i++){
		if (i == 0){
			cout << "\t";
		}
		cout << cities[i] << "\t";
	}
	cout << endl;
	for (i = 0; i < n; i++){
		cout << endl;
		for (j = 0; j < n; j++){
			if (j == 0){
				cout << cities[i] << "\t";
			}
			cout << data[i][j] << "\t";
		}
	}
}

int Graph::prims(Graph &spanning){
	int cost[MAX][MAX];
	int u,v,min_distance,distance[MAX],from[MAX];
	int visited[MAX],i,j,min_cost,no_of_edges;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (data[i][j] == 0){
				cost[i][j] = infinity;
			}
			else{
				cost[i][j] = data[i][j];
			}
			spanning.data[i][j] = 0;
		}
	}
	distance[0] = 0;
	visited[0] = 1;

	for (i = 1; i < n; i++){
		distance[i] = cost[0][i];
		visited[i] = 0;
		from[i] = 0;
	}
	min_cost = 0;
	no_of_edges = n - 1;
	while (no_of_edges > 0){
		min_distance = infinity;

		for (int i = 1; i < n; i++){
			if (visited[i] == 0 && distance[i] < min_distance){
				v = i;
				min_distance = distance[i];
			}
		}
		u = from[v];
		spanning.data[u][v] = distance[v];
		spanning.data[v][u] = distance[v];
		no_of_edges--;
		visited[v] = 1;

		for (i = 1; i < n; i++){
			if (visited[i] == 0 && cost[i][v] < distance[i]){
				distance[i] = cost[i][v];
				from[i] = v;
			}
		}
		min_cost = min_cost + cost[u][v];
	}
	spanning.n = n;
	return (min_cost);
}

void Graph::choice(){
	Graph spanning(n);
	int x = 1, choice;
	while (x == 1){
		cout << endl << "*******MENU*******" << endl;
		cout << "1. Read Graph" << endl;
		cout << "2. Display input adjacent matrix" << endl;
		cout << "3. Display Spanning distance matrix" << endl;
		cout << "4. Total cost of minimum spanning tree: " << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;

		switch(choice){
			case 1:{
				this->readgraph();
				break;
			}
			case 2:{
				cout << endl << "The original graph (input adjacency matrix) is: " << endl;
				this->displaygraph();
				break;
			}
			case 3:{
				int total_cost = this->prims(spanning);
				cout << endl << "Spanning tree matrix: " << endl;
				spanning.displaygraph();
				break;
			}
			case 4:{
				int total_cost = this->prims(spanning);
				cout << endl << " Total cost of minimum spanning tree= " << total_cost;
				break;
			}
			case 5:{
				x = 2;
				break;
			}
		}
	}
}


int main() {
	int n;
	cout << "Enter the number of cities(Vertices)" << endl;
	cin >> n;
	Graph g(n);
	g.choice();
	return 0;
}







