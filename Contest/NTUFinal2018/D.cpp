#include<bits/stdc++.h>
using namespace std;

double calc(vector<int> v,vector<int> gr){
    double ans=0;
    int z=0;
    for(int i:gr){
        for(int y=0;y<i;++y){
            ans+=double(v[z])/i;
            ++z;
        }
    }
    return ans;
}

double BFMAX=0;

int a[305];
double dp[32][305];
int cf[32][305],ls[32],rs[32];

double AC(int n,int m){
    for(int i=0;i<32;++i)for(int j=0;j<305;++j)dp[i][j]=-1e9;
    dp[0][0]=0;
    for(int i=0;i<m;++i){
        int l=ls[i],r=rs[i]; 
        if(l==0)l=1;
        for(int w=l;w<=r;++w){
            double value=1.0/w;
            for(int j=0;j+w<=300;++j){
                if(dp[i][j]+value > dp[i+1][j+w]){
                    dp[i+1][j+w]=dp[i][j]+value;
                    cf[i+1][j+w]=w;
                }
            }
        }
    }
    vector<int> grs;
    int ni=m,nj=n;
    while(dp[ni][nj]<0)++nj;
    int exceed=nj-n;
    while(ni){
        grs.push_back(cf[ni][nj]);
        tie(ni,nj)=make_pair(ni-1,nj-cf[ni][nj]);
    }
    // cout<<"grs: "; for(int i:grs)cout<<i<<" "; cout<<endl;
    sort(grs.begin(),grs.end(),greater<int>());
    while(exceed--)grs.pop_back();
    sort(a,a+n,greater<int>());
    reverse(grs.begin(),grs.end());
    return calc(vector<int>(a,a+n),grs);
}

void dfs(int now,int mm,int sum,int nn,vector<int> gr){
    if(now==mm){
        if(sum==nn){
            sort(gr.begin(),gr.end());
            BFMAX=max(BFMAX,calc(vector<int>(a,a+nn),gr));
        }
        return;
    }
    if(sum>nn)return;
    for(int i=ls[now];i<=rs[now];++i){
        gr.push_back(i);
        dfs(now+1,mm,sum+i,nn,gr);
        gr.pop_back();
    }
}

double BF(int n,int m){
    dfs(0,m,0,n,vector<int>());
    return BFMAX;
}

int main(){
    srand(time(0)+clock());
    int n; scanf("%d",&n);
    for(int i=0;i<n;++i)scanf("%d",&a[i]);
    int m; scanf("%d",&m);
    for(int i=0;i<m;++i)scanf("%d%d",&ls[i],&rs[i]);
    cout<<fixed<<setprecision(14)<<AC(n,m)<<endl;
    // cout<<fixed<<setprecision(14)<<BF(n,m)<<endl;
    /* int n=rand()%100;
    int m=rand()%n+1;
    int le=n-m;
    vector<int> gr1(m,1),gr2(m,1);
    for(int z=0;z<le;++z)++gr1[rand()%m];
    for(int z=0;z<le;++z)++gr2[rand()%m];
    sort(gr1.begin(),gr1.end());
    sort(gr2.begin(),gr2.end());
    double sum1=0,sum2=0;
    for(int i:gr1)sum1+=1.0/i;
    for(int i:gr2)sum2+=1.0/i;
    while(1){
        vector<int> v(n);
        for(int i=0;i<n;++i)v[i]=rand()%1000;

        sort(v.begin(),v.end(),greater<int>());

        double ans1=calc(v,gr1);
        double ans2=calc(v,gr2);
        if((gr1<=gr2 && ans1>=ans2) || (gr1>=gr2 && ans1<=ans2))continue;
        else{
            cout<<"n = "<<n<<endl;
            for(int i:v) cout<<i<<" "; cout<<endl;
            cout<<"m = "<<m<<endl;
            for(int i:gr1)cout<<i<<" "; cout<<ans1<<endl;;
            for(int i:gr2)cout<<i<<" "; cout<<ans2<<endl;
            break;
        }

        cout<<ans1<<" "<<ans2<<" "<<(ans1<ans2)<<" "<<sum1<<" "<<sum2<<" "<<(sum1<sum2)<<endl;
    } */
}
