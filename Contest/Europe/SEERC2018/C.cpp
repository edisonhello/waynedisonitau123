#include<bits/stdc++.h>
using namespace std;

vector<int> G[222];
int clr[222];

void add(int a,int b){
    G[a].push_back(b);
    G[b].push_back(a);
}

bitset<222> v;
int d[222];
int bfs(int s,int m){
    v.reset(); v[s]=1;
    queue<int> q; q.push(s);
    int cnt=clr[s];
    if (m == 1 && cnt == 1) return 0;
    memset(d,0,sizeof(d));
    while(q.size()){
        int now=q.front(); q.pop();
        for(int i:G[now]){
            if(v[i])continue;
            v[i]=1;
            q.push(i);
            d[i]=d[now]+1;
            if(clr[i])++cnt;
            if(cnt>=m)return d[i];
        }
    }
}

int main(){
    int n,m; cin>>n>>m;
    int nn=n;
    for(int i=1;i<=n;++i)cin>>clr[i];
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        ++nn;
        add(u,nn);
        add(v,nn);
    }
    int mn=1e9;
    for(int i=1;i<=nn;++i){
        mn=min(mn,bfs(i,m));
    }
    cout<<mn<<endl;
}
