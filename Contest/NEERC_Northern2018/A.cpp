#include<bits/stdc++.h>
using namespace std;

int dp[1000006];
int w[]={6,2,5,5,4,5,6,3,7,6};
int v[]={0,1,2,3,4,5,6,7,8,9};

int main(){
    freopen("auxiliary.in","r",stdin);
    freopen("auxiliary.out","w",stdout);
    memset(dp,0xc0,sizeof(dp));
    dp[0]=0;
    int n; cin>>n;
    for(int i=0;i<10;++i){
        for(int j=w[i];j<=n;++j){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[n]<<endl;
}
