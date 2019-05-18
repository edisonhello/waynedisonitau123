#include<bits/stdc++.h>
using namespace std;

string mp[2004];

int main(){
    ios_base::sync_with_stdio(0) ; cin.tie(0);
    int n,m; cin>>n>>m;
    for(int i=0;i<n;++i)cin>>mp[i];

    int mnn=1,mnm=1;
    for(int i=0;i<n;++i){
        for(int j=0;j<m/2;++j){
            if(mp[i][j]!=mp[i][m-1-j])mnm=max(mnm,m/2-j);
        }
    }
    for(int i=0;i<n/2;++i){
        for(int j=0;j<m;++j){
            if(mp[i][j]!=mp[n-1-i][j])mnn=max(mnn,n/2-i);
        }
    }
    int mxn=n/2-1,mxm=m/2-1;
    cout<<(mxn-mnn+1)*(mxm-mnm+1)<<endl;
}
