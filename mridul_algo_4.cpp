// Find the number of SCC (strongly connected compunents)
// input 
// 6 7
// 1 2
// 2 3
// 3 1
// 1 4
// 4 5
// 5 6
// 6 4
// output 
// 2

#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> adj, revAdj;

void dfs1(int u, vector<bool> &visited, stack<int> &st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v, visited, st);
    }
    st.push(u);
}

void dfs2(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v : revAdj[u]) {
        if (!visited[v]) dfs2(v, visited);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    adj.assign(N + 1, vector<int>());
    revAdj.assign(N + 1, vector<int>());

    for (int i = 0; i < M; i++) {
        int v, u; 
        cin >> v >> u;
        // edge from u to v (one-way channel)
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    vector<bool> visited(N + 1, false);
    stack<int> st;

    // Step 1: DFS on original graph to fill stack by finish time
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) dfs1(i, visited, st);
    }

    // Step 2: DFS on reversed graph in stack order to find SCCs
    fill(visited.begin(), visited.end(), false);
    int sccCount = 0;

    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!visited[u]) {
            dfs2(u, visited);
            sccCount++;
        }
    }

    cout << sccCount << "\n";

    return 0;
}
