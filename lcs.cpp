//Longest Common Subsequence (LCS)____ dp
#include <bits/stdc++.h>
using namespace std;

int LCS(string X, string Y) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    int lcsLength = LCS(X, Y);
    cout << "Length of LCS = " << lcsLength << endl;
    return 0;
}


//Using______A R R A Y 

#include <bits/stdc++.h>
using namespace std;

int LCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    
    int dp[20][20];  // 2D array for storing LCS lengths

    // Initialize first row and first column to 0
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // Fill dp array
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } 
            else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } 
                else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }

    return dp[m][n];
}

int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";

    int lcsLength = LCS(X, Y);

    cout << "Length of LCS = " << lcsLength << endl;

    return 0;
}
