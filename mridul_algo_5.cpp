//  0/1 knapsack


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, W;
    cin >> N >> W;

    vector<int> stuffiness(N);
    vector<long long> yumminess(N);

    for (int i = 0; i < N; i++) {
        cin >> yumminess[i] >> stuffiness[i];
    }

    vector<long long> dp(W + 1, 0);

    for (int i = 0; i < N; i++) {
        for (int w = W; w >= stuffiness[i]; w--) {
            dp[w] = max(dp[w], dp[w - stuffiness[i]] + yumminess[i]);
        }
    }

    cout << dp[W] << "\n";

    return 0;
}
