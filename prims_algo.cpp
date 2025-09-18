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
        adj[v].push_back({u,w});
    }
    vector<int> key(n+1, INT_MAX);
    vector<bool> inMST(n+1,false);
    key[1]=0;
    int cost=0;
    for(int i=1;i<=n;i++){
        int u=-1;
        for(int j=1;j<=n;j++){
            if(!inMST[j] && (u==-1 || key[j]<key[u])) u=j;
        }
        inMST[u]=true;
        cost+=key[u];
        for(auto p: adj[u]){
            int v=p.first, w=p.second;
            if(!inMST[v] && w<key[v]) key[v]=w;
        }
    }
    cout<<cost;
    return 0;
}
