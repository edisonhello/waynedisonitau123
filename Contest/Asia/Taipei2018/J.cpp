#pragma GCC optimize("Ofast","unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n,m;
ll d[1003][1003],dp[1003][1003];

pair<int,int> MWMC(){
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;++i)dp[0][i]=0;
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
        for(int k=1;k<=n;++k){
            // dp[i][k]=min(dp[i-1][j]+d[j][k],dp[i][k]);
            if((dp[i-1][j]+d[j][k]-dp[i][k])>>31)dp[i][k]=dp[i-1][j]+d[j][k];
        }
    }
    int au=1<<30,ad=1;
    for(int i=1;i<=n;++i){
        if(dp[n][i]==0x3f3f3f3f3f3f3f3f)continue;
        int u=0,d=1;
        for(int j=n-1;j>=0;--j){
            if(1ll*(dp[n][i]-dp[j][i])*d>1ll*u*(n-j)){
                u=dp[n][i]-dp[j][i];
                d=n-j;
            }
        }
        if(1ll*u*ad<1ll*au*d)au=u,ad=d;
    }
    int g=__gcd(au,ad);
    return {au/g,ad/g};
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // int t=11; while(t--){
    int t; cin>>t; while(t--){
        cin>>n>>m; 
        // n=1000; m=0;
        memset(d,0x3f,sizeof(d));
        while(m--){
            int u,v,w; cin>>u>>v>>w;
            d[u][v]=w;
        }
        auto ans=MWMC();
        if(ans.first==(1<<30))cout<<-1<<'\n';
        else cout<<ans.first<<" "<<ans.second<<'\n';
    }
}
