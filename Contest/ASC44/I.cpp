#include<bits/stdc++.h>
using namespace std;

struct test{
    long long dl,pt;
} a[100005];

struct stop{
    long long l,r;
} b[100005];

struct all{
    int type,index;
    long long time;
} c[200005];

int main(){
#ifdef ONLINE_JUDGE
    freopen("intelligent.in", "r", stdin);
    freopen("intelligent.out", "w", stdout);
#endif
    int n; while(cin>>n,n){
        for(int i=0;i<n;++i){
            cin>>a[i].dl>>a[i].pt; ++a[i].pt;
        }
        int m; cin>>m;
        for(int i=0;i<m;++i){
            cin>>b[i].l>>b[i].r;
        }   
        for(int i=0;i<n;++i){
            c[i].type=1;
            c[i].index=i;
            c[i].time=a[i].dl;
        }
        for(int i=0;i<m;++i){
            c[i+n].type=2;
            c[i+n].index=i;
            c[i+n].time=b[i].r;
        }
        sort(c,c+n+m,[&](const all &a,const all &b){ return a.time<b.time; });
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,less<pair<long long,int>>> pq;
        set<int> ans;
        long long empty=0;
        long long last=0;
        for(int i=0;i<n+m;++i){
            if(c[i].type==1){
                empty+=c[i].time-last;
                if(a[c[i].index].pt<=empty){
                    empty-=a[c[i].index].pt;
                    pq.emplace(a[c[i].index].pt,c[i].index);
                    ans.insert(c[i].index);
                }
                else{
                    if(pq.empty());
                    else{
                        if(pq.top().first<=a[c[i].index].pt);
                        else{
                            ans.erase(pq.top().second);
                            empty+=pq.top().first;
                            pq.pop();
                            ans.insert(c[i].index);
                            empty-=a[c[i].index].pt;
                            pq.emplace(a[c[i].index].pt,c[i].index);
                        }
                    }
                }
            }
            else{
                empty+=c[i].time-last;
                empty-=b[c[i].index].r-b[c[i].index].l+1;
            }
            last=c[i].time;
        }
        cout<<ans.size()<<'\n';
        for(int i:ans)cout<<i+1<<" "; cout<<endl;
    }
}
