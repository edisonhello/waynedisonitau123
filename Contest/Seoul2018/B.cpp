#include<bits/stdc++.h>
using namespace std;

int good[505][505],t[505],deg[505];
vector<pair<int,int>> G[505],iG[505];
vector<int> tp;
bitset<505> notok,v;
int bel[505];

void dfs1(int now,int up){
    v[now]=1;
    for(auto &p:G[now]){
        if(p.second<up)continue;
        if(v[p.first])continue;
        dfs1(p.first,up);
    }
    tp.push_back(now);
}
void dfs2(int now,int cc,int up){
    v[now]=1;
    bel[now]=cc;
    for(auto &p:iG[now]){
        if(p.second<up)continue;
        if(v[p.first])continue;
        dfs2(p.first,cc,up);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    while(m--){
        for(int i=1;i<=n;++i)cin>>t[i];
        for(int i=1;i<=n;++i)if(t[i]==0)t[i]=1e9;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(t[i]<t[j])++good[i][j];
            }
        }
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
        if(good[i][j]>good[j][i]){
            G[i].emplace_back(j,good[i][j]);
            iG[j].emplace_back(i,good[i][j]);
        }
    }
    auto doit=[&](const int up){
        tp.clear(); v.reset();
        for(int i=1;i<=n;++i){
            if(v[i])continue;
            dfs1(i,up);
        }
        reverse(tp.begin(),tp.end());
        int cc=0; v.reset();
        for(int i:tp){
            if(v[i])continue;
            ++cc;
            dfs2(i,cc,up);
        }
        memset(deg,0,sizeof(deg));
        for(int i=1;i<=n;++i){
            for(auto &p:G[i]){
                if(p.second<up)continue;
                if(bel[i]==bel[p.first])continue;
                ++deg[bel[p.first]];
            }
        }
        for(int i=1;i<=n;++i){
            if(deg[bel[i]])notok[i]=1;
        }
    };
    for(int i=0;i<=500;++i){
        doit(i);
    }
    for(int i=1;i<=n;++i){
        if(!notok[i])cout<<i<<" ";
    }
    cout<<endl;
}
