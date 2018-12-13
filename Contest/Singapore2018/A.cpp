#pragma GCC optimize("O3", "no-stack-protector")
#pragma GCC target("avx")
#include<bits/stdc++.h>
using namespace  std;

const int maxn = 1.3e7;
pair<int, int> line[maxn];

long long rotatingSweepLine(vector<pair<int, int>> ps){
    int n=int(ps.size());
    vector<int> id(n),pos(n);
    int m=-1;
    for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)line[++m]=make_pair(i,j); ++m;
    sort(line,line + m,[&](const pair<int, int> &a,const pair<int, int> &b)->bool{
        if(ps[a.first].first==ps[a.second].first)return 0;
        if(ps[b.first].first==ps[b.second].first)return 1;
        return (ps[a.first].second-ps[a.second].second)*1ll * (ps[b.first].first-ps[b.second].first)<(ps[b.first].second-ps[b.second].second)*1ll*(ps[a.first].first-ps[a.second].first);
    });
    for(int i=0;i<n;++i)id[i]=i;
    sort(id.begin(),id.end(),[&](const int &a,const int &b){ return ps[a]<ps[b]; });
    for(int i=0;i<n;++i)pos[id[i]]=i;

    auto area=[&](const int &a,const int &b,const int &c)->long long{
        long long r=0;
        r+=ps[a].first*1ll*ps[b].second-ps[a].second*1ll*ps[b].first;
        r+=ps[b].first*1ll*ps[c].second-ps[b].second*1ll*ps[c].first;
        r+=ps[c].first*1ll*ps[a].second-ps[c].second*1ll*ps[a].first;
        return r;
    };

    // cout<<"ps: "; for(int i=0;i<n;++i)cout<<"("<<ps[i].first<<","<<ps[i].second<<") "; cout<<endl;
    long long ans = 0;
    for(int i=0;i<m;++i){
        auto l=line[i];
        // ans=max(ans,area(l.first,l.second,pos[0]));
        // ans=max(ans,area(l.first,l.second,pos[n-1]));
        long long x = area(l.first, l.second, id[0]);
        long long y = area(l.first, l.second, id[n - 1]);
        if (x > ans) ans = x;
        if (y > ans) ans = y;
        // ans=max(ans,area(l.first,l.second,id[0]));
        // ans=max(ans,area(l.first,l.second,id[n-1]));
        // cout<<"doing line "<<l.first<<" "<<l.second<<endl;
        // cout<<"pos: "; for(int i=0;i<n;++i)cout<<pos[i]<<" "; cout<<endl;
        // cout<<"id : "; for(int i=0;i<n;++i)cout<<id[i]<<" "; cout<<endl;
        // swap(pos[l.first],pos[l.second]);
        // tie(id[pos[l.second]],id[pos[l.first]])=make_pair(l.second,l.first);
        tie(pos[l.first],pos[l.second],id[pos[l.first]],id[pos[l.second]])=make_tuple(pos[l.second],pos[l.first],l.second,l.first);
    }
    return ans;
}

pair<int,int> operator-(const pair<int,int> a,const pair<int,int> b){
    return make_pair(a.first-b.first,a.second-b.second);
}
long long operator^(const pair<int,int> a,const pair<int,int> b){
    return a.first*1ll*b.second-a.second*1ll*b.first;
}

vector<pair<int,int>> tubao(vector<pair<int,int>> &v){
    int n=int(v.size());
    vector<int> tb;
    for(int i=0;i<n;++i){
        while(tb.size()>1u && ((v[i]-v[tb[tb.size()-2]])^(v[tb.back()]-v[tb[tb.size()-2]]))>=0)tb.pop_back();
        tb.push_back(i);
    }
    int t=tb.size();
    for(int i=n-2;i>=0;--i){
        while(tb.size()>t && ((v[i]-v[tb[tb.size()-2]])^(v[tb.back()]-v[tb[tb.size()-2]]))>=0)tb.pop_back();
        tb.push_back(i);
    }
    tb.pop_back();
    vector<pair<int,int>> r;
    for(int i:tb)r.push_back(v[i]);
    // cout<<"tb: "; for(int i:tb)cout<<i<<" "; cout<<endl;
    sort(r.begin(),r.end());
    // cout<<"point in convex: "; for(auto p:r)cout<<"("<<p.first<<","<<p.second<<") "; cout<<endl;
    return r;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    vector<pair<int, int>> v(n);
    for(int i=0;i<n;++i){
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(),v.end());
    // cout<<"v: "; for(auto p:v)cout<<"("<<p.first<<","<<p.second<<") "; cout<<endl;
    v.resize(unique(v.begin(),v.end())-v.begin());
    // cout<<"v: "; for(auto p:v)cout<<"("<<p.first<<","<<p.second<<") "; cout<<endl;
    long long ans = rotatingSweepLine(tubao(v));
    cout<<ans/2<<"."<<(ans&1?"5":"0")<<endl;
}
