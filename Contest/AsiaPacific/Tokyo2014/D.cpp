

#include<bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

pair<int,int> ob[12]; // pos, hei

int main(){
    int d,n,b; cin>>d>>n>>b; ++b;
    for(int i=0;i<n;++i)cin>>ob[i].first>>ob[i].second;
    double v=1e9;
    for(int i=1;i<=b;++i){
        double once = double(d) / i;
        double L=PI/4, R=PI/2-1e-6;
        int cnt=100;
        while(cnt--){
            double theta = (L+R)/2;
            bool ok = 1;
            for(int i=0;i<n;++i){
                double d = ob[i].first - floor(double(ob[i].first) / once) * once;
                if(d > once/2) d = once - d;
                // cout<<"d: "<<d<<endl;
                double vx = sqrt(once / 2 / tan(theta));
                double vy = vx * tan(theta);
                double y = -(1.0 / (2 * vx * vx)) * d * d + vy / vx * d;
                // cout<<"y: "<<y<<endl;
                if(y < ob[i].second){ ok=0; break; }
            }
            if (ok) R = theta;
            else L = theta;
        }
        double vx = sqrt(once / 2 / tan(L));
        double vy = vx * tan(L);
        v = min(v, hypot(vx,vy));
        // cout<<"L: "<<L<<endl;
    }
    cout<<fixed<<setprecision(20)<<v<<endl;
}
