#include<bits/stdc++.h>
using namespace std;

int deg[100005];
set<pair<int,int>> edg;
set<int> G[100005];
set<int> wdeg[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    while(m--){
        int u,v; cin>>u>>v;
        edg.insert(minmax(u,v));
        G[u].insert(v);
        G[v].insert(u);
    }
    for(int i=1;i<=n;++i)wdeg[G[i].size()].insert(i);
    while(wdeg[2].size()){
        int bye=*wdeg[2].begin();
        wdeg[2].erase(bye);
        int to1=*G[bye].begin();
        int to2=*next(G[bye].begin());
        if(edg.count(minmax(to1,to2))){
            wdeg[G[to1].size()].erase(to1);
            wdeg[G[to2].size()].erase(to2);
            G[to1].erase(bye);
            G[to2].erase(bye);
            wdeg[G[to1].size()].insert(to1);
            wdeg[G[to2].size()].insert(to2);
            edg.erase(minmax(to1,bye));
            edg.erase(minmax(to2,bye));
        }
        else{
            G[to1].erase(bye);
            G[to2].erase(bye);
            G[to1].insert(to2);
            G[to2].insert(to1);
            edg.erase(minmax(to1,bye));
            edg.erase(minmax(to2,bye));
            edg.insert(minmax(to1,to2));
        }
    }
    if([&](){
        if(wdeg[1].size()!=2u)return 0;
        for(int i=2;i<=n;++i)if(wdeg[i].size())return 0;
        return 1;
    }()){
        cout<<"Yes"<<endl;
    }
    else cout<<"No"<<endl;
}
