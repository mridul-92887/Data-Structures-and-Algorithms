#include <iostream>
#include <vector>
using namespace std;

// Apna C L G 
void merge(vector<int>& array, int s, int mid, int e) {
    int i = s;
    int j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= e) {
        if (array[i] <= array[j]) {
            temp.push_back(array[i]);
            i++;
        } else {
            temp.push_back(array[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(array[i]);
        i++;
    }

    while (j <= e) {
        temp.push_back(array[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        array[k + s] = temp[k];
    }
}

void mergeSort(vector<int>& array, int s, int e) {
    if (s < e) {
        int mid = s + (e - s) / 2;
        mergeSort(array, s, mid);
        mergeSort(array, mid + 1, e);
        merge(array, s, mid, e);
    }
}

// A R R A Y
void marge(int array[],int left,int mid,int right ){
    int n1=mid-left+1;
    int n2=right-mid;
    int leftArray[n1];
    int rightArray[n2];
    for(int i=0;i<n1;i++){
        leftArray[i]=array[left+i];
    }
    for(int i=0;i<n2;i++){
        rightArray[i]=array[mid+1+i];
    }
    int i=0,j=0;
    int k=left;
    while(i<n1&&j<n2){
        if(leftArray[i]<=rightArray[j]){
            array[k]=leftArray[i];
            i++;
            k++;
        }else{
            array[k]=rightArray[j];
            j++;
            k++;
        }
    }
    while(i<n1){
        array[k]=leftArray[i];
            i++;
            k++;
    }
    while(j<n2){
        array[k]=rightArray[j];
            j++;
            k++;
    }
}


//V E C T O R
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArray;
    vector<int> rightArray;

    for(int i = left; i <= mid; i++) {
        leftArray.push_back(arr[i]);
    }

    for(int i = mid + 1; i <= right; i++) {
        rightArray.push_back(arr[i]);
    }

    int i = 0, j = 0, k = left;

    while(i < leftArray.size() && j < rightArray.size()) {
        if(leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while(i < leftArray.size()) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while(j < rightArray.size()) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergesort(vector<int>& arr, int left, int right) {
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


void printArray(const vector<int>& array) {
    for (int value : array) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Array size must be greater than 0.\n";
        return 0;
    }

    vector<int> array(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    cout << "Original array: ";
    printArray(array);

    mergeSort(array, 0, array.size() - 1);

    cout << "Sorted array: ";
    printArray(array);

    return 0;
}
