#include <iostream>
#include <vector>
using namespace std;
// Apna C L G
int partition(vector<int>& arr, int st, int end) {
    int idx = st - 1;
    int pivot = arr[end];
    
    for (int j = st; j < end; j++) {
        if (arr[j] <= pivot) {
            idx++;
            swap(arr[j], arr[idx]);
        }
    }
    
    idx++;
    swap(arr[end], arr[idx]);
    return idx;
}

void quickSort(vector<int>& arr, int st, int end) {
    if (st < end) {
        int pivIdx = partition(arr, st, end);
        quickSort(arr, st, pivIdx - 1);
        quickSort(arr, pivIdx + 1, end);
    }
}

// V E C T O R 
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot is last element
    int i = low - 1;        // index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);  // return pivot index
}
void quickSort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }
    int pi = partition(arr, low, high);  // partitioning index

    quickSort(arr, low, pi - 1);   // sort left part
    quickSort(arr, pi + 1, high);  // sort right part
}


int main() {
    vector<int> arr = {12, 4, 7, 9, 1, 3, 5, 8};
    int st = 0;
    int end = arr.size() - 1;
    
    quickSort(arr, st, end);
    
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
