#include <iostream>
#include <stack>
#include <queue>
using namespace std;


// the node class is used to creat list representation
//got advice from Baraa Ahmad.
class Node {

public:

    int SID = -1;

    Node *next = NULL;
};


// here is the graph class 
// assume we work on an undirected graph of 6 nodes (fix size) 
// it has a matrix representation and a list representation 
// ask students to input matrix representation
// and design a function to convert that to a list representation 
class Graph {

public:

    Graph();

    void SetMatrix(int a, int b); // set Matrix[a][b] = Matrix[b][a] = 1
    // a and b must be in [0,5]
    // already implemented

    void DeleteMatrix();  // reset matrix to zero
    // already implemented

    void Convert(); // convert matrix representation to list
    // in the list, make sure nodes are sorted in an ascending order
    // @TODO: you need to implement this method

    void EnumerateList(); // enumerate all nodes in the list
    // already implemented

    int *DFS(int idx);  // depth first search based on list representation
    // idx represents the first node to visit
    // whenever there is a tie, choose the smallest node to visit first
    // return a pointer to an array of 6 nodes based on the order they are visited
    // for example, if DFS visits 3, 5, 2, 0, 1, 4; then the array should have
    // x[0]=3, x[1]=5, x[2]=2, x[3]=0, x[4]=1, x[5]=4
    // @TODO: you need to implement this method

private:

    int Matrix[6][6];

    Node *List[6];

};


// enumerate nodes in a list
void Graph::EnumerateList() {

    Node *temp;

    for (int i = 0; i < 6; i++) {

        cout << i << " -> ";

        if (List[i] != NULL) {

            temp = List[i];

            cout << temp->SID;

            while (temp->next != NULL) {

                temp = temp->next;

                cout << " -> " << temp->SID << ' ';
            }
            cout << endl;
        }
    }
}


// SetMatrix Function
void Graph::SetMatrix(int a, int b) {

    Matrix[a][b] = 1;

    Matrix[b][a] = 1;
}


// DeleteMatrix Function
void Graph::DeleteMatrix() {

    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {

            Matrix[i][j] = 0;
        }
    }
}


// constructor
Graph::Graph() {

    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {

            Matrix[i][j] = 0;
        }

        List[i] = NULL;
    }
}


// convert matrix representation to list
// in the list, make sure nodes are sorted in an ascending order
// @TODO: you need to implement this method
void Graph::Convert() {
    for (int i = 0; i < 6; i++) { //i is row
        Node *node = new Node(); //create a new node
        for (int j = 0; j < 6; j++) { //j is column
            if (Matrix[i][j] == 1) { //if a number is visited,
                if (List[i] == NULL) { //and if list row is empty,
                    node->SID = j; //assign j(index column) to node
                    List[i] = node; //assign that node to List row.
                } else { //else if a number is not visited,
                    node->next = new Node();
                    node->next->SID = j;
                    node = node->next; //assign the node's next to node.
                }
            }
        }
    }
}


// depth first search based on list representation
// idx represents the first node to visit
// whenever there is a tie, choose the smallest node to visit first
// return a pointer to an array of 6 nodes based on the order they are visited
// for example, if DFS visits 3, 5, 2, 0, 1, 4; then the array should have
// x[0]=3, x[1]=5, x[2]=2, x[3]=0, x[4]=1, x[5]=4
// @TODO: you need to implement this method
int *Graph::DFS(int idx) {
    static int x[6]; //create array x
    static int marked[6]; //create array that's marked.
    marked[idx] = 1; //idx is now visited, so it's marked.

    static int i;
    x[i++] = idx; //increment to insert at the next element.

    Node *temp = List[idx];
    while (temp != NULL) { //while temp is not NULL,
        if (!marked[temp->SID]) { //and if temp is not marked(not visited),
            DFS(temp->SID); //go through DFS and update.
        }
        temp = temp->next; //if temp is marked, go to the next.
    }
    return x;
}


int main() {

    Graph graph;

    int a, b; // the values of a and b are between 0 and 5
    int *visit;

    // always input 8 edges
    for (int i = 0; i < 8; i++) {

        cin >> a >> b;

        graph.SetMatrix(a, b);
    }

    int idx;
    cin >> idx;

    // always immediately convert matrix into list
    cout << "Adjacency List" << endl;
    graph.Convert();
    graph.DeleteMatrix();
    graph.EnumerateList();

    cout << "DFS" << endl;
    visit = graph.DFS(idx);

    for (int i = 0; i < 6; i++) {

        cout << visit[i] << ' ';
    }

    return 0;
}

