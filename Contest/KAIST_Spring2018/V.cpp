#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> G[250005];
long long d[250005],near[250005];
bitset<250005> v;
long long ans[250005];
int srs[250005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    while(m--){
        int u,v,w; cin>>u>>v>>w;
        w<<=1;
        G[u].emplace_back(v,w);
        if(u!=v)G[v].emplace_back(u,w);
    }
    int k; cin>>k;
    memset(d,0x3f,sizeof(d));
    priority_queue<tuple<long long,int,int>,vector<tuple<long long,int,int>>,greater<tuple<long long,int,int>>> pq;
    for(int i=1;i<=k;++i){
        cin>>srs[i];
        d[srs[i]]=0;
        near[srs[i]]=srs[i];
        pq.emplace(0,srs[i],srs[i]);
    }
    while(pq.size()){
        while(pq.size() && v[get<2>(pq.top())])pq.pop();
        if(pq.empty())break;
        int now=get<2>(pq.top()); pq.pop();
        v[now]=1;
        for(auto &e:G[now]){
            if(d[e.first]>d[now]+e.second || (d[e.first]==d[now]+e.second && near[e.first]>near[now])){
                d[e.first]=d[now]+e.second;
                near[e.first]=near[now];
                pq.emplace(d[e.first],near[e.first],e.first);
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(auto &e:G[i]){
            if(e.first>i)continue;
            int u=i,v=e.first,w=e.second;
            if(near[u]==near[v]){
                ans[near[u]]+=w;
            }
            else{
                assert(abs(d[u]-d[v])<=w);
                int diff=abs(d[u]-d[v]);
                if(d[u]<d[v])ans[near[u]]+=diff;
                else ans[near[v]]+=diff;
                int le=w-diff;
                ans[near[u]]+=le/2;
                ans[near[v]]+=le/2;
            }
        }
    }
    for(int i=1;i<=k;++i){
        long long o=ans[srs[i]];
        cout<<(o>>1)<<".";
        if(o&1)cout<<"5\n";
        else cout<<"0\n";
    }
}

