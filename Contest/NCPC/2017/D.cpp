#include<bits/stdc++.h>
using namespace std;


set<int> G[100005];
int dt[100005];

void sol(){
    int n,p,f,m; cin>>n>>p>>f>>m;
    memset(dt,0,sizeof(dt));
    for(int i=1;i<=n;++i)G[i].clear();
    vector<int> ms(m);
    for(int &i:ms)cin>>i;
    for(int i=1;i<=n;++i){
        for(int m:ms){
            int j=m-i;
            if(j==i)continue;
            if(j<1 || j>n)continue;
            G[i].insert(j);
            // G[j].insert(i);
        }
    }
    queue<int> q;
    for(int i=1;i<=n;++i)if(int(G[i].size())<=f){
        q.push(i);
        dt[i]=1;
    }
    while(q.size()){
        int now=q.front(); q.pop();
        // cout<<"now: "<<now<<endl;
        for(int i:G[now]){
            G[i].erase(now);
            if(dt[i])continue;
            if(int(G[i].size())<=f){
                q.push(i);
                dt[i]=dt[now]+1;
            }
        }
        G[now].clear();
    }
    if(dt[p]==0)dt[p]=-1;
    cout<<dt[p]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--)sol();
}
