#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void countSort(int arr[], int n) {
    if (n <= 0){
        return;
    }
    int k = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            cerr << "Error: Counting sort cannot handle negative numbers.\n";
            return;
        }
        k = max(k, arr[i]);
    }

    vector<int> count(k + 1, 0);

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }

    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

int main() {
    int arr[] = {1, 3, 2, 3, 4, 1, 6, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    countSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
