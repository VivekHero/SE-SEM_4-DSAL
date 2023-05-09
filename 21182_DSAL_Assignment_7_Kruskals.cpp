#include <iostream>
#define MAX 30
using namespace std;

struct edge{
    int u,v,w;
};

class EdgeList{
    edge data[MAX];
    int n;
    public:
    friend class Graph;
    EdgeList(){
        n = 0;
    }

    void sort(){
        int i,j;
        edge temp;
        for (i = 1; i < n; i++){
            for (j = 0; j < n - i; j++){
                if (data[j].w > data[j+1].w){
                    temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        }
    }

    void print(){
        int i, cost = 0;
        for (i = 0; i < n; i++){
            cout << "\n" << data[i].u << " " << data[i].v << " " << data[i].w;
            cost = cost + data[i].w;
        }
        cout << endl;
        cout << "Cost of spanning tree is = " << cost << endl;
    }
};

class Graph{
    int G[MAX][MAX];
    int n;
    string* cities;

    public:
    Graph(){
        n = 0;
    }

    void readgraph();
    void displaygraph();
    void kruskals(EdgeList &);
    void choice();
};

void Graph::readgraph(){
    cout << "Enter the number of vertices" << endl;
    cin >> n;
    cities = new string[n];

    cout << "Enter names of cities" << endl;
    for (int i = 0; i < n; i++){
        cin >> cities[i];
    }

    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (i == j){
                G[i][j] = 0;
            }
            cout << "\nEnter cost to connect " << cities[i] << " and " << cities[j] << " : ";
            cin >> G[i][j];
            G[j][i] = G[i][j];
        }
    }
}

void Graph::displaygraph(){
    for (int i = 0; i < n; i++){
        if (i == 0){
            cout << "\t";
        }
        cout << cities[i] << "\t";
    }

    for (int i = 0; i < n; i++){
        cout << "\n";
        for (int j = 0; j < n; j++){
            if (j == 0){
                cout << cities[i] << "\t";
            }
            cout << G[i][j] << "\t";
        }
    }
}

int find(int belongs[], int vertexno){
    return (belongs[vertexno]);
}

void union1(int belongs[], int c1, int c2, int n){
    int i;
    for (i = 0; i < n; i++){
        if (belongs[i] == c2){
            belongs[i] = c1;
        }
    }
}

void Graph::kruskals(EdgeList &spanlist){
    int belongs[MAX],i,j,cno1,cno2;
    EdgeList elist;

    for (i = 1; i < n; i++){
        for (j = 0; j < i; j++){
            if (G[i][j] != 0){
                elist.data[elist.n].u = i;
                elist.data[elist.n].v = j;
                elist.data[elist.n].w = G[i][j];
                elist.n++;
            }
        }
    }
    elist.sort();
    for (int i = 0; i < n; i++){
        belongs[i] = i;
    }

    for (i = 0; i < elist.n; i++){
        cno1 = find(belongs,elist.data[i].u);
        cno2 = find(belongs,elist.data[i].v);
        if (cno1 != cno2){
            spanlist.data[spanlist.n] = elist.data[i];
            spanlist.n = spanlist.n + 1;
            union1(belongs,cno1,cno2,n);
        }
    }

}

void Graph::choice(){
    EdgeList spanning;
	int x = 1, choice;
	while (x == 1){
		cout << endl << "*******MENU*******" << endl;
		cout << "1. Read Graph" << endl;
		cout << "2. Display input adjacent matrix" << endl;
		cout << "3. Total cost of minimum spanning tree: " << endl;
		cout << "4. Exit" << endl;
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
				this->kruskals(spanning);
				cout << endl << "Total cost of Minimum Spanning Tree is using Kruskal's Algorithm : ";
				spanning.print();
                break;
			}
			case 4:{
				x = 2;
                break;
			}
			default : {
                cout << "Invalid Choice" << endl;
                break;
            }
		}
	}
}

int main(){
    Graph g;
    g.choice();
    return 0;
}
