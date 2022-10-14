#include <iostream>

using namespace std;

class Array {

public:
    // please implement the following six member functions
    void Set(int key, int index);  // assign "key" to "x[index]"
    int *Get();                    // return pointer to a copy of array x
    // must be a copy, not x itself
    void Sort_Bubble();            // bubble sort array x
    void Sort_Insertion();         // insertion sort array x
    int Search_Linear(int key);    // linear search of "key" in the array
    // if success, return index of key
    // if fail, return -1
    int Search_Binary(int key);    // binary search of "key" in the array
    // if success, return index of key
    // if fail, return -1
private:
    int x[10];                     // array size is fixed to 10
    int size = sizeof(x) / sizeof(x[0]); //get the size of array by dividing
    // the total memory of the array by the size of each element.
};


// assign "key" to "x[index]".
void Array::Set(int key, int index) {
    x[index] = key;
}


// return pointer to a copy of array x.
int *Array::Get() {
    //make a copy of array x.
    int *copy = new int[size];
    for (int i = 0; i < size; i++) {
        copy[i] = x[i];
    }
    //return pointer to the copied array.
    return copy;
}


//got advice from Maria Doan.
// bubble sort array x.
void Array::Sort_Bubble() {
    int numSwap = 1;
    while (numSwap != 0) {
        numSwap = 0; //reset to 0, so you can go over the whole array again from the start.
        for (int i = 0; i < size - 1; i++) { //swap previous and next numbers if the previous number is bigger.
            if (x[i] > x[i + 1]) {
                swap(x[i], x[i + 1]);
                numSwap++;
            }
        }
    }
}


// insertion sort array x.
void Array::Sort_Insertion() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) { //start from an index after i to compare them back to back.
            if (x[j] < x[i]) { //if the next number is smaller than the previous, swap them.
                swap(x[i], x[j]);
            }
        }
    }
}


// linear search of "key" in the array
// if success, return index of key
// if fail, return -1
int Array::Search_Linear(int key) {
    for (int i = 0; i < size - 1; i++) { //traverse the array by going through each index.
        if (x[i] == key) {
            return i;
        }
    }
    return -1;
}


// binary search of "key" in the array
// if success, return index of key
// if fail, return -1
int Array::Search_Binary(int key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (x[mid] == key) { //if middle number is the key, return mid.
            return mid;
        } else if (x[mid] > key) { //if middle is greater than key, replace right to the left of mid.
            right = mid - 1;
        } else {
            left = mid + 1; //if middle is less than key, replace left to the right of mid.
        }
    }
    return -1;
}


int main() {
    Array A;

    int InputKey, operationChoice, SearchKey, IndexKey;
    int i = 0;
    while (i < 10) {
        cin >> InputKey;             // Reads the input numbers from the console
        A.Set(InputKey, i);
        i++;
    }

    // if operationChoice = 1, directly output elements in A
    // if operationChoice = 2, sort elements in A by bubble sort and output result
    // if operationChoice = 3, sort elements in A by insertion sort and output result
    // if operationChoice = 4, apply linear search to search for "SearchKey" in A
    // if operationChoice = 5, first apply bubble sort on A, then apply binary search to search for "SearchKey" in A
    cin >> operationChoice;
    int *temp;

    if (operationChoice == 1) {
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs
        }
    } else if (operationChoice == 2) {
        A.Sort_Bubble();
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs
        }
    } else if (operationChoice == 3) {
        A.Sort_Insertion();
        temp = A.Get();
        for (int i = 0; i < 10; i++) {
            cout << temp[i] << ' ';   // outputs are separated by tabs
        }
    } else if (operationChoice == 4) {
        cin >> SearchKey;
        IndexKey = A.Search_Linear(SearchKey);
        cout << IndexKey << endl;
    } else if (operationChoice == 5) {
        cin >> SearchKey;
        A.Sort_Bubble();
        IndexKey = A.Search_Binary(SearchKey);
        cout << IndexKey << endl;
    } else {
        cout << "Enter a valid choice";
    }
    return 0;
}

