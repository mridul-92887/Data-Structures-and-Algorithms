#include <bits/stdc++.h>
using namespace std;

void reverseArray(vector<int>& arr, int start, int end) {
    if (start >= end) {
        return;
    } 
    else {
        swap(arr[start], arr[end]);
        reverseArray(arr, start + 1, end - 1);
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    reverseArray(arr, 0, arr.size() - 1);

    cout << "Reversed array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
