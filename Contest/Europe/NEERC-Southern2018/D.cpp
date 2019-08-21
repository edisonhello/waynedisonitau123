#include<bits/stdc++.h>
using namespace std;
#define ll long long

int a[200005];

int main(){
    ll n,k; cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];
    ll ans=0;
    for(int i=1;i<=n;++i){
        if(a[i]<=0)continue;
        ans+=a[i]/k;
        a[i]%=k;
        if(a[i]>0){
            a[i+1]-=k-a[i];
            ++ans;
        }
    }
    cout<<ans<<endl;
}
