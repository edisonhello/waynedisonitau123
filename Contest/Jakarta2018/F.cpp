#include<bits/stdc++.h>
using namespace std;


int a[100005],b[100005];
int mxat[100005];
long long ane[100005],bne[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    int pro=0,pre=0;
    for(int i=1;i<=n;++i){
        if(pre+a[i]>m)break;
        pro=i;
        pre+=a[i];
    }
    for(int i=1;i<=n;++i)ane[i]=ane[i-1]+a[i];
    for(int i=1;i<=n;++i)bne[i]=bne[i-1]+b[i];
    if(bne[pro]>m)exit((cout<<0<<endl,0));
    mxat[pro]=pro;
    for(int i=pro-1;i>=1;--i){
        if(b[i]>=b[mxat[i+1]]){
            mxat[i]=i;
        }
        else mxat[i]=mxat[i+1];
    }
    int now=1;
    int uball=0;
    long long utime=0;
    vector<long long> boom;
    // cout<<"pro: "<<pro<<endl;
    while(1){
        if(now>pro)break;
        if(bne[pro]+utime>m)break;
        int stopat=mxat[now];
        long long twhenat=bne[stopat]+utime;
        int i_go=upper_bound(ane,ane+1+n,twhenat)-ane-1;
        int i_have_ball=i_go-uball;
        // cout<<"now: "<<now<<" ,stopat: "<<stopat<<" ,twhenat: "<<twhenat<<" i_go: "<<i_go<<" i_have ball: "<<i_have_ball<<endl;;
        if(i_have_ball==0){
            ++now;
            continue;
        }
        for(int z=0;z<i_have_ball;++z){
            boom.push_back(utime+bne[stopat]);
            utime+=b[stopat];
            ++uball;
        }
        now=stopat;
    }
    if(bne[pro]+utime>m){
        while(boom.size() && boom.back()>m)boom.pop_back();
        cout<<boom.size()<<endl;
        for(auto i:boom)cout<<i<<" ";
        cout<<endl;
    }
    else cout<<-1<<endl;
}
