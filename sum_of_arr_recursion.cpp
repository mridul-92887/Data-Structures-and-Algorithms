#include <bits/stdc++.h>
using namespace std;

int sumArray(vector<int>& arr, int n) {
    if (n == 0) {
        return 0;
    } 
    else {
        int result = arr[n - 1] + sumArray(arr, n - 1);
        return result;
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int total = sumArray(arr, arr.size());
    cout << "Sum of array elements is " << total << endl;
    return 0;
}
