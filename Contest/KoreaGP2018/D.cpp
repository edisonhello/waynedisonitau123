#include<bits/stdc++.h>
using namespace std;

pair<int,int> seg[300005];
vector<int> G[300005],iG[300005],tp;
int n,m,ind[300005],ans[300005],line[300005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>seg[i].first>>seg[i].second;
    while(m--){
        int u,v; cin>>u>>v;
        G[u].push_back(v);
        iG[v].push_back(u);
    }
    if([&](){
        queue<int> q;
        for(int i=1;i<=n;++i)for(int j:G[i])++ind[j];
        for(int i=1;i<=n;++i)if(ind[i]==0)q.push(i);
        while(q.size()){
            int now=q.front(); q.pop();
            tp.push_back(now);
            for(int i:G[now]){
                --ind[i];
                if(ind[i]==0)q.push(i);
            }
        }
        return int(tp.size())!=n;
    }())exit((cout<<-1<<endl,0));
    reverse(tp.begin(),tp.end());
    for(int i:tp){
        for(int j:iG[i]){
            seg[j].second=min(seg[j].second,seg[i].second);
        }
    }
    // auto cmp=[&](const int &a,const int &b){ return seg[a].second==seg[b].second ? seg[a].first>seg[b].first : seg[a].second>seg[b].second; };
    auto cmpr=[&](const int &a,const int &b){ return seg[a].second>seg[b].second; };
    auto cmpl=[&](const int &a,const int &b){ return seg[a].first>seg[b].first; };
    priority_queue<int,vector<int>,decltype(cmpr)> pqr(cmpr);
    priority_queue<int,vector<int>,decltype(cmpl)> pql(cmpl);
    memset(ind,0,sizeof(ind));
    for(int i=1;i<=n;++i)for(int j:G[i])++ind[j];
    for(int i=1;i<=n;++i)if(ind[i]==0)pql.push(i);
    int idx=1;
    while(pql.size() && seg[pql.top()].first<=idx)pqr.push(pql.top()),pql.pop();
    while(pqr.size()){
        int now=pqr.top(); pqr.pop();
        ans[now]=idx;
        line[idx]=now;
        ++idx;
        for(int i:G[now]){
            --ind[i];
            if(ind[i]==0)pql.push(i);
        }
        while(pql.size() && seg[pql.top()].first<=idx)pqr.push(pql.top()),pql.pop();
    }
    for(int i=1;i<=n;++i)if(!ans[i] || !line[i])exit((cout<<-1<<endl,0));
    for(int i=1;i<=n;++i)if(!(seg[i].first<=ans[i] && ans[i]<=seg[i].second))exit((cout<<-1<<endl,0));
    for(int i=1;i<=n;++i)cout<<line[i]<<'\n';
}
