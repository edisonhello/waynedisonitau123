#include<bits/stdc++.h>
using namespace std;
#define double long double

int a[105],e[105];
double x[105];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n; cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i]>>e[i],++e[i];
        auto needx=[&](const double lam)->double{
            double sum=0;
            for(int i=1;i<=n;++i){
                if(e[i]==1){ x[i]=0; continue; }
                x[i]=pow(lam/e[i]/a[i],1./(e[i]-1));
                sum+=x[i];
            }
            return sum;
        };
        auto check1=[&](double to1)->double{
            int min1a=1e6;
            for(int i=1;i<=n;++i)if(e[i]==1)min1a=min(min1a,a[i]);
            if(min1a==1e6)to1=0;
            double rt=to1*min1a;
            double L=0,R=10000;
            while(R-L>1e-12){
                double M=(L+R)/2;
                if(needx(M)>=1-to1)R=M;
                else L=M;
            }
            double sum=0;
            for(int i=1;i<=n;++i)if(e[i]>1)sum+=a[i]*pow(x[i],e[i]);
            // cout<<"check1 "<<to1<<" get min sum is "<<sum+rt<<endl;
            // cout<<"x is "; for(int i=1;i<=n;++i)cout<<x[i]<<" "; cout<<endl;
            return sum+rt;
        };
        double L=0,R=1;
        while(R-L>1e-12){
            double M1=L+(R-L)/3;
            double M2=R-(R-L)/3;
            if(check1(M1)>check1(M2))L=M1;
            else R=M2;
        }
        double sum=0;
        for(int i=1;i<=n;++i)if(e[i]>1)sum+=a[i]*pow(x[i],e[i]);
        double mnmn=1e9;
        for(int i=1;i<=n;++i)if(e[i]==1)mnmn=min(mnmn,a[i]*L);
        cout<<fixed<<setprecision(20)<<sum+(mnmn<1e9?mnmn:0)<<endl;
    }
}
// 
