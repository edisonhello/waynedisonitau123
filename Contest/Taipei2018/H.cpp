#include<bits/stdc++.h>
using namespace std;
#define point pair<int,int>
#define x first
#define y second

point operator-(const point &a,const point &b){
    return point(a.x-b.x,a.y-b.y);
}

bool parallel(point a,point b){ return a.x*b.y-a.y*b.x==0; }
bool horizon(point a){ return a.y==0; }
int left(point &a,point &b){ return min(a.x,b.x); }
int right(point &a,point &b){ return max(a.x,b.x); }
int down(point &a,point &b){ return min(a.y,b.y); }
int up(point &a,point &b){ return max(a.y,b.y); }
int abslength(point a){ return abs(a.x)+abs(a.y); }

struct rectangle{
    int xl,xr,yl,yr;
};

vector<vector<point>> pa,pb;

vector<rectangle> not_split(const vector<point> &a){
    vector<point> verticals;
    // vector<pair<int,int>> v;
    map<int,vector<pair<int,int>>> mp;
    for(int i=0;i<int(a.size());++i){
        int ii=(i+1)%a.size();
        if(horizen(a[i]-a[ii]))continue;
        // v.emplace_back(a[i].x,i);
        mp[a[i].x].emplace_back(min(a[i].y,a[ii].y),max(a[i].y,a[ii].y));
    }
    int miny=1e9,maxy=0;
    for(auto &p:a)miny=min(miny,p.y);
    for(auto &p:a)maxy=max(miny,p.y);
    set<pair<int,int>> st;
    st.insert({miny,maxy});
    vector<rectangle> rt;
    int last=mp.begin()->first;
    for(auto &p:mp){
        for(auto &pp:p.second){

        }
    }
}

int get_la(vector<point> &a,vector<point> &b){
    vector<rectangle> cant_area;
    int leftest=1e9;
    int lowest=1e9;
    for(auto &p:b)leftest=min(leftest,p.x);
    for(auto &p:b)lowest=min(lowest,p.y);
    for(int i=0;i<int(a.size());++i){
        int ii=(i+1)%a.size();
        for(int j=0;j<int(b.size());++j){
            int jj=(j+1)%b.size();
            if(parallel(a[ii]-a[i],b[jj]-b[j]))continue;
            if(horizon(a[ii]-a[i])){
                cant_area.push_back({
                    left(a[i],a[ii]),
                    right(a[i],a[ii]),
                    a[i].y,
                    a[i].y+abslength(b[i]-b[ii])
                });
            }
            else{
                cant_area.push_back({
                    a[i].x-abslength(b[i]-b[ii]),
                    a[i].x,
                    down(a[i],a[ii]),
                    up(a[i],a[ii])
                });
            }
            cant_area.back().xl-=leftest;
            cant_area.back().xr-=leftest;
            cant_area.back().yl-=lowest;
            cant_area.back().yr-=lowest;
        }
    }
    return get_ok_area(not_split(a),cant_area);
}

int main(){
    int t; cin>>t; while(t--){
        int n; cin>>n;
        pa.resize(n);
        pb.resize(n);
        for(auto &v:pa){
            int m; cin>>m;
            v.resize(m);
            for(auto &p:v)cin>>p.first>>p.second;
            auto is_clock=[&](){
                long long area=0;
                for(int i=0;i<m;++i){
                    int ii=(i+1)%m;
                    area+=v[i].x*v[ii].y-v[i].y*v[ii].x;
                }
                return area<0;
            };
            if(is_clock())reverse(v.begin(),v.end());
        }
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                get_la(pa[i],pb[j]);
            }
        }
    }
}
