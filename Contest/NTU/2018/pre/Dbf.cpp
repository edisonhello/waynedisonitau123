#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> G[100005];

long long dfs(int now,int pa,int la){
    long long rt=0;
    for(auto i:G[now]){
        if(i.first==pa)continue;
        rt=max(rt,dfs(i.first,now,i.second)+(pa==-1?0ll:1ll*(i.second-la)*(i.second-la)));
    }
    return rt;
}

int main(){
    int n; cin>>n;
    for(int i=1;i<n;++i){
        int u,v,w; cin>>u>>v>>w;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }
    for(int i=1;i<=n;++i){
        cout<<dfs(i,-1,0)<<endl;
    }
}
