#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long

ll k[666];
ll offset;
vector<pair<ll,ll>> ans;

auto calc=[&](ll x)->vector<ll>{
    vector<ll> rt(64,0);
    if(!x)return rt;
    // rt[0]=x/2;
    for(int i=0;i<64;++i){
        if(i==63)rt[i]=0;
        else rt[i]=x/(1ull<<(i+1))*(1ull<<i);
        ll pa=(i==63?x:x%(1ull<<(i+1)));
        ll mi=(1ull<<i)-1;
        if(pa<mi);
        else rt[i]+=pa-mi;
    }
    // cout<<"calc : "; for(auto i:rt)cout<<i<<" "; cout<<endl;
    return rt;
};
auto icalc=[&](vector<ll> &v)->ll{
    // cout<<"icalc: "; for(auto i:v)cout<<i<<" "; cout<<endl;
    ll x=v[0]*2;
    if(calc(x)==v)return x;
    if(x && calc(x-1)==v)return x-1;
    // return -1;
    return 0;
};
auto doL=[&](ll R)->void{
    // cout<<"called doL, R: "<<R<<endl;
    vector<ll> r=calc(R);
    for(int i=0;i<64;++i)r[i]-=k[i];
    ll L=icalc(r);
    // cout<<"get L: "<<L<<endl;
    ans.emplace_back(L+1,R);
};

void dfs(int n){
    if(n<0){ return; }

    ll maxs=k[n];
    ll mins=k[0];
    // cout<<"n: "<<n<<" , maxs: "<<maxs<<" , mins: "<<mins<<endl;
    if(maxs==0){
        dfs(n-1);
        return;
    }
    if(maxs&1){
        ll shouldL=maxs/2;
        ll shouldR=maxs/2+1;
        if(shouldL<=mins && mins<=shouldR){
            offset+=(1ull<<n);
            dfs(n-1);
            offset-=(1ull<<n);
            doL((1ull<<n)+maxs-1+offset);
        }
        else{
            ll R=(1ull<<n)+maxs-1+offset;
            doL(R);
        }
    }
    else{
        // maxs is even
        ll should=maxs/2;
        if(mins!=should){
            ll R=(1ull<<n)+maxs-1+offset;
            doL(R);
        }
        else{
            offset+=(1ull<<n);
            dfs(n-1);
            offset-=(1ull<<n);
            ll R=(1ull<<n)+maxs-1+offset;
            doL(R);
        }
    }
}

int main(){
    int n; while(cin>>n,n){
        memset(k,0,sizeof(k));
        for(int i=0;i<n;++i)cin>>k[i];
        offset=0;
        ans.clear();
        dfs(n-1);
        vector<pair<ll,ll>> real;
        for(auto &p:ans){
            vector<ll> a=calc(p.first-1),b=calc(p.second);
            bool same=1;
            for(int i=0;i<64;++i)if(b[i]-a[i]!=k[i])same=0;
            if(p.first<1 || p.second<1 || p.first>1000000000000000000 || p.second>1000000000000000000)same=0;
            if(same)real.push_back(p);
        }
        if(real.empty()){ cout<<"None"<<'\n'; }
        else if(real.size()>1u){ cout<<"Many"<<'\n'; }
        else cout<<real[0].first<<" "<<real[0].second<<'\n';
    }
}
