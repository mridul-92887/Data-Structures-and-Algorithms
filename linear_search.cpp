#include <bits/stdc++.h>
using namespace std;

int linearSearch(vector<int>& arr, int x) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> arr = {5, 8, 12, 20, 25, 30};
    int x = 20;

    int res = linearSearch(arr, x);

    if (res == -1) {
        cout << "Element is not present in the array";
    } else {
        cout << "Element is present at index " << res;
    }

    return 0;
}
