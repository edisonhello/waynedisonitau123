#include<bits/stdc++.h>
using namespace std;

int pos[1005][2];

int main(){
    freopen("intel.in","r",stdin);
    freopen("intel.out","w",stdout);
    int n; cin>>n;
    for(int i=0;i<n;++i){
        cin>>pos[i][0]>>pos[i][1];
    }
    int ans=0;
    for(int i=0;i<n;++i){
        int j=i+1;
        if(j==n)j=0;
        ans+=abs(pos[i][0]-pos[j][0])+abs(pos[i][1]-pos[j][1]);
    }
    int l=1e9,r=-1e9,d=1e9,u=-1e9;
    for(int i=0;i<n;++i){
        l=min(l,pos[i][0]);
        r=max(r,pos[i][0]);
        d=min(d,pos[i][1]);
        u=max(u,pos[i][1]);
    }
    ans-=(r-l)*2+(u-d)*2;
    cout<<ans<<endl;
}
