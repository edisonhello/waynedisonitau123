#include<bits/stdc++.h>
using namespace std;

const double eps=1e-11;

struct point{
    double x,y;
    point()=default;
    point(double x,double y):x(x),y(y){}
} p[1005];

point operator+(const point a,const point b){ return point(a.x+b.x,a.y+b.y); }
point operator-(const point a,const point b){ return point(a.x-b.x,a.y-b.y); }
point operator*(const point a,const double b){ return point(a.x*b,a.y*b); }
point operator/(const point a,const double b){ return point(a.x/b,a.y/b); }
bool operator==(const point a,const point b){ return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps; }
double abs(point p){ return sqrt(p.x*p.x+p.y*p.y); }

bool operator<(const point a,const point b){ return abs(a.x-b.x)<eps?(abs(a.y-b.y)<eps?0:a.y<b.y):a.x<b.x; }

struct line{
    double a,b;
    line()=default;
    line(double a,double b):a(a),b(b){}
} rec[1005][1005];

bool operator<(const line a,const line b){ return abs(a.a-b.a)<eps?(abs(a.b-b.b)<eps?0:a.b<b.b):a.a<b.a; }

map<line,int> mp,cl;
map<point,int> mpp;

int _rev[1000005];


int main(){
    for(int i=2;i<=1000;++i)_rev[i*(i-1)/2]=i;
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=0;i<n;++i)cin>>p[i].x>>p[i].y;
    sort(p,p+n);
    p[n]=point(1e12,1e12);
    int ans=n-1;
    
    // for(int i=0;i<n;++i)cout<<"point "<<i<<" p: "<<p[i].x<<" "<<p[i].y<<endl;

    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            // cout<<"i j "<<i<<" "<<j<<endl;
            point vec=p[j]-p[i];
            point mid=p[i]+vec/2;
            point nor(-vec.y,vec.x);
            point p1=mid;
            point p2=mid+nor;
            /* cout<<"vec: "<<vec.x<<" "<<vec.y<<endl;
            cout<<"mid: "<<mid.x<<" "<<mid.y<<endl;
            cout<<"nor: "<<nor.x<<" "<<nor.y<<endl;
            cout<<"p1 : "<<p1.x<<" "<<p1.y<<endl;
            cout<<"p2 : "<<p2.x<<" "<<p2.y<<endl; */
            double dt=p1.x*p2.y-p1.y*p2.x;
            double dta=p2.y-p1.y;
            double dtb=p1.x-p2.x;
            // cout<<"dt dta dtb "<<dt<<" "<<dta<<" "<<dtb<<endl;
            if(abs(dt)<eps){
                double dy=p2.y-p1.y;
                double dx=p2.x-p1.x;
                if(abs(dx)<eps)dx=0,dy=1;
                if(abs(dy)<eps)dx=1,dy=0;
                if(abs(dx)<eps)rec[i][j]=line(1e15,1e15);
                else rec[i][j]=line(1e15,dy/dx);
            }
            else{
                rec[i][j]=line(dta/dt,dtb/dt);
            }
            // cout<<"i j rec[i][j] "<<i<<" "<<j<<" "<<rec[i][j].a<<" "<<rec[i][j].b<<endl;
            mp[rec[i][j]]+=2;
            p1=p[j]; p2=p[i];
            dt=p1.x*p2.y-p1.y*p2.x;
            dta=p2.y-p1.y;
            dtb=p1.x-p2.x;
            if(abs(dt)<eps){
                double dy=p2.y-p1.y;
                double dx=p2.x-p1.x;
                if(abs(dx)<eps)dx=0,dy=1;
                if(abs(dy)<eps)dx=1,dy=0;
                if(abs(dx)<eps)++cl[line(1e15,1e15)];
                else ++cl[line(1e15,dy/dx)];
            }
            else{
                ++cl[line(dta/dt,dtb/dt)];
            }
        }
    }
    for(int i=0;i<n;++i){
        vector<int> o;
        for(int j=0;j<n;++j)if(i!=j)o.push_back(j);
        sort(o.begin(),o.end(),[&](const int a,const int b){ return abs(p[i]-p[a])<abs(p[i]-p[b]); });
        set<line> added;
        for(int j=0,jj;j<int(o.size());j=jj){
            for(jj=j+1;jj<int(o.size()) && abs(abs(p[o[jj]]-p[i])-abs(p[o[j]]-p[i]))<eps;++jj);
            int L=j,R=jj;
            for(int i=L;i<R;++i)for(int j=i+1;j<R;++j){
                int ii=o[i],jj=o[j];
                if(ii>jj)swap(ii,jj);
                if(added.count(rec[ii][jj]))continue;
                added.insert(rec[ii][jj]);
                ++mp[rec[ii][jj]];
            }
        }
    }
    for(auto &p:mp)ans=min(ans,n-p.second);
    for(auto &p:cl)ans=min(ans,n-_rev[p.second]);
    // for(auto &p:mp)cout<<p.first.a<<" "<<p.first.b<<" : "<<p.second<<endl;

    // cout<<"mid ans: "<<ans<<endl;

    set<point> added;
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            point mid=(p[i]+p[j])/2;
            mpp[mid]+=2;
            if((*lower_bound(p,p+n,mid))==mid && !added.count(mid)){
                mpp[mid]+=1;
                added.insert(mid);
            }
        }
    }
    for(auto &p:mpp)ans=min(ans,n-p.second);

    cout<<ans<<endl;
}
