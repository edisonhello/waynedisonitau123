#include<bits/stdc++.h>
using namespace std;

struct point{
    double x,y,z; 
    point(double x=0,double y=0,double z=0): x(x),y(y),z(z){}
};

double abs(point a){ return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }

point operator+(const point a,const point b){ return point(a.x+b.x,a.y+b.y,a.z+b.z); }
point operator-(const point a,const point b){ return point(a.x-b.x,a.y-b.y,a.z-b.z); }

double solve(point c,double r,point a,point b){
    double dab=abs(a-b);
    if(dab<1e-9)return 0;
    double dac=abs(a-c);
    double dbc=abs(b-c);
    double bac=acos((dab*dab+dac*dac-dbc*dbc)/(2*dab*dac));
    double abc=acos((dab*dab+dbc*dbc-dac*dac)/(2*dab*dbc));
    double acb=acos((dac*dac+dbc*dbc-dab*dab)/(2*dac*dbc));
    if(abc>=acos(-1)/2 || bac>=acos(-1)/2)return dab;

    double d_c_ab=dbc*sin(abc);
    if(d_c_ab>=r)return dab;
    double dad=sqrt(dac*dac-r*r);
    double dbe=sqrt(dbc*dbc-r*r);
    double acd=acos((dac*dac+r*r-dad*dad)/(2*dac*r));
    double bce=acos((dbc*dbc+r*r-dbe*dbe)/(2*dbc*r));
    double angle=acos(-1)-acd-bce-bac-abc;
    return dad+dbe+r*angle;
}

int main(){
    int t; cin>>t; while(t--){
        point c;
        double r;
        cin>>c.x>>c.y>>c.z>>r;
        point a,b;
        cin>>a.x>>a.y>>a.z>>b.x>>b.y>>b.z;
        cout<<fixed<<setprecision(12)<<solve(c,r,a,b)<<'\n';
    }
}
