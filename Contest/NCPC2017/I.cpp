#include<bits/stdc++.h>
using namespace std;

bool same(const double a,const double b){ return abs(a-b)<1e-9; }

struct Point{
    double x,y;
    Point():x(0),y(0){}
    Point(double x,double y):x(x),y(y){}
};
Point operator+(const Point a,const Point b){ return Point(a.x+b.x,a.y+b.y); }
Point operator-(const Point a,const Point b){ return Point(a.x-b.x,a.y-b.y); }
Point operator*(const Point a,const double b){ return Point(a.x*b,a.y*b); }
Point operator/(const Point a,const double b){ return Point(a.x/b,a.y/b); }
double operator^(const Point a,const Point b){ return a.x*b.y-a.y*b.x; }
double abs(const Point a){ return sqrt(a.x*a.x+a.y*a.y); }
ostream& operator<<(ostream &o,const Point p){ o<<"("<<p.x<<","<<p.y<<")"; return o; }

struct Line{
    double a,b,c;
    double angle;
    Point pa,pb;
    Line():a(0),b(0),c(0),angle(0),pa(),pb(){}
    Line(Point pa,Point pb):a(pa.y-pb.y),b(pb.x-pa.x),c(pa^pb),angle(atan2(-a,b)),pa(pa),pb(pb){}
};

Point intersect(Line la,Line lb){
    double bot=-la.a*lb.b+la.b*lb.a;
    return Point(-la.b*lb.c+la.c*lb.b,la.a*lb.c-la.c*lb.a)/bot;
}

bool jizz(Line l1,Line l2,Line l3){
    Point p=intersect(l2,l3);
    return ((l1.pb-l1.pa)^(p-l1.pa))<-1e-9;
}

bool cmp(const Line &a,const Line &b){
    return same(a.angle,b.angle)?(((b.pb-b.pa)^(a.pb-b.pa))>1e-9):a.angle<b.angle;
}

vector<Point> HPI(vector<Line> &ls){
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
    if(dq.size()<3u)return vector<Point>();
    vector<Point> rt;
    for(int i=0;i<int(dq.size());++i)rt.push_back(intersect(pls[dq[i]],pls[dq[(i+1)%dq.size()]]));
    return rt;
}

#define line Line
int main(){
    double l,w; int n; double nx,ny; while(cin>>l>>w>>n>>nx>>ny){
        if(same(l,0) && same(w,0) && n==0 && same(nx,0) && same(ny,0))break;
        vector<Line> hpils;
        hpils.push_back(line(Point(0,0),Point(w,0)));
        hpils.push_back(line(Point(w,0),Point(w,l)));
        hpils.push_back(line(Point(w,l),Point(0,l)));
        hpils.push_back(line(Point(0,l),Point(0,0)));
        Point np(nx,ny);
        for(int i=0;i<n;++i){
            Point p; cin>>p.x>>p.y;
            Point vec=p-np;
            vec=Point(-vec.y,vec.x);
            Point mid=(p+np)/2;
            hpils.push_back(Line(Point(mid-vec),Point(mid+vec)));
        }
        // cout<<"before hpi"<<endl;
        vector<Point> ps=HPI(hpils);
        // cout<<"after hpi"<<endl;
        // for(Point p:ps)cout<<p<<" "; cout<<endl;
        double area=0;
        for(int i=0;i<int(ps.size());++i){
            Point vp=(i?ps[i-1]:ps.back());
            area+=(vp^ps[i]);
        }
        area/=2;
        cout<<(long long)round(area)<<endl;
    }
}
