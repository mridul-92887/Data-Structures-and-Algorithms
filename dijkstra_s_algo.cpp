#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> adj[n+1];
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w}); // undirected
    }
    int src;
    cin>>src;
    vector<int> dist(n+1, INT_MAX);
    dist[src]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        for(auto edge: adj[node]){
            int v = edge.first;
            int w = edge.second;
            if(dist[node]+w < dist[v]){
                dist[v] = dist[node]+w;
                pq.push({dist[v], v});
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dist[i]==INT_MAX) cout<<"INF ";
        else cout<<dist[i]<<" ";
    }
    return 0;
}
