#include <iostream>
#include <stack>

using namespace std;

// --------------------------------------------------------------
// --------------------------------------------------------------
// the 'Node' and 'SList' classes are fixed
// please do not modify them (except adding new member functions) 
// please add your implementation of the member functions 
// the 'Enumeration' function has been implemented for you 
// for the 'Insert' function, you probably want to dynamically allocate memory for a newly inserted node 
// --------------------------------------------------------------
// --------------------------------------------------------------

class Node { // "Node" class; each node is a student described by SID

public:

    int SID = 0;

    Node *ptr = NULL;
};


class SList { // singly linked list class; each node is an 'Node' object

public:

    SList() { head = NULL; }

    Node *GetList(); // return head pointer of the list

    void Enumerate();  // print all elements in the list, from head to tail, separately by a single space ' ' 

    int Search(int key);  // search for 'key' in the list; 
    // if found, return index of the node (starting from 0)
    // if not found, return -1

    void Insert(int key);  // insert key at the end of the list 

    void Remove(int key); // if key is in the list, remove it 
    // otherwise, do nothing

    void Reverse(); // reverse the list (tip: you can use stack)

    // add any other public member functions as you like 
    // ......
    // ...... 

private:
    Node *head;  // head pointer of the list
};


void SList::Enumerate() { // enumeration function, implemented for you
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->SID << ' ';
        temp = temp->ptr;
    }
};


// return head pointer of the list
Node *SList::GetList() {
    return head;
}


// search for 'key' in the list;
// if found, return index of the node (starting from 0)
// if not found, return -1
int SList::Search(int key) {
    int index = 0;
    Node *temp = head;
    while (temp->ptr != NULL) { //traverse the list while temp has data.
        if (temp->SID == key) { //if temp SID == key, found.
            return index;
        }
        index++; //else, move to the next index.
        temp = temp->ptr; //look at the next data.
    }
    return -1;
}


// insert key at the end of the list
void SList::Insert(int key) {
    Node *temp = head;
    Node *lastNode = new Node(); //create a new node to assign key
    lastNode->SID = key; //assign key to last node data.
    if (head == NULL) { //if list is empty assign key to head.
        head = lastNode;
    } else {
        while (temp->ptr != NULL) { //traverse the list while temp's next node has data.
            temp = temp->ptr;
        }
        temp->ptr = lastNode; //previous last node now points to the new last node.
    }
}


// if key is in the list, remove it
// otherwise, do nothing
//got advice from Maria Doan.
void SList::Remove(int key) {
    Node *nextHead = head->ptr;

    while (head->SID == key) { //if head is the key, assign the next node as new head and delete old head.
        head = nextHead;
    }

    Node *temp = head;
    Node *prev = temp;

    while (temp != NULL) { //traverse the list while temp has data.
        if (temp->SID == key) { //if temp's data == key,
            prev->ptr = temp->ptr; //previous node now connects to the next next node.
        } else {
            prev = temp; // store the current node to use it as a previous node later.
        }
        temp = temp->ptr;
    }
}


// reverse the list (tip: you can use stack)
void SList::Reverse() {
    Node *temp = head;
    stack<Node *> stack;

    while (temp != NULL) { //while temp has data, traverse.
        stack.push(temp); //push the current temp into the stack.
        temp = temp->ptr; //then move onto the next node and assign it to temp.
    }

    temp = stack.top(); //assign the top node as temp
    head = temp; //update head to the top node.
    stack.pop(); //pop the top node.

    while (!stack.empty()) { //as long as the stack is not empty, go over stack.
        temp->ptr = stack.top(); //temp next now points to the updated top node.
        stack.pop(); //pop the updated top node
        temp = temp->ptr; //move temp.
    }
    temp->ptr = NULL; //update last node pointer to NULL.
}


// --------------------------------------------------------------
// --------------------------------------------------------------
// the following merge function is only for your reference 
// you don't have to use recursion
// --------------------------------------------------------------
// --------------------------------------------------------------


Node *Split(Node *head, Node *left, Node *right) {
    Node *fast;
    Node *slow;
    slow = head;
    fast = head->ptr;

    if (head == NULL || head->ptr == NULL) { //assign left and right.
        left = head;
        right = NULL;
    } else {
        slow = head;
        fast = head->ptr;

        while (fast != NULL) { //while the fast node has data, traverse and assign the next node.
            fast = fast->ptr;
            if (fast != NULL) {
                slow = slow->ptr; //move the slow node at the same time.
                fast = fast->ptr;
            }
        }

        left = head; //update left
        right = slow->ptr; //update right
        slow->ptr = NULL; //splits the list here.

        return right;
    }
}


Node *Merge(Node *left, Node *right) {
    Node *SortedList = NULL; //create a node to assign in sorted order.

    //create a base case.
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    //assign the nodes in order.
    if (left->SID < right->SID) {
        SortedList = left;
        SortedList->ptr = Merge(left->ptr, right); //recursion on the left sublist.
    } else {
        SortedList = right;
        SortedList->ptr = Merge(left, right->ptr); //recursion on the right sublist.
    }
    return SortedList;
}


//got advice from Maria Doan.
Node *MergeSort(Node *ptr) {  // merge sort (recursive implementation)
    // input head pointer of a singly linked list
    // output head pointer of the sorted linked list

    // Step 1. split the list into two sub-lists
    // assume ptr1 is head of 1st sublist 
    // assume ptr2 is head of 2nd sublist
    Node *ptr1 = ptr;
    Node *ptr2 = ptr->ptr;

    if (ptr1 == NULL || ptr2 == NULL) { //check if it's a single node.
        return ptr;
    }

    //assign ptr2 to the head of the second sublist.
    ptr2 = Split(ptr, ptr1, ptr2);

    // Step 2. sort each sublist by calling the MergeSort
    ptr1 = MergeSort(ptr1);
    ptr2 = MergeSort(ptr2);

    // Step 3. merge the sorted sublists into a sorted list
    // you can define a function for that, or implement it directly here
    Node *head = Merge(ptr1, ptr2);

    // step 4. return the head pointer of the sorted list
    return head;
}


int main() {
    SList x;

    int operationChoice, Key2Search, Key2Remove, Key2Insert;

    int InputKey;
    int i = 0, y = 0;
    while (i < 10) {
        cin >> InputKey;
        x.Insert(InputKey);
        i++;
    }

    cin >> operationChoice;

    if (operationChoice == 1) {
        Node *head = x.GetList();
        cout << head->SID;
    } else if (operationChoice == 2) {
        cin >> Key2Search;
        y = x.Search(Key2Search);
        cout << y;
    } else if (operationChoice == 3) {
        cin >> Key2Insert;
        x.Insert(Key2Insert);
        x.Enumerate();
    } else if (operationChoice == 4) {
        cin >> Key2Remove;
        x.Remove(Key2Remove);
        x.Enumerate();
    } else if (operationChoice == 5) {
        x.Reverse();
        x.Enumerate();
    } else if (operationChoice == 6) {
        Node *sorted_list = MergeSort(x.GetList());

        while (sorted_list != NULL) {

            cout << sorted_list->SID << ' ';

            sorted_list = sorted_list->ptr;
        }
    } else {
        cout << "Enter a valid choice";
    }
    return 0;

}

