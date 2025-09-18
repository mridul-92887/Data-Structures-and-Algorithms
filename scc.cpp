//  SCC (Strongly Connected Components)
#include <bits/stdc++.h>
using namespace std;

void dfs1(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st){
    visited[node]=true;
    for(int neighbor: adj[node]){
        if(!visited[neighbor]){
            dfs1(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

void dfs2(int node, vector<vector<int>>& transpose, vector<bool>& visited){
    visited[node]=true;
    cout<<node<<" ";
    for(int neighbor: transpose[node]){
        if(!visited[neighbor]){
            dfs2(neighbor, transpose, visited);
        }
    }
}

int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v); // directed graph
    }

    stack<int> st;
    vector<bool> visited(n+1,false);
    
    // Step 1: normal DFS to fill stack
    for(int i=1;i<=n;i++){
        if(!visited[i]) dfs1(i, adj, visited, st);
    }

    // Step 2: transpose graph
    vector<vector<int>> transpose(n+1);
    for(int i=1;i<=n;i++){
        for(int neighbor: adj[i]){
            transpose[neighbor].push_back(i);
        }
    }

    // Step 3: DFS on transpose graph
    fill(visited.begin(), visited.end(), false);
    int scc_count=0;
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(!visited[node]){
            dfs2(node, transpose, visited);
            cout<<endl; // ekta SCC er nodes print korar jonno
            scc_count++;
        }
    }

    cout<<"Total SCC: "<<scc_count<<endl;
    return 0;
}
