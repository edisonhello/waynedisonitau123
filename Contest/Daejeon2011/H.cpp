#include<bits/stdc++.h>
using namespace std;

int deg[1005][2];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n; cin>>n;
        memset(deg,0,sizeof(deg));
        for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j){
                int c; cin>>c;
                ++deg[i][c];
                ++deg[j][c];
            }
        }
        int sumab=0;
        for(int i=0;i<n;++i)sumab+=deg[i][0]*deg[i][1];
        sumab>>=1;
        int total=n*(n-1)*(n-2)/6;
        cout<<total-sumab<<'\n';
    }
}
