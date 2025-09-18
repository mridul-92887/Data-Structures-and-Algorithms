#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];   // key = বর্তমান element যেটাকে ঠিক জায়গায় বসাতে হবে
        int j = i - 1;

        // যতক্ষণ পর্যন্ত আগের উপাদান key থেকে বড়, ততক্ষণ সেগুলো ডান দিকে সরাও
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // এখন key তার সঠিক জায়গায় বসে
        arr[j + 1] = key;
    }
} 

void printArray(int arr[], int n) {
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[100], n;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
