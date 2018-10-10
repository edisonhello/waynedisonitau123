#include<bits/stdc++.h>
using namespace std;

struct point{
    long long x,y;
    point(long long x=0,long long y=0):x(x),y(y){}
} pt[444];
point operator-(const point &a,const point &b){ return point(a.x-b.x,a.y-b.y); }
long long operator^(const point &a,const point &b){ return a.x*b.y-a.y*b.x; }
double abs(point a){ return sqrt(a.x*a.x+a.y*a.y); }

int dp[2][444][444];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        memset(dp,0,sizeof(dp));
        int n; cin>>n;
        for(int i=1;i<=n;++i)cin>>pt[i].x>>pt[i].y;
        int ans=1;
        dp[0][1][2]=((pt[1]^pt[2])>0 && abs(pt[1])<abs(pt[2])?2:0);
        if(dp[0][1][2]==2)ans=2;
        for(int i=3;i<=n;++i){
            int at=i&1;
            memset(dp[at],0,444*444*4);
            for(int j=1;j<=i;++j)for(int k=1;k<=i;++k)dp[at][j][k]=dp[at^1][j][k];
            for(int j=1;j<i;++j){
                // j -> i
                if((pt[j]^pt[i])>0 && abs(pt[j])<abs(pt[i]))dp[at][j][i]=max(dp[at][j][i],2);
            }
            for(int j=1;j<i-1;++j){
                for(int k=j+1;k<i;++k){
                    // j -> k -> i
                    if(!dp[at^1][j][k])continue;
                    if((pt[k]^pt[i])<=0)continue;
                    if(abs(pt[k])>=abs(pt[i]))continue;
                    point v1=pt[k]-pt[j],v2=pt[i]-pt[k];
                    if((v1^v2)<=0)continue;
                    dp[at][k][i]=max(dp[at][k][i],dp[at^1][j][k]+1);
                }
            }
            for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)ans=max(ans,dp[at][i][j]);
        }
        cout<<ans<<'\n';
    }
}
