// )(nlongn) time r LIS code
// Longest increasing subsequence


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> lis; // এখানে increasing subsequence রাখবো

    for (int i = 0; i < n; i++) {
        int x = arr[i];

        // x এর জায়গা খুঁজে বের করো (lower_bound = first element >= x)
        auto it = lower_bound(lis.begin(), lis.end(), x);

        if (it == lis.end()) {
            lis.push_back(x); // নতুন বড় element পেলাম
        } else {
            *it = x; // পুরাতন element এর জায়গায় নতুন ছোট x বসালাম
        }
    }

    cout << lis.size() << endl;

    return 0;
}
