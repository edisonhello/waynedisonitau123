#include<bits/stdc++.h>
using namespace std;

set<pair<int,int>> st[1111];

bitset<505> g[505];
int deg[505];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // int n=500,m=0; 
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)g[i][j]=1;
    for(int i=1;i<=n;++i)g[i][i]=0;
    int es=0;
    while(m--){
        int u,v; cin>>u>>v;
        g[u][v]=g[v][u]=0;
        ++deg[u]; ++deg[v];
        ++es;
    }
    for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j){
        if(g[i][j])st[deg[i]+deg[j]].insert(make_pair(i,j));
    }
    for(int k=n*2;k>=0;--k){
        // cout<<"doing k: "<<k<<endl;
        while(st[k].size()){
            int u,v; tie(u,v)=*st[k].begin(); st[k].erase(st[k].begin());
            g[u][v]=g[v][u]=0;
            ++es; ++deg[u]; ++deg[v];
            // cout<<"connect new edge: "<<u<<" to "<<v<<endl;
            for(int x=g[u]._Find_first();x<=n;x=g[u]._Find_next(x)){
                int a=x, b=u;
                if(b<a)swap(a,b);
                int od=deg[a]+deg[b]-1;
                // cout<<"un connected edge "<<a<<" to "<<b<<" ori deg: "<<od<<endl;
                if(od>=k)continue;
                st[od].erase(make_pair(a,b));
                st[od+1].insert(make_pair(a,b));
            }
            for(int x=g[v]._Find_first();x<=n;x=g[v]._Find_next(x)){
                int a=x, b=v;
                if(b<a)swap(a,b);
                int od=deg[a]+deg[b]-1;
                // cout<<"un connected edge "<<a<<" to "<<b<<" ori deg: "<<od<<endl;
                if(od>=k)continue;
                st[od].erase(make_pair(a,b));
                st[od+1].insert(make_pair(a,b));
            }
        }
        // cout<<"es: "<<es<<endl;
        if(es==n*(n-1)/2){
            cout<<k<<endl;
            exit(0);
        }
    }
}
