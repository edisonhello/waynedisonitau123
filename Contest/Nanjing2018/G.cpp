#include<bits/stdc++.h>
using namespace std;

#define ll long long

const long long mod=1000000007;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        long long n; cin>>n;
        long long t1=(n*n+3*n+2)%mod*n%mod*(n+1)%mod*250000002;
        long long t2=(-2*n-3)%mod*n%mod*(n+1)%mod*(2*n+1)%mod*83333334%mod;
        long long t3=n*n%mod*(n+1)%mod*(n+1)%mod*125000001%mod;
        cout<<((t1+t2+t3)%mod+mod)%mod<<'\n';;
    }
}
