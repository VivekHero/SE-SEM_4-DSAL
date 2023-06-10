/* Source - Sahil Sharma (GitHub Link -- https://github.com/SharmaSahil2003)
*/

#include <iostream>
#include <climits>
#define MAX 10
using namespace std;

class TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;

    public:
    TreeNode(){
        val = 0;
        left = right = NULL;
    }

    friend class OBST;
};

class cwr{
    int cost, weight, root;

    public:
    cwr(){
        cost = 0;
        weight = 0;
        root = 0;
    }

    friend class OBST;
};

class OBST{
    int key[MAX], p[MAX], q[MAX], cost, n;
    cwr arr[MAX][MAX];
    TreeNode *tree;

    public:
    OBST(){
        tree = NULL;
        cost = 0;
        n = 0;
        for (int i = 0; i < MAX; i++){
            key[i] = p[i] = q[i] = 0;
        }
    }

    void input(){
        cout << "Enter number of entries : " << endl;
        cin >> n;

        for (int i = 1; i <= n; i++){
            cout << "Enter Node " << i << " : ";
            cin >> key[i]; 
        }
        cout << endl;

        for (int i = 1; i <= n; i++){
            cout << "Enter Success Probability Of Node " << i << " : ";
            cin >> p[i];
        }
        cout << endl;

        for (int i = 0; i <= n; i++){
            cout << "Enter Unsuccess Probability of Node " << i << " : ";
            cin >> q[i];
        }
        cout << endl;
    }

    int getweight(int i, int j){
        if (i == j){
            return q[i];
        }

        return arr[i][j - 1].weight + p[j] + q[j];
    }

    int getcost(int i, int j){
        if (i == j){
            return 0;
        }

        int min_val = INT_MAX;
        int indx = 0;

        for (int l = i + 1; l <= j; l++){
            int temp = arr[i][l - 1].cost + arr[l][j].cost;

            if (temp < min_val){
                min_val = temp;
                indx = l;
            }
        }

        arr[i][j].root = indx;
        return min_val + arr[i][j].weight;
    }

    void create(){
        for (int c = 0; c <= n; c++){
            for (int i = 0, j = c ; j <= n && i <= n ; i++, j++){
                arr[i][j].weight = getweight(i, j);
                arr[i][j].cost = getcost(i, j); 
            }
        }

        cout << "ARRAY COST: " << endl;
        for (int c = 0; c <= n; c++){
            for (int i = 0, j = c; j <= n && i <= n; i++, j++){
                cout << arr[i][j].cost << " ";
            }
            cout << endl;
        }

        cout << "ARRAY WEIGHT: " << endl;
        for (int c = 0; c <= n; c++){
            for (int i = 0, j = c; j <= n && i <= n; i++, j++){
                cout << arr[i][j].weight << " ";
            }
            cout << endl;
        }

        cout << "ARRAY ROOT: " << endl;
        for (int c = 0; c <= n; c++){
            for (int i = 0, j = c; j <= n && i <= n; i++, j++){
                cout << arr[i][j].root << " ";
            }
            cout << endl;
        }

        cout << "FINAL COST : " << arr[0][n].cost << endl;
        tree = buildtree(0, n);
    }

    TreeNode *buildtree(int i, int j){
        cout << i << " " << j << endl;
        if (i >= j){
            cout << "Returned NULL" << endl;
            return NULL;
        }
        else{
            TreeNode *root = new TreeNode();
            root->val = key[arr[i][j].root];
            root->left = buildtree(i, arr[i][j].root - 1);
            root->right = buildtree(arr[i][j].root, j);
            return root;
        }
    }

    void inorder(TreeNode *root){
        if (root == NULL){
            return;
        }

        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }

    void preorder(TreeNode *root){
        if (root == NULL){
            return;
        }

        cout << root->val << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void check(){
        cout << "Inorder - " << endl;
        inorder(tree);
        
        cout << endl;
        
        cout << "Preorder - " << endl; 
        preorder(tree);
        
        cout << endl;
    }
};

int main(){
    OBST obj;
    int choice;
    
    do{
        cout << "----- MENU -----" << endl;
        cout << "1. Input keys and corresponding probabilties" << endl;
        cout << "2. Create OBST" << endl;
        cout << "3. Display the inorder and preorder of OBST" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        
        switch(choice){
            case 1:{
                obj.input();
                break;
            }
            case 2:{
                obj.create();
                break;
            }
            case 3:{
                obj.check();
                break;
            }
            case 4:{
                cout << "Thank you for visiting" << endl;
                exit(0);
                break;
            }
            default:{
                cout << "Invalid choice entered" << endl;
            }
        }
    }while(choice != 4);
    
    return 0;
}
