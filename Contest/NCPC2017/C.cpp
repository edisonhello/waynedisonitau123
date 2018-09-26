#include<bits/stdc++.h>
using namespace std;

vector<int> G[1004];
vector<int> ans[1004];
bitset<1004> v;
stack<int> st;
int start;

void dfs(int now){
    // cout<<"start: "<<start<<" , now: "<<now<<endl;
    v[now]=1;
    st.push(now);
    for(int i:G[now]){
        if(v[0])continue;
        if(v[i]){
            vector<int> tans;
            while(st.top()!=i){
                tans.push_back(st.top());
                st.pop();
            }
            tans.push_back(i);
            v[0]=1;
            ans[start]=tans;
            break;
        }
        dfs(i);
    }
    if(st.size())st.pop();
}

vector<pair<int,int>> e;
vector<int> num;
map<int,int> mp,imp;

int main(){
    int n; cin>>n;
    for(int i=0;i<n;++i){
        int u,v; cin>>u>>v;
        e.emplace_back(u,v);
        num.push_back(u);
        num.push_back(v);
    }
    sort(num.begin(),num.end());
    num.resize(unique(num.begin(),num.end())-num.begin());
    for(int i=0;i<int(num.size());++i){
        mp[num[i]]=i+1;
        imp[i+1]=num[i];
    }
    for(auto &p:e){
        p.first=mp[p.first];
        p.second=mp[p.second];
        G[p.first].push_back(p.second);
    }
    for(int i=1;i<=n;++i){
        v.reset();
        while(st.size())st.pop();
        start=i;
        dfs(i);
        reverse(ans[i].begin(),ans[i].end());
    }
    int m; cin>>m; while(m--){
        int t; cin>>t; t=mp[t];
        for(int i:ans[t])cout<<imp[i]<<" \n"[i==ans[t].back()];
    }
}

