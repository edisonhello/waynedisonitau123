#include<bits/stdc++.h>
using namespace std;

int cnt[1000006],ans[1000006];
bitset<1000006> hasfa;

int main(){
    freopen("equal.in","r",stdin);
    freopen("equal.out","w",stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        int t; cin>>t; ++cnt[t];
    }
    int k=0;
    for(int i=1;i<=1000000;++i)if(cnt[i])++k;
    for(int i=0;i<=n;++i)ans[i]=k;
    int nohasfamin=1e9,mcf=-1;
    for(int i=1;i<=1000000;++i){
        if(!cnt[i])continue;
        for(int j=i*2;j<=1000000;j+=i){
            if(cnt[j]){
                hasfa[i]=1;
                break;
            }
        }
        if(!hasfa[i]){
            nohasfamin=min(nohasfamin,cnt[i]);
            if(cnt[i]==nohasfamin)mcf=i;
        }
    }
    queue<int> q;
    int now=nohasfamin;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=1;i<=1000000;++i)if(cnt[i]){
        if(i==mcf)continue;
        pq.push(cnt[i]);
    }
    while(pq.size()){
        now+=pq.top();
        pq.pop();
        q.push(now);
    }
    q.push(n+1);
    int nowa=k;
    while(q.size()){
        int now=q.front(); q.pop();
        if(q.empty())break;
        --nowa;
        for(int i=now;i<min(n+1,q.front());++i)ans[i]=min(ans[i],nowa);
    }
    for(int i=1;i<=1000000;++i)if(cnt[i] && hasfa[i])pq.push(cnt[i]);
    now=0;
    while(pq.size()){
        now+=pq.top();
        pq.pop();
        q.push(now);
    }
    q.push(n+1);
    nowa=k;
    while(q.size()){
        int now=q.front(); q.pop();
        if(q.empty())break;
        --nowa;
        for(int i=now;i<min(n+1,q.front());++i)ans[i]=min(ans[i],nowa);
    }
    for(int i=0;i<=n;++i)cout<<ans[i]<<" "; cout<<endl;
}
