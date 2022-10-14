#include <iostream>

using namespace std;

//Maria Doan has helped me with this assignment.
class Node {

public:

    int SID = 0;

    Node *left = NULL;

    Node *right = NULL;

    Node *parent = NULL;

    int balanceFactor = 0;

    int height = -1;

};


class AVL {

public:

    Node *GetRoot(); // return root node pointer; not really used in testing

    void AVL_Enumerate(); // enumerate nodes based on in-order traverse 

    void AVL_Insert(Node *x); // insert a new node x into AVL tree

private:

    Node *root = NULL;
};


Node *AVL::GetRoot() { //return root
    return root;
}


int depth(Node *ptr) { // measure depth of a node

    int counter = 0;

    while (ptr->parent != NULL) {

        ptr = ptr->parent;

        counter++;
    }

    return counter;
}


void enumerate(Node *ptr) { // in-order traverse

    if (ptr->left != NULL) {

        enumerate(ptr->left);

    }
    cout << ptr->SID << ' ';

    if (ptr->right != NULL) {

        enumerate(ptr->right);
    }
}


void AVL::AVL_Enumerate() {

    enumerate(root);
}


int isRoot(Node *ptr) { // check if node is root or not

    if (ptr->parent == NULL) {

        return 1;
    } else {

        return 0;
    }
}


int isLeaf(Node *ptr) { // check if node is leaf or not

    if (ptr->left == NULL && ptr->right == NULL) {

        return 1;
    } else {

        return 0;
    }
}


Node *insert(Node *root, Node *x) { // insert a node to a tree with root

    if (root == NULL) {

        root = x;
    } else {

        if (x->SID <= root->SID) {
            root->left = insert(root->left, x);
            //update root
            root->left->parent = root;
        } else {
            root->right = insert(root->right, x);
            //update root
            root->right->parent = root;
        }
    }

    return root;
}


int findmax(Node *root) { // find max node from a tree with root

    if (root->right == NULL) {

        return root->SID;
    } else {

        return findmax(root->right);
    }
}


//find height of the tree
int height(Node *x) {
    if (x == NULL) {
        return 0;
    }
    if (isLeaf(x) == 1) {
        return 1;
    } else {
        int left = height(x->left);
        int right = height(x->right);
        if (left > right) {
            return left + 1; //the parent node is greater than 1.
        } else {
            return right + 1; //same goes to the right parent node.
        }
    }
}


int findBalance(Node *x) { //find balance factor of node x.
    if (x == NULL) {
        return 0;
    } else {
        return height(x->left) - height(x->right); //subtract height of left node from height of right node.
    }
}


Node *rotation_clockwise(Node *root) { //rotate tree at root clockwise
    Node *temp = root->left;

    if (root->left->right != NULL) {
        root->left = root->left->right;
    }

    temp->right = root;
    //update parent if there's a problem.
    if (temp->parent == temp->right) {
        temp->parent = temp->parent->parent;
        temp->right->parent = temp;
    }
    if (temp->right->left == temp) {
        temp->right->left = NULL;
    }

    root = temp;

    //replace rebalanced subtree into the tree.
    if (root->parent != NULL && root->SID < root->parent->SID) {
        root->parent->left = root;
    } else if (root->parent != NULL && root->SID > root->parent->SID) {
        root->parent->right = root;
    }
    return root;
}


Node *rotation_counterclock(Node *root) { // rotate tree at root counter-clockwise

    Node *temp = root->right;

    if (root->right->left != NULL) {

        root->right = root->right->left;
    }

    temp->left = root;

    //update parent if there's a problem.
    if (temp->parent == temp->left) {
        temp->parent = temp->parent->parent;
        temp->left->parent = temp;
    }
    if (temp->left->right == temp) {
        temp->left->right = NULL;
    }

    root = temp;

    //replace rebalanced subtree into the tree.
    if (root->parent != NULL && root->SID < root->parent->SID) {
        root->parent->left = root;
    } else if (root->parent != NULL && root->SID > root->parent->SID) {
        root->parent->right = root;
    }

    return root;
}


void AVL::AVL_Insert(Node *x) { //insert a new node into AVL tree
    root = insert(root, x); //begin with BST insertion.

    Node *temp = x;
    int balance = findBalance(x); //get balance factor to check if it's unbalanced.

    while (temp->parent != NULL && balance > -2 && balance < 2) { //find the lowest unbalanced node if it exists.
        temp = temp->parent;
        balance = findBalance(x); //use recursive to continuously go up the tree.
    }

    //if node is unbalanced, go through the rotations.
    if (balance > 1 && x->SID < temp->left->SID) { //Left-Left
        temp = rotation_clockwise(x);
    }

    if (balance < -1 && x->SID > temp->right->SID) { //Right-right
        temp = rotation_counterclock(x);
    }

    if (balance > 1 && x->SID > temp->left->SID) { //Left-right
        temp->left = rotation_counterclock(temp->left); //rotate left first.
        temp = rotation_clockwise(x); //then rotate right.
    }

    if (balance < -1 && x->SID < temp->right->SID) { //Right-left
        temp->right = rotation_clockwise(temp->right); //rotate right first.
        temp = rotation_counterclock(x); //then rotate left.
    }
}


int main() {
    Node tmp[10];

    for (int i = 0; i < 10; i++) {

        cin >> tmp[i].SID;
    }

    AVL x;

    for (int i = 0; i < 10; i++) {

        x.AVL_Insert(&tmp[i]);
    }

    int operationChoice;

    cin >> operationChoice;

    if (operationChoice == 1) { // enumerate key 

        x.AVL_Enumerate();
    } else {

        cout << "Enter a valid choice";
    }

    return 0;
}
