#include<bits/stdc++.h>
using namespace std;

int a[1000006];
bitset<1000006> ismx;

int main(){
    int ts; cin>>ts; while(ts--){
        int n; cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i],ismx[i]=0;
        int pmx=0;
        for(int i=n;i>=1;--i){
            pmx=max(pmx,a[i]);
            if(a[i]==pmx)ismx[i]=1;
        }
        long long ans=0;
        stack<int> st;
        for(int i=1;i<=n;++i){
            st.push(a[i]);
            if(ismx[i]){
                while(st.size()){
                    ans+=a[i]-st.top();
                    st.pop();
                }
            }
        }
        cout<<ans<<'\n';
    }
}
