// d[i][j] == 0 if {i,j} !in E
long long d[1003][1003],dp[1003][1003];

pair<long long,long long> MMWC(){
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;++i)dp[0][i]=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            for(int k=1;k<=n;++k){
                dp[i][k]=min(dp[i-1][j]+d[j][k],dp[i][k]);
            }
        }
    }
    long long au=1ll<<31,ad=1;
    for(int i=1;i<=n;++i){
        if(dp[n][i]==0x3f3f3f3f3f3f3f3f)continue;
        long long u=0,d=1;
        for(int j=n-1;j>=0;--j){
            if((dp[n][i]-dp[j][i])*d>u*(n-j)){
                u=dp[n][i]-dp[j][i];
                d=n-j;
            }
        }
        if(u*ad<au*d)au=u,ad=d;
    }
    long long g=__gcd(au,ad);
    return make_pair(au/g,ad/g);
}
