// Longest common subsequence 
//sodo length ta print korbe 

#include <bits/stdc++.h>
using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the dp table
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "Length of LCS: " << dp[n][m] << endl;

    return 0;
}

// sub sequence soho print korte caile ai code 
#include <bits/stdc++.h>
using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the dp table
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct the LCS string
    int i = n, j = m;
    string lcs = "";

    while(i > 0 && j > 0) {
        if(str1[i - 1] == str2[j - 1]) {
            lcs += str1[i - 1];
            i--;
            j--;
        } else if(dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    cout << "Length of LCS: " << dp[n][m] << endl;
    cout << "LCS: " << lcs << endl;

    return 0;
}
