#include <iostream>

using namespace std;


class Student {
public:
    int SID = 0;
    float GPA = 0;
    Student *ptr = NULL;
};


class HashTable {
public:

    int Insert(Student *y); // insert a student x based on x.SID
    // return 1 if insertion is successful
    // return -1 if insertion fails (e.g. table full)

    float Search(int key);  // search for a student with SID=key in the table 
    // return GPA if student is found
    // return -1 if student is not found

    int Remove(int key);   // remove a student with SID=key from the table 
    // return 1 if student is found and removed
    // return -1 if student is not found

    void Enumerate();  // enumerate all numbers, already implemented for you 

private:

    Student *x[5] = {NULL, NULL, NULL, NULL, NULL}; // array of student pointers
    int link[5] = {-1, -1, -1, -1, -1}; // link array, all initialized to -1
    int Counter[5] = {0, 0, 0, 0, 0};

    int hash(int key); // hash function, already implemented for you
};


int HashTable::hash(int key) { //hash function
    return key % 2;
}


void HashTable::Enumerate() {

    Student *temp;

    for (int i = 0; i < 5; i++) {

        temp = x[i];

        while (temp != NULL) {       // print the chain

            cout << temp->SID << ' ';

            temp = temp->ptr;
        }

        cout << link[i] << '\n';  // last number is the corresponding link value, then change line 
        // so, basically, each line for one chain + corresponding link
    }

}


// insert a student x based on x.SID
// return 1 if insertion is successful
// return -1 if insertion fails (e.g. table full)
//Got advice from Maria Doan.
int HashTable::Insert(Student *y) {

    int new_SID, sizeTable = 5;
    new_SID = hash(y->SID); //gets index in hash table from SID.

    while (new_SID != -1) { //traverse the list
        //check first node
        if (x[new_SID] == NULL) { //if no collision detected,
            x[new_SID] = y; //insert student into index of hash table.
            Counter[new_SID]++; //increment counter.
            return 1;
        }
            //check second node
        else if (x[new_SID]->ptr == NULL) { //if next node is null, insert SID.
            x[new_SID]->ptr = y; //insert student into index of hash table.
            Counter[new_SID]++; //increment counter.
            return 1;
        } else { //if slot is full, use linear probing to find next empty slot. Then update link array
            int counter = 0;
            while (counter < sizeTable && x[counter] != NULL) { //traverse the array
                ++counter; //update counter if I find an empty slot.
            }
            if (link[new_SID] == -1 && counter < sizeTable) {
                link[new_SID] = counter; //link is now pointing to the next empty slot in array.
            }
            new_SID = link[new_SID]; //update data.
        }
    }
    return -1;
}


// search for a student with SID=key in the table
// return GPA if student is found
// return -1 if student is not found
float HashTable::Search(int key) {
    for (int i = 0; i < 5; i++) { //traverse
        if (x[i] != NULL) {
            if (x[i]->SID == key) { //if student SID == key, return student GPA.
                return x[i]->GPA;
            } else if (x[i]->ptr != NULL &&
                       x[i]->ptr->SID == key) { //else if the student ptr SID == key, return student ptr's GPA.
                return x[i]->ptr->GPA;
            }
        }
    }
    return -1;
}


// remove a student with SID=key from the table
// return 1 if student is found and removed
// return -1 if student is not found
int HashTable::Remove(int key) {
    for (int i = 0; i < 5; i++) { //traverse
        if (x[i] != NULL) {
            if (x[i]->SID == key) { //if student SID == key, remove student and return 1.
                x[i] = x[i]->ptr;
                return 1;
            } else if (x[i]->ptr != NULL &&
                       x[i]->ptr->SID == key) { //else if the student ptr SID == key, assign that student to NULL.
                x[i]->ptr = NULL;
                return 1;
            }
        }
    }
    return -1;
}


int main() {
    HashTable table;

    for (int i = 0; i < 10; i++) {
        Student *x = new Student;
        cin >> x->SID >> x->GPA;
        x->ptr = NULL;
        table.Insert(x);
    }

    int operationChoice, SearchKey, RemoveKey;

    cin >> operationChoice >> SearchKey >> RemoveKey;

    if (operationChoice == 1) {

        table.Enumerate();
    } else if (operationChoice == 2) {

        cout << table.Search(SearchKey);
    } else if (operationChoice == 3) {

        table.Remove(RemoveKey);
        table.Enumerate();

    } else {

        cout << "Enter a valid choice";
    }
    return 0;
}
