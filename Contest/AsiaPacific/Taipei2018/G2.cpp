#include<bits/stdc++.h>
using namespace std;
#define double long double

int a[105],e[105];
double x[105];
bool skip[105];

double mpow(double b,int n){
    double a=1;
    while(n){
        if(n&1)a*=b;
        b*=b; n>>=1;
    }
    return a;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        memset(skip,0,sizeof(skip));
        memset(x,0,sizeof(x));
        int n; cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i]>>e[i],++e[i];

        int mne1id=-1;
        for(int i=1;i<=n;++i)if(e[i]==1)mne1id=i;
        for(int i=1;i<=n;++i)if(e[i]==1 && a[i]<a[mne1id])mne1id=i;
        for(int i=1;i<=n;++i)if(e[i]==1 && i!=mne1id)skip[i]=1;

        // cout<<"mne1id: "<<mne1id<<endl;
        if(mne1id!=-1){
            double sumx=0;
            for(int i=1;i<=n;++i)if(e[i]>1){
                x[i]=pow((double)a[mne1id]/e[i]/a[i],1.0/(e[i]-1));
                sumx+=x[i];
            }
            // cout<<"sumx: "<<sumx<<endl;
            if(sumx<=1){
                double ot=1-sumx;
                double sum=a[mne1id]*ot;
                for(int i=1;i<=n;++i)if(e[i]>1){
                    sum+=a[i]*mpow(x[i],e[i]);
                }
                cout<<fixed<<setprecision(20)<<sum<<endl;
                continue;
            }
        }
        auto getsumx=[&](const double &la)->double{
            double sum=0;
            for(int i=1;i<=n;++i)if(e[i]>1){
                x[i]=pow(la/e[i]/a[i],1.0/(e[i]-1));
                sum+=x[i];
            }
            return sum;
        };
        double L=0,R=6000;
        while(R-L>1e-10){
            double M=(L+R)/2;
            if(getsumx(M)>=1)R=M;
            else L=M;
        }
        double sum=0;
        for(int i=1;i<=n;++i)if(e[i]>1){
            sum+=a[i]*mpow(x[i],e[i]);
        }
        cout<<fixed<<setprecision(20)<<sum<<endl;
    }
}
