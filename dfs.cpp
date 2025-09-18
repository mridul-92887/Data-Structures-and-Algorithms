#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool>& visited){
    visited[node]=true;
    cout<<node<<" ";
    for(int neighbor: adj[node]){
        if(!visited[neighbor]){
            dfs(neighbor, adj, visited);
        }
    }
}

int main() {
    int n,e;
    cin>>n>>e;
    vector<int> adj[n+1];
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> visited(n+1,false);
    int start;
    cin>>start;
    dfs(start, adj, visited);
    return 0;
}
