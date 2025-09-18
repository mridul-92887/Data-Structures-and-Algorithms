#include <bits/stdc++.h>
using namespace std;

int findMinIndex(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    int minIndex = -1;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (arr[mid1] == arr[mid2]) {
            low = mid1 + 1;
            high = mid2 - 1;
            minIndex = mid1;
        }
        else if (arr[mid1] < arr[mid2]) {
            high = mid2 - 1;
            minIndex = mid1;
        }
        else {
            low = mid1 + 1;
            minIndex = mid2;
        }
    }

    return minIndex;
}

int main() {
    vector<int> arr = {9, 7, 1, 2, 3, 6, 10};

    int idx = findMinIndex(arr);
    cout << "Index of minimum element: " << idx << endl;

    return 0;
}
