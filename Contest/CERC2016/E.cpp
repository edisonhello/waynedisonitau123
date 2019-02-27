#include<bits/stdc++.h>
using namespace std;
#define ll long long

set<ll> app;
vector<tuple<ll,ll,ll>> ans;

int main(){
    ll n,k; cin>>k>>n;
    for(ll a=1;a<=100;++a)for(ll b=a+1;b<=100;++b)for(ll c=b+1;c<=100;++c){
        if(a*a+b*b+c*c==k*(a*b+b*c+c*a)+1){
            if(app.count(a)+app.count(b)+app.count(c))continue;
            app.insert(a);
            app.insert(b);
            app.insert(c);
            ans.emplace_back(a,b,c);
        }
    }
    int ptr=0;
    while((int)ans.size()<n){
        ll a,b,c;
        tie(a,b,c)=ans[ptr]; ++ptr;
        auto trans=[&](ll a,ll b,ll c){
            a=k*(b+c)-a;
            b=k*(a+c)-b;
            c=k*(a+b)-c;
            if(app.count(a)+app.count(b)+app.count(c))return;
            app.insert(a);
            app.insert(b);
            app.insert(c);
            ans.emplace_back(a,b,c);
        };
        trans(a,b,c);
        trans(a,c,b);
        trans(b,a,c);
        trans(b,c,a);
        trans(c,a,b);
        trans(c,b,a);
    }
    for(int i=0;i<n;++i){
        ll a,b,c; 
        tie(a,b,c)=ans[i];
        cout<<a<<" "<<b<<" "<<c<<endl;
    }
}
