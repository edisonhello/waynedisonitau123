#include<bits/stdc++.h>
using namespace std;

set<long long> checked;
vector<vector<long long>> ans;

void check(long long n,long long a){
    if(checked.find(a)!=checked.end())return;
    checked.insert(a);
    vector<long long> nw;
    while(n%a==0)n/=a,nw.push_back(a);
    while(n%(a+1)==0)n/=(a+1),nw.push_back(a+1);
    if(n!=1)return;
    if(nw[0]==a+1)return;
    ans.push_back(nw);
}

int main(){
    freopen("little.in","r",stdin);
    freopen("little.out","w",stdout);
    long long n; cin>>n;
    if((n&-n)==n){
        cout<<-1<<endl;
        exit(0);
    }
    for(int i=2;i<=120000;++i){
        check(n,i);
    }
    int tq=pow(n,1.0/3);
    for(int i=max(2,tq-4);i<=tq+4;++i){
        check(n,i);
    }
    int sq=sqrt(n);
    for(int i=max(2,sq-4);i<=sq+4;++i){
        check(n,i);
    }
    check(n,n);
    cout<<ans.size()<<'\n';
    for(auto &v:ans){
        cout<<v.size();
        for(long long i:v)cout<<" "<<i;
        cout<<'\n';
    }
}
