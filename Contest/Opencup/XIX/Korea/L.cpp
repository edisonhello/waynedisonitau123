#include<bits/stdc++.h>
using namespace std;

int n,a[100005],ge[100005],ls[100005];
pair<int,int> ans[100005];

void pre(int mr){
    int now=1;
    int gr=0,bad=0;
    while(now<=n){
        int len=max(ge[now],ls[now])+1;
        if(len<=mr){
            ++gr;
            if(now+mr-1<=n){
                bad+=mr-len;
                now+=mr;
            }
            else{
                int mmr=n-now+1;
                bad+=mmr-len;
                now+=mmr;
            }
        }
        else{
            ++gr;
            now+=len;
        }
    }
    ans[mr]=make_pair(gr,bad);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n; 
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=n-1;i>=1;--i){
        if(a[i]<=a[i+1]){
            ge[i]=ge[i+1]+1;
        }
        else{
            ls[i]=ls[i+1]+1;
        }
    }
    for(int i=2;i<=n;++i)pre(i);
    int q; cin>>q; while(q--){
        int x; cin>>x;
        cout<<ans[x].first<<" "<<ans[x].second<<'\n';
    }
}
