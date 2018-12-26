#include<bits/stdc++.h>
using namespace std;

int a[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n; cin>>n;
        for(int i=2;i<=n;++i)cin>>a[i];
        for(int i=3;i<=n;++i)a[i]+=a[i-1];
        sort(a+1,a+1+n);
        long long ans=0,ls=0,rs=0;
        int lc=0,rc=0;
        int L=1,R=n;
        vector<long long> op;
        while(L<=R){
            ans+=(a[L]*1ll*lc-ls)+(rs-a[L]*1ll*rc);
            ++lc; ls+=a[L];
            ++L;
            op.push_back(ans);
            if(!(L<=R))break;
            ans+=(a[R]*1ll*lc-ls)+(rs-a[R]*1ll*rc);
            ++rc; rs+=a[R];
            --R;
            op.push_back(ans);
        }
        for(int i=0;i<int(op.size());++i){
            cout<<op[i]<<" \n"[i==op.size()-1];
        }
    }
}
