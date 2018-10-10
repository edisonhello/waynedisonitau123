#include<bits/stdc++.h>
using namespace std;

int a[1005];

int main(){
    int ts; cin>>ts; while(ts--){
        int n,x; cin>>n>>x;
        for(int i=1;i<=n;++i)cin>>a[i];
        if(x<=n){ cout<<x<<endl; continue; }
        x-=n;
        long long L=0,R=1e16;
        auto serv=[&](long long t)->long long{
            long long rt=0;
            for(int i=1;i<=n;++i){
                rt+=t/a[i];
            }
            return rt;
        };
        while(R>L){
            long long M=(L+R)>>1;
            if(serv(M)>=x)R=M;
            else L=M+1;
        }
        // cout<<"x: "<<x<<endl;
        int nth=x-serv(L-1);
        // cout<<"served: "<<serv(L-1)<<endl;
        // cout<<"time: "<<L<<endl;
        // cout<<"nth: "<<nth<<endl;
        vector<int> ept;
        for(int i=1;i<=n;++i){
            if(L%a[i]==0)ept.push_back(i);
        }

        cout<<ept[nth-1]<<'\n';
    }
}
