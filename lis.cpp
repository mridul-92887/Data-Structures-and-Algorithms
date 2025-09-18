//Longest Increasing Subsequence (LIS)___________
#include <bits/stdc++.h>
using namespace std;

int LIS(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

int main() {
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60};
    int lisLength = LIS(arr);
    cout << "Length of Longest Increasing Subsequence = " << lisLength << endl;
    return 0;
}

//Using A R R A Y_______________

#include <bits/stdc++.h>
using namespace std;

int LIS(int arr[], int n) {
    int dp[100]; 
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int maxLIS = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > maxLIS) {
            maxLIS = dp[i];
        }
    }

    return maxLIS;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[100];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int lisLength = LIS(arr, n);
    cout << "Length of Longest Increasing Subsequence = " << lisLength << endl;

    return 0;
}
