#include <bits/stdc++.h>
using namespace std;

int minCoinsRecur(int i, int sum, vector<int> &coins) {
    if (sum == 0) {
        return 0;
    }
    if (sum < 0 || i == coins.size()) {
        return INT_MAX;
    }

    int take = INT_MAX;
    if (coins[i] > 0) {
        take = minCoinsRecur(i, sum - coins[i], coins);
        if (take != INT_MAX) {
            take = take + 1;
        }
    }

    int noTake = minCoinsRecur(i + 1, sum, coins);

    return min(take, noTake);
}

int minCoins(vector<int> &coins, int sum) {
    int res = minCoinsRecur(0, sum, coins);
    if (res != INT_MAX) {
        return res;
    } 
    else {
        return -1;
    }
}

int main() {
    int n, sum;
    cout << "Enter number of coin types: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter the coin values: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    cout << "Enter the total sum: ";
    cin >> sum;

    int result = minCoins(coins, sum);
    if (result == -1) {
        cout << "It is not possible to form the sum with given coins" << endl;
    } 
    else {
        cout << "Minimum number of coins required = " << result << endl;
    }

    return 0;
}
