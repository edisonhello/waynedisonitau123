#include<bits/stdc++.h>
using namespace std;

#define point pair<long long,long long>
#define x first
#define y second

point pt[500005],pt2[500005];
int out[500005];

point operator-(const point &a,const point &b){ return point(a.x-b.x,a.y-b.y); }
long long operator^(const point &a,const point &b){ return a.x*b.y-a.y*b.x; }

vector<int> convex(point *p,int n){
    vector<int> tb;
    for(int i=0;i<n;++i){
        while(tb.size()>1 && ((p[i]-p[tb.back()])^(p[tb[tb.size()-2]]-p[tb.back()]))>0)tb.pop_back();
        tb.push_back(i);
    }
    int t=tb.size();
    for(int i=n-2;i>=0;--i){
        while(tb.size()>t && ((p[i]-p[tb.back()])^(p[tb[tb.size()-2]]-p[tb.back()]))>0)tb.pop_back();
        tb.push_back(i);
    }
    if(tb.size()>1u)tb.pop_back();
    return tb;
}
vector<int> convex_(point *p,int n){
    vector<int> tb;
    for(int i=0;i<n;++i){
        while(tb.size()>1 && ((p[i]-p[tb.back()])^(p[tb[tb.size()-2]]-p[tb.back()]))>=0)tb.pop_back();
        tb.push_back(i);
    }
    int t=tb.size();
    for(int i=n-2;i>=0;--i){
        while(tb.size()>t && ((p[i]-p[tb.back()])^(p[tb[tb.size()-2]]-p[tb.back()]))>=0)tb.pop_back();
        tb.push_back(i);
    }
    if(tb.size()>1u)tb.pop_back();
    return tb;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=0;i<n;++i)cin>>pt[i].x>>pt[i].y;
    sort(pt,pt+n);
    vector<int> tb=convex(pt,n);
    // cout<<"tb: "; for(int i:tb)cout<<i<<" "; cout<<endl;
    for(int i:tb)out[i]=1;
    tb=convex(pt,n);
    // cout<<"tb: "; for(int i:tb)cout<<i<<" "; cout<<endl;
    int m=0;
    for(int i=0;i<n;++i)if(!out[i]){
        pt2[m++]=pt[i];
    }
    if(m==0){ exit((cout<<-1<<endl,0)); }
    vector<int> tb2=convex_(pt2,m);
    long long area=0;
    for(int i=0;i<int(tb.size());++i){
        int j=(i==int(tb.size())-1)?0:i+1;
        int pi=tb[i],pj=tb[j];
        area+=pt[pi].x*pt[pj].y-pt[pi].y*pt[pj].x;
    }
    area=abs(area);
    // cout<<"big area: "<<area<<endl;
    long long sub=1e18;
    auto calc=[&](int a,int b,int c){
        // cout<<"calc "<<a<<" "<<b<<" "<<c<<endl;
        long long rt=abs((pt[tb[a]]-pt[tb[b]])^(pt2[tb2[c]]-pt[tb[b]]));
        // cout<<"rt: "<<rt<<endl;
        sub=min(sub,rt);
        return rt;
    };
    int j=0;
    for(int jj=0;jj<int(tb2.size());++jj){
        if(calc(0,1,jj)<=sub){
            j=jj;
            sub=calc(0,1,jj);
        }
    }
    for(int i=1;i<int(tb.size());++i){
        int i2=(i+1)%tb.size();
        while(calc(i,i2,(j+1)%tb2.size()) < calc(i,i2,j) && (j+1)%tb2.size()!=j)j=(j+1)%tb2.size();
    }
    /* for(int i=0;i<int(tb.size());++i){
        for(int z=0;z<int(tb2.size());++z){
            int j=(i==int(tb.size())-1)?0:i+1;
            int pi=tb[i],pj=tb[j],pz=tb2[z];
            // cout<<pi<<" "<<pj<<" "<<pz<<endl;
            // cout<<"sub update with "<<abs((pt[pi]-pt[pj])^(pt2[pz]-pt[pj]))<<endl;
            sub=min(sub,abs((pt[pi]-pt[pj])^(pt2[pz]-pt[pj])));
        }
    } */
    area-=sub;
    cout<<area<<endl;

}
