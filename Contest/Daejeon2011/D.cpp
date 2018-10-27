#include<bits/stdc++.h>
using namespace std;

int sk[10005][5];
int dp[2][6][32];
int sum[10005][32];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        int n,k; cin>>n>>k;
        k=min(k,5);
        for(int i=0;i<n;++i)for(int j=0;j<5;++j)cin>>sk[i][j];
        for(int i=0;i<n;++i)for(int z=0;z<32;++z){
            sum[i][z]=0;
            for(int j=0;j<5;++j){
                if(z&(1<<j)){
                    sum[i][z]+=sk[i][j];
                }
            }
        }
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;++i){
            int now=i&1;
            int pre=now^1;
            for(int j=0;j<=k;++j)for(int z=0;z<32;++z)dp[now][j][z]=dp[pre][j][z];
            for(int j=0;j<k;++j){
                for(int z=0;z<32;++z){
                    for(int zz=z;zz<32;++zz){
                        if((zz|z)!=zz)continue;
                        dp[now][j+1][zz]=max(dp[now][j+1][zz],dp[pre][j][z]+sum[i][zz^z]);
                    }
                }
            }
        }
        int mx=0;
        for(int i=0;i<32;++i){
            mx=max(mx,dp[(n-1)&1][k][i]);
        }
        cout<<mx<<endl;
    }
}
