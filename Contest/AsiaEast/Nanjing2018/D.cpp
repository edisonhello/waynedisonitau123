#include<bits/stdc++.h>
using namespace std;

#define sq(x) ((x)*(x))

struct point{
    double x,y,z; 
} p[105];

point operator-(const point a,const point b){ return point{a.x-b.x,a.y-b.y,a.z-b.z}; };
double abs(const point a){ return sqrt(sq(a.x)+sq(a.y)+sq(a.z)); }
point cross(const point a,const point b){ return point{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x}; }

double calc(point a,point b,point c){
    double la=abs(b-c);
    double lb=abs(a-c);
    double lc=abs(a-b);
    double area=abs(cross(c-a,b-a))/2;
    auto gcos=[&](double a,double b,double c){
        return (b*b+c*c-a*a)/(2*b*c);
    };
    if(gcos(la,lb,lc)<0 || gcos(lb,la,lc)<0 || gcos(lc,la,lb)<0)return min(la*lb*lc/4/area,max(max(la/2,lb/2),lc/2));
    else return la*lb*lc/4/area;
}

int main(){
    int n; cin>>n;
    for(int i=0;i<n;++i){
        cin>>p[i].x>>p[i].y>>p[i].z;
    }
    double ans=0;
    for(int i=2;i<n;++i)for(int j=1;j<i;++j)for(int k=0;k<j;++k){
        ans=max(ans,calc(p[i],p[j],p[k]));
    }
    cout<<fixed<<setprecision(20)<<ans<<endl;
}
