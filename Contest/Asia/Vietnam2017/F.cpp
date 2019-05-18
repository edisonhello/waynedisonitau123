#include<bits/stdc++.h>
using namespace std;

struct item{
    int i, l, r;
};

long long a[2005];
long long sum[2005],sum2[2005];
long long dp[2005][2005];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n,g,k; cin>>n>>g>>k;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;++i)sum2[i]=sum2[i-1]+a[i]*a[i];
    for(int i=1;i<=g;++i){
        auto calc=[&](int l,int r)->long long{
            if(k==1){
                int m=(l+r)>>1;
                return ((sum[r]-sum[m])-a[m]*(r-m))+(a[m]*(m-l+1)-(sum[m]-sum[l-1]));
            }
            else{
                long long avg=(sum[r]-sum[l-1])/(r-l+1);
                auto cc=[&](long long v)->long long{
                    return (sum2[r]-sum2[l-1]) - (2*v*(sum[r]-sum[l-1])) + (r-l+1)*v*v;
                };
                return min(cc(avg-1),min(cc(avg),cc(avg+1)));
            }
        };
        auto f=[&](int l,int r)->long long{
            return dp[i-1][l] + calc(l+1,r);
        };
        deque<item> dq;
        dq.push_back({0, 1, n});
        for(int j=1;j<=n;++j){
            dp[i][j] = f(dq.front().i, j);
            // cout<<"dp "<<i<<" "<<j<<" "<<dp[i][j]<<" fr " << dq.front().i << endl;
            while (dq.size() && dq.front().r <= j) dq.pop_front();
            if (dq.size()) dq.front().l = j + 1;
            item it={j, j + 1, n};
            while(dq.size() && f(j,dq.back().l) <= f(dq.back().i, dq.back().l)) {
                // for (int k = dq.back().l; k <= dq.back().r; ++k) assert(f(j, k) <= f(dq.back().i, k));
                dq.pop_back();
            }
            if (dq.size()) {
                int d = 13, c = dq.back().l;
                while (d--) if (c + (1 << d) <= dq.back().r) {
                    if (f(j, c + (1 << d)) > f(dq.back().i, c + (1 << d))) c += (1 << d);
                }
                dq.back().r = c;
                it.l = c + 1;
            }
            if (it.l <= n) dq.push_back(it);
        }
    }
    cout<<dp[g][n]<<'\n';
}


