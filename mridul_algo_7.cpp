#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> adj, revAdj;
vector<vector<int>> sccList; // SCC এর node গুলো এখানে রাখব

void dfs1(int u, vector<bool> &visited, stack<int> &st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v, visited, st);
    }
    st.push(u);
}

void dfs2(int u, vector<bool> &visited, vector<int> &currentSCC) {
    visited[u] = true;
    currentSCC.push_back(u);
    for (int v : revAdj[u]) {
        if (!visited[v]) dfs2(v, visited, currentSCC);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    adj.assign(N + 1, vector<int>());
    revAdj.assign(N + 1, vector<int>());

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    vector<bool> visited(N + 1, false);
    stack<int> st;

    // Step 1: DFS on original graph
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) dfs1(i, visited, st);
    }

    // Step 2: DFS on reversed graph to find SCCs
    fill(visited.begin(), visited.end(), false);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            vector<int> currentSCC;
            dfs2(u, visited, currentSCC);
            sccList.push_back(currentSCC);
        }
    }

    // এখন cycle থাকা SCC এর সংখ্যা বের করবো
    int cycleCount = 0;
    for (auto &comp : sccList) {
        if ((int)comp.size() > 1) {
            // size ২ বা তার বেশি → cycle আছে
            cycleCount++;
        } else {
            // size == 1 হলে self loop আছে কিনা চেক করো
            int node = comp[0];
            for (int x : adj[node]) {
                if (x == node) {
                    cycleCount++;
                    break;
                }
            }
        }
    }

    cout << cycleCount << "\n";

    return 0;
}
