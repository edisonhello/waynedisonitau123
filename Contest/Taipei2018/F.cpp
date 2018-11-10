#include<bits/stdc++.h>
using namespace std;

int x;
struct yao{
    int w,v;
};
vector<yao> bs,ms,is;
vector<vector<yao>> v;

long long co1[1000005],co2[1000005];

long long solve(const vector<yao> &as,const vector<yao> &bs,const vector<yao> &cs){
    int a=int(as.size()),b=int(bs.size()),c=int(cs.size());

    memset(co1,0x3f,sizeof(co1)); co1[0]=0;
    for(yao &z:as)for(int i=1000000;i>=z.v;--i)co1[i]=min(co1[i],co1[i-z.v]+z.w);
    for(int i=1000000;i>=0;--i)co1[i]=min(co1[i],co1[i+1]);
    long long mnco1=1e9;
    for(yao &z:as)if(z.v>1000000)mnco1=min(mnco1,z.w);
    for(int i=0;i<=1000000;++i)co1[i]=min(co1[i],mnco1);
    
    memset(co2,0x3f,sizeof(co2)); co2[0]=0;
    for(yao &z:bs)for(int i=1000000;i>=z.v;--i)co2[i]=min(co2[i],co2[i-z.v]+z.w);
    for(int i=1000000;i>=0;--i)co2[i]=min(co2[i],co2[i+1]);
    long long mnco2=1e9;
    for(yao &z:bs)if(z.v>1000000)mnco2=min(mnco2,z.w);
    for(int i=0;i<=1000000;++i)co2[i]=min(co2[i],mnco2);

    int L=0,R=1000;
    while(LR){
        int M=(L+R)>>1;
        if(check1(M)
    }
}

int main(){
    int nb,nm,ni; cin>>x>>nb>>nm>>ni;
    bs.resize(nb);
    ms.resize(nm);
    is.resize(ni);
    long long mxb=0,mxs=0,mxi=0;
    for(int i=0;i<nb;++i)cin>>bs[i].w>>bs[i].v;
    for(int i=0;i<nm;++i)cin>>ms[i].w>>ms[i].v;
    for(int i=0;i<ni;++i)cin>>is[i].w>>is[i].v;
    for(int i=0;i<nb;++i)mxb+=bs[i].e;
    for(int i=0;i<nm;++i)mxs+=ms[i].e;
    for(int i=0;i<ni;++i)mxi+=is[i].e;
    double s=pow(mxb,1./3)*pow(mxs,1./3)*pow(mxi,1./3);
    if((s+5)*(s+1)*(s+4)<x){
        cout<<"DEAREST DROP"<<endl;
        exit(0);
    }
    long long ans=1e18;
    v.push_back(bs);    
    v.push_back(ms);    
    v.push_back(is);    
    sort(v.begin(),v.end());
    do{
        ans=min(ans,solve(v[0],v[1],v[2]));
    }while(next_permutation(v.begin(),v.end()));
    cout<<ans<<endl;
}
