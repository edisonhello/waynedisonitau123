#include<bits/stdc++.h>
using namespace std;

int a[111];

int get(int m){
    int r=0;
    while(m--){
        int t; cin>>t;
        r=r*10+t;
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n,m; cin>>n>>m;
        int x=get(m),y=get(m);
        for(int i=0;i<n;++i)cin>>a[i];
        int win=0;
        for(int i=0;i<n;++i){
            int xx=0;
            for(int j=0;j<m;++j){
                xx=xx*10+a[(i+j)%n];
            }
            if(x<=xx && xx<=y)++win;
        }
        cout<<win<<'\n';
    }
}
