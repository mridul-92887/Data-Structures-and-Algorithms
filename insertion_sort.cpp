#include <iostream>
using namespace std;

void insertionSort(int array[], int n) {
    for(int i = 1; i < n; i++) {
        int current = array[i];
        int prev = i - 1;

        while(prev >= 0 && array[prev] > current) {
            array[prev + 1] = array[prev];
            prev--;
        }
        array[prev + 1] = current;
    }
}

void printArray(int array[], int n) {
    for(int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    int array[] = {12, 11, 13, 5, 6};
    int n = sizeof(array) / sizeof(array[0]);

    cout << "Before Sorting: ";
    printArray(array, n);

    insertionSort(array, n);

    cout << "After Sorting: ";
    printArray(array, n);

    return 0;
}