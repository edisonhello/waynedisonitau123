#include<bits/stdc++.h>
using namespace std;
#define double long double

const double eps=1e-15;

bool same(const double a,const double b){ return abs(a-b)<eps; }
struct Point{
    double x,y; 
    Point():x(0),y(0){}
    Point(double x,double y):x(x),y(y){}
    void norm(){
        double len=sqrt(x*x+y*y);
        x/=len, y/=len;
    }
};
Point operator+(const Point a,const Point b){ return Point(a.x+b.x,a.y+b.y); }
Point operator-(const Point a,const Point b){ return Point(a.x-b.x,a.y-b.y); }
Point operator*(const Point a,const double b){ return Point(a.x*b,a.y*b); }
Point operator/(const Point a,const double b){ return Point(a.x/b,a.y/b); }
double operator^(const Point a,const Point b){ return a.x*b.y-a.y*b.x; }
double abs(const Point a){ return sqrt(a.x*a.x+a.y*a.y); }

struct Line{
    double a,b,c,angle;
    Point pa,pb;
    Line() = default;
    Line(Point pa,Point pb):a(pa.y-pb.y),b(pb.x-pa.x),c(pa^pb),angle(atan2(-a,b)),pa(pa),pb(pb){}
};

bool smaller;

Point intersect(Line la,Line lb,int getans=0){
    if(same(la.a*lb.b,la.b*lb.a)){ smaller=1; return Point(7122,7122); }
    double bot=-la.a*lb.b+la.b*lb.a;
    return Point(-la.b*lb.c+la.c*lb.b,la.a*lb.c-la.c*lb.a)/bot;
}

bool jizz(Line l1,Line l2,Line l3){
    Point p=intersect(l2,l3);
    return ((l1.pb-l1.pa)^(p-l1.pa))<-eps;
}

bool cmp(const Line &a,const Line &b){
    return same(a.angle,b.angle)?(((b.pb-b.pa)^(a.pb-b.pa))>eps):a.angle<b.angle;
}

vector<Point> HPI(vector<Line> &ls){
    smaller=0;
    sort(ls.begin(),ls.end(),cmp);
    vector<Line> pls(1,ls[0]);
    for(int i=0;i<int(ls.size());++i)if(!same(ls[i].angle,pls.back().angle))pls.push_back(ls[i]);
    deque<int> dq; dq.push_back(0); dq.push_back(1);
    for(int i=2;i<int(pls.size());++i){
        while(dq.size()>1u && jizz(pls[i],pls[dq.back()],pls[dq[dq.size()-2]]))dq.pop_back();
        while(dq.size()>1u && jizz(pls[i],pls[dq[0]],pls[dq[1]]))dq.pop_front();
        dq.push_back(i);
    }
    while(dq.size()>1u && jizz(pls[dq.front()],pls[dq.back()],pls[dq[dq.size()-2]]))dq.pop_back();
    while(dq.size()>1u && jizz(pls[dq.back()],pls[dq[0]],pls[dq[1]]))dq.pop_front();
    if(dq.size()<3u || smaller)return vector<Point>();
    vector<Point> rt;

    for(int i=0;i<(int)dq.size();++i){
        rt.push_back(intersect(pls[dq[i]],pls[dq[(i+1)%dq.size()]],1));
    }
    return rt;
}

int n;
Point p[222];

bool ok(double r){
    vector<Line> ls;
    for(int i=0;i<n;++i){
        Point nx=p[(i+1)%n];
        Point dir=nx-p[i];
        swap(dir.x,dir.y); dir.x*=-1;
        dir.norm();
        dir=dir*r;
        Line l(p[i]+dir,p[(i+1)%n]+dir);
        ls.push_back(l);
    }
    auto res=HPI(ls);
    if(res.size()<2u)return 0;
    for(auto p1:res)for(auto p2:res){
        if(abs(p1-p2)>2*r)return 1;
    }
    return 0;
}

void getans(double r){
    vector<Line> ls;
    for(int i=0;i<n;++i){
        Point nx=p[(i+1)%n];
        Point dir=nx-p[i];
        swap(dir.x,dir.y); dir.x*=-1;
        dir.norm();
        dir=dir*r;
        Line l(p[i]+dir,p[(i+1)%n]+dir);
        ls.push_back(l);
    }
    auto res=HPI(ls);
    for(auto p1:res)for(auto p2:res){
        if(abs(p1-p2)>2*r){
            cout<<fixed<<setprecision(30);
            cout<<r<<endl;
            cout<<p1.x<<" "<<p1.y<<endl;
            cout<<p2.x<<" "<<p2.y<<endl;
            return;
        }
    }
    assert(false);
}
int main(){
#ifdef ONLINE_JUDGE
    freopen("kabbalah.in", "r", stdin);
    freopen("kabbalah.out", "w", stdout);
#endif
    while(cin>>n,n){
        for(int i=0;i<n;++i)cin>>p[i].x>>p[i].y;
        double L=0,R=10000000;
        int it=200;
        while(it--){
            double M=(L+R)/2;
            if(ok(M))L=M;
            else R=M;
        }
        getans(L);
    }
}
