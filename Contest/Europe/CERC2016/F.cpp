#include<bits/stdc++.h>
using namespace std;

int a[100005],b[100005],ta[100005],posa[100005],posb[100005];
bitset<100005> bye;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    for(int i=1;i<=n;++i)posa[a[i]]=i,posb[b[i]]=i;
    for(int i=1;i<=n;++i){
        if(a[i]!=b[i])bye[a[i]]=bye[b[i]]=1;
        if(a[i]!=b[i] && a[i]!=0)bye[i]=1;
        if(bye[i])bye[a[i]]=1;
    }
    // cout<<"bye: "; for(int i=1;i<=n;++i)cout<<bye[i]<<" "; cout<<endl;
    int ans=0;
    for(int i=1;i<=n;++i){
        if(bye[i]==1 && a[i])++ans,a[i]=0;
    }
    for(int i=1;i<=n;++i)if(a[i]!=b[i])++ans;
    cout<<ans<<endl;
}
