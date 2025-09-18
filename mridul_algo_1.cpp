// edge r man dawa thakle kaj korbe nh 
// N>10^5 or N=10^5 amon hole kaj korbe nh 
// negative adge hole kaj korbe nh  




#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int N, S, D;
    cin >> N >> S >> D;
    S--;  // 1-based থেকে 0-based index-এ রূপান্তর
    D--;

    // Adjacency matrix ইনপুট নেওয়া
    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    // BFS চালানোর জন্য দরকার visited এবং parent array
    vector<bool> visited(N, false);
    vector<int> parent(N, -1);

    queue<int> q;
    visited[S] = true;
    q.push(S);

    // BFS দিয়ে পথ খোঁজা
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next = 0; next < N; next++) {
            if (graph[current][next] == 1 && !visited[next]) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }
        }
    }

    // যদি গন্তব্য D-তে পৌঁছানো না যায়
    if (!visited[D]) {
        cout << -1 << endl;
        return 0;
    }

    // পথ তৈরি করা (reverse করে)
    vector<int> path;
    int node = D;
    while (node != -1) {
        path.push_back(node + 1); // আবার 1-based করে নিই
        node = parent[node];
    }
    reverse(path.begin(), path.end());

    // আউটপুট
    cout << path.size() << endl;
    for (int loc : path) {
        cout << loc << " ";
    }
    cout << endl;

    return 0;
}
