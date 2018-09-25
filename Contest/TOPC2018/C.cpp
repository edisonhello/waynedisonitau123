#include<bits/stdc++.h>
using namespace std;
#define double long double

const double pi=acos(-1);

pair<double,double> ray[123];
double px,py;

double dis(double x,double y){
    return sqrt(x*x+y*y);
}

double getangle(double x1,double y1,double x2,double y2){
    double nai=x1*x2+y1*y2;
    double abx=dis(x1,y1),aby=dis(x2,y2);
    double csx=nai/abx/aby;
    double tha=acos(csx);
    return tha;
}

bool oppo(double px,double py,int i){
    return getangle(px,py,ray[i].first,ray[i].second)>=pi/2;
}

void solve(){
    int n;
    cin>>n>>px>>py;
    for(int i=0;i<n;++i)cin>>ray[i].first>>ray[i].second;
    cout<<fixed<<setprecision(10);
    double alpha=getangle(ray[0].first,ray[0].second,ray[n-1].first,ray[n-1].second);
    double r=dis(px,py);
    cout<<2*r*sin(alpha)<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--)solve();
}
