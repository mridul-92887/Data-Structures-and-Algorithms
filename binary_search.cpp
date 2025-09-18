#include <iostream>
using namespace std;

int binarySearch(int array[], int n, int target) {
    int start = 0;
    int end = n - 1;

    while(start <= end) {
        int mid = start + (end - start) / 2;

        if(array[mid] == target) {
            return mid;
        }
        else if(array[mid] < target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }

    return -1;
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(array) / sizeof(array[0]);
    int target = 40;

    int index = binarySearch(array, n, target);

    if(index != -1) {
        cout << "Element found at index: " << index << endl;
    }
    else {
        cout << "Element not found" << endl;
    }

    return 0;
}

// int binarySearch(vector<int>& v, int target) {
//     int start = 0;
//     int end = v.size() - 1;

//     while(start <= end) {
//         int mid = start + (end - start) / 2;

//         if(v[mid] == target) {
//             return mid;
//         }
//         else if(v[mid] < target) {
//             start = mid + 1;
//         }
//         else {
//             end = mid - 1;
//         }
//     }

//     return -1;
// }
