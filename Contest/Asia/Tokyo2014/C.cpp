#include<bits/stdc++.h>
using namespace std;

pair<int,int> a[1004];
int le[1005],mn[1007][1007];
int dp[1005];

int main(){
    int n,m; cin>>n>>m;
    for(int i=0;i<m;++i)cin>>a[i].first>>a[i].second;
    for(int i=0;i<=n+1;++i)le[i]=1e9;
    for(int i=0;i<m;++i)le[a[i].second]=min(le[a[i].second],a[i].first);
    for(int i=0;i<=n+1;++i){
        mn[i][i]=le[i];
        for(int j=i+1;j<=n+1;++j){
            mn[i][j]=min(mn[i][j-1],le[j]);
            // cout<<"mn "<<i<<" "<<j<<" = "<<mn[i][j]<<endl;
        }
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    for(int i=1;i<=n+1;++i){
        for(int j=0;j<i;++j){
            if(mn[j+1][i]==1e9){
                dp[i]=min(dp[i],dp[j]+i-j);
            }
            else{
                dp[i]=min(dp[i],dp[j]+(i-j)+(i-mn[j+1][i])*2);
            }
        }
    }
    cout<<dp[n+1]<<endl;
}
