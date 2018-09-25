#include<bits/stdc++.h>
using namespace std;

int d[1003];

int main(){
    int n; cin>>n;
    for(int i=1;i<=n;++i)cin>>d[i];
    int sum=0;
    for(int i=1;i<=n;++i)sum+=d[i];
    if(sum!=(n-1)*2)exit((cout<<"NO"<<endl,0));
    for(int i=2;i<=n;++i)--d[i];
    for(int i=n-1;i>=1;--i)d[i]+=d[i+1];
    cout<<([&](){ for(int i=1;i<=n;++i)if(n-i<d[i])return 0; return 1; }()?"YES\n":"NO\n");
}
