#include<bits/stdc++.h>
using namespace std;

int a[1000006];

bitset<1000006> _p;
vector<int> p;
int minf[1000006];

void init(){
    for(int i=2;i<=1000000;++i){
        if(_p[i])continue;
        p.push_back(i);
        minf[i]=i;
        for(auto j=1ll*i*i;j<=1000000;j+=i){
            minf[j]=i;
            _p[j]=1;
        }
    }
}

vector<int> app[1000006];

int main(){
    srand(time(0)); cin.tie(0);
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    int n; cin>>n;
    // int n=1000000;
    for(int i=1;i<=n;++i)cin>>a[i];
    // for(int i=1;i<=n;++i)a[i]=rand()%1000000+1;
    for(int i=1;i<=n;++i){
        int x=a[i];
        set<int> ff;
        while(x>1){
            ff.insert(minf[x]);
            x/=minf[x];
        }
        for(int j:ff){
            app[j].push_back(i);
        }
    }
    long long ans=0;
    for(int i=2;i<=1000000;++i){
        if(app[i].empty())continue;
        // cout<<"app["<<i<<"]: "; for(int z:app[i])cout<<z<<" "; cout<<endl;
        ans+=1ll*n*(n+1)/2;
        ans-=1ll*(app[i][0]-1)*(app[i][0]-0)/2;
        ans-=1ll*(n-app[i].back())*(n-app[i].back()+1)/2;
        for(int z=1;z<int(app[i].size());++z){
            ans-=1ll*(app[i][z]-app[i][z-1]-1)*(app[i][z]-app[i][z-1]-0)/2;
        }
        // cout<<"ans: "<<ans<<endl;
    }
    cout<<ans<<endl;
}
