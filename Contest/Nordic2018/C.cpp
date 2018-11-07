#include<bits/stdc++.h>
using namespace std;

int a[34536];

int main(){
    int n; cin>>n;
    for(int i=0;i<n;++i){
        int t; cin>>t; ++a[t];
    }
    int ans=0;
    int dir=0;
    int now=0;
    for(int i=1;i<=444;++i){
        if(now+dir>=20){
            dir=0; now=0; ans++;
        }
        now+=dir;
        if(a[i])++dir;
    }
    cout<<ans<<endl;
}
