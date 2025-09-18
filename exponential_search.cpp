#include <bits/stdc++.h>
using namespace std;

int exponential_search(vector<int> arr, int x) {
    int n = arr.size();

    if (n == 0) {
        return -1;
    }

    // Find range for binary search by repeatedly doubling i
    int i = 1;
    while (i < n && arr[i] < x) {
        i = i * 2;
    }

    // Perform binary search on the range [i/2, min(i, n-1)]
    int left = i / 2;
    int right = min(i, n - 1);

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == x) {
            return mid;
        } 
        else if (arr[mid] < x) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40};
    int n = arr.size();
    int x = 10;

    int result = exponential_search(arr, x);

    if (result == -1) {
        cout << "Element not found in the array";
    } 
    else {
        cout << "Element is present at index " << result << endl;
    }

    return 0;
}
