#include<bits/stdc++.h>
using namespace std;

void go(long long n){
    vector<pair<int,int>> mem(150,make_pair(-1,-1));
    mem[2]=make_pair(0,0);
    unordered_map<long long,int> pos;
    pos[1]=1;
    pos[2]=2;
    int ptr=3;
    function<int(long long)> dfs=[&](long long n)->int {
        auto it=pos.find(n);
        if(it!=pos.end())return it->second;
        long long rn=n/2;
        long long ln=n-rn;
        int lc=dfs(ln);
        int rc=dfs(rn);
        mem[ptr]=make_pair(lc-1,rc-1);
        pos[n]=ptr;
        return ptr++;
    };
    int idx=dfs(n);
    cout<<idx<<'\n';
    for(int i=1;i<=idx;++i)cout<<mem[i].first<<" "<<mem[i].second<<'\n';
    cout<<idx-1<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        long long n; cin>>n;
        go(n);
    }
}
