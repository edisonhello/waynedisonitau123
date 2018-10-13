#include<bits/stdc++.h>
using namespace std;

pair<int,int> pt[20];
int ans,n;
vector<pair<int,int>> li;
bitset<20> u;

void dfs(int now){
    if(now>=n){
        int aa=0;
        for(int i=0;i<int(li.size());++i){
            for(int j=i+1;j<int(li.size());++j){
                if(li[i].first*li[j].second==li[i].second*li[j].first)++aa;
            }
        }
        ans=max(ans,aa);
        return;
    }
    if(u[now]){ dfs(now+1); return; }
    u[now]=1;
    for(int i=now+1;i<n;++i){
        if(u[i])continue;
        li.emplace_back(pt[i].first-pt[now].first,pt[i].second-pt[now].second);
        u[i]=1;
        dfs(now+1);
        u[i]=0;
        li.pop_back();
    }
    u[now]=0;
}


int main(){
    cin>>n;
    for(int i=0;i<n;++i)cin>>pt[i].first>>pt[i].second;
    dfs(0);
    cout<<ans<<endl;
}
