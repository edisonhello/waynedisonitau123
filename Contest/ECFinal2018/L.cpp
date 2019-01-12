#include<bits/stdc++.h>
using namespace std;

int ty[100005],c0,c1,e01,e10,ab0,ab1;
vector<int> G[100005];
int ans[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>ty[i];
    for(int i=1;i<=n;++i)++(ty[i]?c1:c0);
    while(m--){
        int u,v; cin>>u>>v;
        if(ty[u]==ty[v])continue;
        G[u].push_back(v);
        G[v].push_back(u);
        if(ty[u]==0)++e01;
        else ++e10;
    }
    for(int i=1;i<=n;++i)if(G[i].size())++(ty[i]?ab1:ab0);
    for(int i=1;i<=n;++i){
        int ans=0;
        if(G[i].size()){ // can go op
            if(ty[i]==0)ans=c0-1;
            else ans=c1-1;
            ans+=G[i].size();
            if(ty[i]==0)ans+=2*(c1-G[i].size());
            else ans+=2*(c0-G[i].size());
        }
        else{
            if(ty[i]==0)ans=c0-1;
            else ans=c1-1;
            if(ty[i]==0)ans+=2*ab1+3*(c1-ab1);
            else ans+=2*ab0+3*(c0-ab0);
        }
        cout<<ans<<' ';
    }
    cout<<endl;
}
