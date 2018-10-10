#include<bits/stdc++.h>
using namespace std;

const int mod=65537;

vector<pair<int,pair<int,int>>> edg;
int djs[555];

int F(int x){ return djs[x]==x?x:djs[x]=F(djs[x]); }
void U(int x,int y){ djs[F(x)]=F(y); }

int main(){
    int n,m; while(cin>>n>>m){
        if(n==0 && m==0)break;
        for(int i=0;i<=n;++i)djs[i]=i;
        edg.clear();
        edg.resize(m);
        for(auto &e:edg)cin>>e.second.first>>e.second.second>>e.first;
        int ans=1;
        sort(edg.begin(),edg.end());
        for(auto &e:edg){
            if(F(e.second.first)==F(e.second.second)){
                continue;
            }
            U(e.second.first,e.second.second);
            ans=1ll*ans*e.first%mod;
        }
        cout<<ans<<endl;
    }
}
