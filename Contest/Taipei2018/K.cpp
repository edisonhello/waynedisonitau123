#include<bits/stdc++.h>
using namespace std;

char c[204];
int d[204][204];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n,m; cin>>n>>m;
        for(int i=1;i<=n;++i)cin>>c[i];
        memset(d,0x3f,sizeof(d));
        for(int i=1;i<=n;++i)d[i][i]=0;
        while(m--){
            int u,v; cin>>u>>v;
            if(c[u]!=c[v])d[u][v]=d[v][u]=1;
            else d[v][u]=d[u][v]=0;
        }
        for(int k=1;k<=n;++k)for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        int mn=9999999;
        for(int i=1;i<=n;++i){
            int mx=0;
            for(int j=1;j<=n;++j)mx=max(mx,d[i][j]);
            mn=min(mn,mx);
        }
        cout<<mn<<endl;
    }
}
