#include<bits/stdc++.h>
using namespace std;

#define point pair<double,double>
#define x first 
#define y second

point operator+(const point a,const point b){return point(a.x+b.x,a.y+b.y);}
point operator-(const point a,const point b){return point(a.x-b.x,a.y-b.y);}
point operator*(const point a,const double b){return point(a.x*b,a.y*b);}
point operator/(const point a,const double b){return point(a.x/b,a.y/b);}
double operator*(const point a,const point b){return a.x*b.x+a.y*b.y;}

double abs(point a){return hypot(a.x,a.y);}

point turn(point a,double t){
    double s=sin(t),c=cos(t);
    return point(c*a.x-s*a.y,a.x*s+a.y*c);
}

struct seg{
    point a,b;
    seg(){}
    seg(point a,point b):a(a),b(b){}
};

struct line{
    double a,b,c;
    line(){ a=b=c=0; }
    line(seg x){ 
        double dx=x.b.x-x.a.x,dy=x.b.y-x.a.y;
        c=-dy*x.a.x+dx*x.a.y;
        a=dy,b=-dx;
    }
    double dis(point p){
        return abs(a*p.x+b*p.y+c)/hypot(a,b);
    }
};

bool inmid(seg x,point p){
    point vec=x.b-x.a;
    point vv=p-x.a;
    if(vec*vv<0)return 0;
    vec=x.a-x.b;
    vv=p-x.b;
    if(vec*vv<0)return 0;
    return 1;
}

double segdis(seg x,seg y){
    double rt=1e9;
    rt=min(rt,abs(x.a-y.a));
    rt=min(rt,abs(x.a-y.b));
    rt=min(rt,abs(x.b-y.a));
    rt=min(rt,abs(x.b-y.b));
    line lx=line(x),ly=line(y);
    if(inmid(x,y.a)){ rt=min(rt,lx.dis(y.a)); }
    if(inmid(x,y.b)){ rt=min(rt,lx.dis(y.b)); }
    if(inmid(y,x.a)){ rt=min(rt,ly.dis(x.a)); }
    if(inmid(y,x.b)){ rt=min(rt,ly.dis(x.b)); }
    return rt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int R,l,w; cin>>R>>l>>w;
    int t; cin>>t; while(t--){
        double A,B; cin>>A>>B;
        seg LL=seg(point(-1000,w),point(0,w));
        seg RR=seg(point(l,w),point(1000,w));
        point vec=turn(point(-l,0),-A);
        seg UU=seg(point(l,w)+vec,point(l,w));
        vec=turn(point(-l,0),-B);
        seg DD=seg(point(l,0)+vec,point(l,0));
        // cout<<"segdis(,LL): "<<segdis(UU,LL)<<endl;
        double rr=min(segdis(UU,LL),min(segdis(UU,DD),segdis(RR,DD)))/2;
        cout<<fixed<<setprecision(20)<<min(double(R),rr)<<'\n';
    }
}

// [[c, -s], [s, c]] [x, y]
