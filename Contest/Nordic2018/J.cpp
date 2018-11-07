#include<bits/stdc++.h>
using namespace std;


void NO(){
    cout<<"impossible"<<endl;
    exit(0);
}
#define ll long long

bool ok(long long a,ll b,ll c,ll d,ll c0,ll c1){
    ll cc=c0+c1;
    if(a+b+c+d != cc*(cc-1)/2)return false;
    if(c1)for(ll s1=0;s1<=c1;++s1){
        ll count10=s1*c0;
        if(count10<=c && count10+c0>=c){
            ll need10=c-count10;
            ll front0=c0-need10;
            for(int i=0;i<s1;++i)cout<<1;
            for(int i=0;i<front0;++i)cout<<0;
            cout<<1;
            for(int i=0;i<need10;++i)cout<<0;
            for(int i=s1+1;i<c1;++i)cout<<1;
            cout<<endl;
            return true;
        }
    }
    if(c0)for(ll s0=0;s0<=c0;++s0){
        ll count01=s0*c1;
        if(count01<=b && count01+c1>=b){
            ll need01=b-count01;
            ll front1=c1-need01;
            for(int i=0;i<s0;++i)cout<<0;
            for(int i=0;i<front1;++i)cout<<1;
            cout<<0;
            for(int i=0;i<need01;++i)cout<<1;
            for(int i=s0+1;i<c0;++i)cout<<0;
            cout<<endl;
            return true;
        }
    }
    return false;
}

int main(){
    long long a,b,c,d;
    cin>>a>>b>>c>>d;
    long long c0=0,c1=0;
    for(;c0*(c0-1)/2<a;++c0);
    if(c0*(c0-1)/2!=a)NO();
    for(;c1*(c1-1)/2<d;++c1);
    if(c1*(c1-1)/2!=d)NO();
    vector<int> able0,able1;
    if(a==0){
        able0.push_back(0);
        able0.push_back(1);
    }
    else{
        able0.push_back(c0);
    }
    if(d==0){
        able1.push_back(0);
        able1.push_back(1);
    }
    else{
        able1.push_back(c1);
    }
    for(int i:able0){
        for(int j:able1){
            if(ok(a,b,c,d,i,j))return 0;
        }
    }
    cout<<"impossible"<<endl;
}
