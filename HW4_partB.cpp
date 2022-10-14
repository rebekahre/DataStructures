#include <iostream>
#include <vector>

using namespace std;

// In this project, implement a minimum heap using vector
//
// Implement two functions 
// -- insert(int key): insert a new key into the heap 
// -- remove(): remove the root key from the heap 
// 
// In the main function, we will first input 10 keys into the heap 
// Then, we will enumarate them from the vector 
// The enumeration function has been implemented for you 
// 

class heap {

public:
    void enumerate(); // enumerate all elements in the heap 

    void insert(int key); // insert a new key into the heap vector 

    void remove(); // remove root key from the heap 

    int parent(int key);

    int left(int key);

    int right(int key);

    void bubbleUp(int key);

    void bubbleDown(int key);


private:
    vector<int> x;
};


void heap::enumerate() {

    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << ' ';
    }
}


int heap::parent(int key) { //returns parent index
    return (key - 1) / 2;
}


int heap::left(int key) { //returns left child
    return (2 * key) + 1;
}


int heap::right(int key) { //returns right child
    return (2 * key) + 2;
}


void heap::bubbleUp(int key) {
    if (key && x[parent(key)] > x[key]) { //if key and key's parent disturb heap,
        swap(x[parent(key)], x[key]); //swap them.
        bubbleUp(parent(key)); //continue swapping if it's out of order.
    }
}


void heap::bubbleDown(int key) {
    int l = left(key);
    int r = right(key);
    int lowest = key;

    if (l < x.size() && x[l] < x[key]) {
        lowest = l; //index at left key has the lowest value.
    }
    if (r < x.size() && x[r] < x[lowest]) {
        lowest = r; //index at right key has the lowest value.
    }
    if (lowest != key) { //if key doesn't have the lowest value,
        swap(x[key], x[lowest]); //swap with a child that has the lower value
        bubbleDown(lowest); //go down until the key has the lowest value.
    }
}


void heap::insert(int key) { // insert a new key into the heap vector (recursive)
    x.push_back(key); //insert key to the end of vector.
    int index = x.size() - 1;
    bubbleUp(index); //bubbleUp the heap until you hit the index. This restores heap property.
}


void heap::remove() { // remove root key from the heap (also recursive)
    x[0] = x.back(); //replace the root with the last element of vector.
    x.pop_back(); //then pop the last element.
    bubbleDown(0); //then bubbleDown from root node to restore heap property.
}


int main() {
    int tmp[10];

    for (int i = 0; i < 10; i++) {

        cin >> tmp[i];
    }

    heap x;
    for (int i = 0; i < 10; i++) {
        x.insert(tmp[i]);
    }

    int operationChoice;

    cin >> operationChoice;

    if (operationChoice == 1) { // enumerate key 

        x.enumerate();
    } else if (operationChoice == 2) { // remove the smallest element from the heap and update the heap
        x.remove();
        x.enumerate();
    } else {

        cout << "Enter a valid choice";
    }

    return 0;
}


