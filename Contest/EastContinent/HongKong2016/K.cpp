#include<bits/stdc++.h>
using namespace std;

vector<int> hero[300005];
vector<int> bel[300005];
vector<int> G[300005];
int pa[300005];
vector<int> use[300005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m,p; cin>>n>>m>>p;
    for(int i=1;i<=m;++i){
        int c; cin>>c; hero[i].resize(c);
        for(int &j:hero[i]){
            cin>>j;
            bel[j].push_back(i);
        }
    }
    for(int i=1;i<=p;++i){
        int t; cin>>t; use[t].push_back(i);
    }
    auto cmp=[&](const int &a,const int &b){ return make_pair(hero[a].size(),a)<make_pair(hero[b].size(),b); };
    for(int i=1;i<=n;++i)sort(bel[i].begin(),bel[i].end(),cmp);
    auto cmp2=[&](const int &a,const int &b){ return make_pair(use[a].size(),a)<make_pair(use[b].size(),b); };
    set<int,decltype(cmp2)> root(cmp2);
    int iroot=0;
    for(int i=1;i<=m;++i){
        int sk=hero[i][0];
        auto it=upper_bound(bel[sk].begin(),bel[sk].end(),i,cmp);
        if(it==bel[sk].end())root.insert(i),iroot+=hero[i].size();
        else pa[i]=*it;
    }
    for(int i=1;i<=m;++i){
        if(pa[i])G[pa[i]].push_back(i);
    }

    auto godown=[&](){
        while(root.size() && use[*root.begin()].empty()){
            int x=*root.begin(); root.erase(*root.begin());
            iroot-=hero[x].size();
            for(int i:G[x])root.insert(i),iroot+=hero[i].size();
        }
        /* vector<int> plug;
        for(int i:root)if(use[i].empty())plug.push_back(i);
        for(int i:plug)root.erase(i),iroot-=hero[i].size();
        for(int x:plug)for(int i:G[x])root.insert(i),iroot+=hero[i].size(); */
    };

    vector<vector<int>> ans;
    while(iroot==n){
        godown();
        if(iroot!=n)break;
        vector<int> now;
        for(int i:root){
            now.push_back(use[i].back());
            use[i].pop_back();
        }
        ans.push_back(now);
    }

    cout<<ans.size()<<endl;
    for(auto &v:ans){
        cout<<v.size();
        for(int i:v)cout<<" "<<i;
        cout<<'\n';
    }

}
