#include<bits/stdc++.h>
using namespace std;

int a[200005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        int n,m; long long t; cin>>n>>m>>t;
        for(int i=1;i<=n;++i)cin>>a[i];
        int L=1,R=min(t,200000ll);
        int mx=0,nowd=1;
        
        auto need=[&](int d)->long long{
            long long nt=0,sess=0;
            int sescnt=0,done=0;
            int las=n;
            while(las>=1 && a[las]>d)--las;
            for(int i=1;i<=n;++i){
                if(a[i]>d)continue;
                ++sescnt;
                sess+=a[i];
                nt+=a[i];
                if(nt<=t)++done;
                if(sescnt==m && i<las){
                    nt+=sess;
                    sess=0;
                    sescnt=0;
                }
            }
            if(done>mx){
                mx=done;
                nowd=d;
            }
            mx=max(mx,done);
            return nt;
        };

        while(L<R){
            int mid=(L+R)>>1;
            if(need(mid)>=t)R=mid;
            else L=mid+1;
        }
        if(L)need(L-1);
        need(L);
        need(L+1);
        cout<<mx<<" "<<nowd<<endl;
        auto checkans=[&](){
            vector<int> as(a+1,a+1+n);
            sort(as.begin(),as.end());
            as.resize(unique(as.begin(),as.end())-as.begin());
            int work=0,maxd=1;
            for(int d:as){
                int nt=0,sest=0,sesc=0,done=0;
                for(int i=1;i<=n;++i){
                    if(a[i]>d)continue;
                    nt+=a[i];
                    sest+=a[i];
                    if(nt>t)break;
                    ++sesc;
                    ++done;
                    if(sesc==m){
                        sesc=0;
                        nt+=sest;
                        sest=0;
                    }
                    if(nt>=t)break;
                }
                if(done>work){
                    work=done;
                    maxd=d;
                }
            }
            if(work!=mx)assert(0);
            int nt=0,sest=0,sesc=0,done=0;
            for(int i=1;i<=n;++i){
                if(a[i]>nowd)continue;
                nt+=a[i];
                sest+=a[i];
                if(nt>t)break;
                ++sesc;
                ++done;
                if(sesc==m){
                    sesc=0;
                    nt+=sest;
                    sest=0;
                }
                if(nt>=t)break;
            }
            if(done!=mx)assert(0);
            cout<<"no problem"<<endl;
        };
        // checkans();
    }
}
