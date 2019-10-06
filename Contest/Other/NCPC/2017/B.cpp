#include<bits/stdc++.h>
using namespace std;

vector<int> G[1004];
int d1[1004],d2[1004];

void dfs(int now,int pa,int *d){
    for(int i:G[now]){
        if(i==pa)continue;
        d[i]=d[now]+1;
        dfs(i,now,d);
    }
}

int main(){
    int n; while(cin>>n,n){
        memset(d1,0,sizeof(d1));
        memset(d2,0,sizeof(d2));
        for(int i=1;i<=n;++i)G[i].clear();
        for(int i=1;i<=n;++i){
            int p; cin>>p;
            if(p){
                G[i].push_back(p);
                G[p].push_back(i);
            }
        }
        dfs(1,1,d1);
        int x=max_element(d1,d1+1+n)-d1;
        memset(d1,0,sizeof(d1));
        dfs(x,x,d1);
        int y=max_element(d1,d1+1+n)-d1;
        memset(d1,0,sizeof(d1));
        dfs(x,x,d1);
        dfs(y,y,d2);
        int mn=1e9;
        for(int i=1;i<=n;++i)mn=min(mn,max(d1[i],d2[i]));
        vector<int> ans;
        for(int i=1;i<=n;++i)if(max(d1[i],d2[i])==mn)ans.push_back(i);
        for(int i:ans)cout<<i<<" \n"[i==ans.back()];
    }
}
