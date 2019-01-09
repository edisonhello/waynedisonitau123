#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define point pair<ll,ll>

point operator-(const point a,const point b){ return point(a.first-b.first,a.second-b.second); }
point operator+(const point a,const point b){ return point(a.first+b.first,a.second+b.second); }
ll operator^(const point a,const point b){ return a.first*b.second-a.second*b.first; }

pair<ll,ll> p[100005],p1,p2;

ll sign(ll x){
    if(x>0)return 1;
    if(x<0)return -1;
    return rand();
}

int main(){
#ifdef ONLINE_JUDGE
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while(cin>>n,n){
        for(int i=0;i<n;++i)cin>>p[i].first>>p[i].second;
        cin>>p1.first>>p1.second;
        cin>>p2.first>>p2.second;
        vector<int> s1,s2;
        int z=0;
        bool no=0;
        for(;;z=(z==n-1?0:z+1)){
            if(((p2-p1)^(p[z]-p1))<=0)no=1;
            else{
                if(no)break;
                else continue;
            }
        }
        for(;;z=(z==n-1?0:z+1)){
            s1.push_back(z);
            if(((p2-p1)^(p[z]-p1))<0)break;
        }
        while(((p2-p1)^(p[s1.back()]-p1))<=0)s1.pop_back();
        for(;;z=(z==n-1?0:z+1)){
            s2.push_back(z);
            if(((p2-p1)^(p[z]-p1))>0)break;
        }
        while(((p2-p1)^(p[s2.back()]-p1))>=0)s2.pop_back();
        // cout<<"de "<<s1.size()<<" "<<s2.size()<<endl;
        ll ans=0;
        for(int i=0;i<int(s2.size());++i){
            int LL=0,LR=int(s1.size())-1;
            while(LL<LR){
                int M=(LL+LR)>>1;
                if(((p[s1[M]]-p[s2[i]])^(p2-p[s2[i]]))>=0)LL=M+1;
                else LR=M;
            }
            int RL=0,RR=int(s1.size())-1;
            while(RL<RR){
                int M=(RL+RR+1)>>1;
                if(((p[s1[M]]-p[s2[i]])^(p1-p[s2[i]]))<=0)RR=M-1;
                else RL=M;
            }
            if(sign((p2-p[s2[i]])^(p[s1[LL]]-p[s2[i]])) != sign((p2-p[s2[i]])^(p1-p[s2[i]])))continue;
            if(sign((p2-p[s2[i]])^(p[s1[RL]]-p[s2[i]])) != sign((p2-p[s2[i]])^(p1-p[s2[i]])))continue;
            if(sign((p1-p[s2[i]])^(p[s1[LL]]-p[s2[i]])) != sign((p1-p[s2[i]])^(p2-p[s2[i]])))continue;
            if(sign((p1-p[s2[i]])^(p[s1[RL]]-p[s2[i]])) != sign((p1-p[s2[i]])^(p2-p[s2[i]])))continue;
            ans+=RL-LL+1;
        }
        cout<<ans<<'\n';
    }
}
