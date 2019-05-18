#include<bits/stdc++.h>
using namespace std;

vector<int> t[100005];
int w[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,k; cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>w[i];
    for(int i=1;i<=n;++i){
        int z; cin>>z;
        t[w[i]].push_back(z);
    }
    long long ans=0;
    vector<int> mo;
    int no=0;
    for(int i=1;i<=k;++i){
        sort(t[i].begin(),t[i].end(),greater<int>());
        while(t[i].size()>1u){
            mo.push_back(t[i].back());
            t[i].pop_back();
        }
        if(t[i].empty())++no;
    }
    sort(mo.begin(),mo.end(),greater<int>());
    while(no){
        --no;
        ans+=mo.back();
        mo.pop_back();
    }
    cout<<ans<<endl;
}
