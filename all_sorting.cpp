#include<bits/stdc++.h>
using namespace std;

// Binary Search
int binarysearch(int array[], int n, int target) {
    int start = 0, end = n - 1;
    while(start <= end) {
        int mid = (start + end) / 2;
        if(target > array[mid]) {
            start = mid + 1;
        } else if(target < array[mid]) {
            end = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// Bubble Sort
void bubblesort(int array[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionsort(int array[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIDX = i;
        for(int j = i + 1; j < n; j++) {
            if(array[j] < array[minIDX]) {
                minIDX = j;
            }
        }
        if(minIDX != i) {
            swap(array[i], array[minIDX]);
        }
    }
}

// Insertion Sort
void insertionsort(int array[], int n) {
    for(int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// Merge Sort
void merge(int array[], int s, int mid, int e) {
    int n1 = mid - s + 1;
    int n2 = e - mid;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++) {
        L[i] = array[s + i];
    }
    for(int i = 0; i < n2; i++) {
        R[i] = array[mid + 1 + i];
    }
    int i = 0, j = 0, k = s;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }
    while(i < n1) {
        array[k++] = L[i++];
    }
    while(j < n2) {
        array[k++] = R[j++];
    }
}

void mergesort(int array[], int s, int e) {
    if(s >= e) return;
    int mid = (s + e) / 2;
    mergesort(array, s, mid);
    mergesort(array, mid + 1, e);
    merge(array, s, mid, e);
}

// Quick Sort
int partition(int array[], int s, int e) {
    int pi = array[e];
    int i = s - 1;
    for(int j = s; j < e; j++) {
        if(array[j] < pi) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[e]);
    return i + 1;
}

void quicksort(int array[], int s, int e) {
    if(s >= e) return;
    int p = partition(array, s, e);
    quicksort(array, s, p - 1);
    quicksort(array, p + 1, e);
}

// Counting Sort
void countingsort(int array[], int n) {
    int k = array[0];
    for(int i = 1; i < n; i++) {
        if(array[i] < 0) {
            cout << "Error: Counting sort cannot handle negative numbers.\n";
            return;
        }
        k = max(k, array[i]);
    }
    vector<int> count_array(k + 1, 0);
    for(int i = 0; i < n; i++) {
        count_array[array[i]]++;
    }
    for(int i = 1; i <= k; i++) {
        count_array[i] += count_array[i - 1];
    }
    vector<int> final_array(n);
    for(int i = n - 1; i >= 0; i--) {
        final_array[count_array[array[i]] - 1] = array[i];
        count_array[array[i]]--;
    }
    for(int i = 0; i < n; i++) {
        array[i] = final_array[i];
    }
}

// Print Array
void printArray(int array[], int n) {
    cout << "Array: ";
    for(int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
}

// Main Menu
int main() {
    while(true) {
        cout << "\n--- Sorting & Searching Menu ---\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Merge Sort\n";
        cout << "5. Quick Sort\n";
        cout << "6. Counting Sort\n";
        cout << "7. Binary Search\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if(choice == 0) {
            break;
        }

        cout << "Enter number of elements: ";
        int n;
        cin >> n;

        int array[n];
        cout << "Enter " << n << " elements: ";
        for(int i = 0; i < n; i++) {
            cin >> array[i];
        }

        switch(choice) {
            case 1: bubblesort(array, n); break;
            case 2: selectionsort(array, n); break;
            case 3: insertionsort(array, n); break;
            case 4: mergesort(array, 0, n - 1); break;
            case 5: quicksort(array, 0, n - 1); break;
            case 6: countingsort(array, n); break;
            case 7: {
                sort(array, array + n); // binary search requires sorted array
                printArray(array, n);
                cout << "Enter value to search: ";
                int target;
                cin >> target;
                int index = binarysearch(array, n, target);
                if(index == -1) {
                    cout << "Not found.\n";
                } else {
                    cout << "Found at index: " << index << "\n";
                }
                continue;
            }
            default: cout << "Invalid choice.\n"; continue;
        }

        printArray(array, n);
    }

    return 0;
}
