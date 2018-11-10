#include<bits/stdc++.h>
using namespace std;

int a[200005],sa[200005],pos[200005];
bitset<200005> u;

int main(){
    int t; cin>>t; while(t--){
        int n,k; cin>>n>>k;
        for(int i=1;i<=k;++i)u[i]=0;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>sa[i];
        for(int i=1;i<=n;++i)pos[sa[i]]=i;
        int outed=0;
        for(int i=1;i<=n;++i){
            if(u[a[pos[i]]])continue;
            u[a[pos[i]]]=1;
            ++outed;
            cout<<a[pos[i]];
            if(outed!=k)cout<<" ";
        }
        for(int i=1;i<=k;++i)if(!u[i]){
            cout<<i;
            ++outed;
            if(outed!=k)cout<<" ";
        }
        cout<<endl;
    }
}
