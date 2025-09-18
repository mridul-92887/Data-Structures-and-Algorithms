#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    vector<tuple<int,int,int>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    int src;
    cin>>src;
    vector<int> dist(n+1, INT_MAX);
    dist[src]=0;
    for(int i=1;i<=n-1;i++){
        for(auto e: edges){
            int u,v,w;
            tie(u,v,w) = e;
            if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dist[i]==INT_MAX) cout<<"INF ";
        else cout<<dist[i]<<" ";
    }
    return 0;
}
