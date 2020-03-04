#include<bits/stdc++.h>
using namespace std;
#define sq(x) ((x)*(x))

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        double a,b,r,d; cin>>a>>b>>r>>d;
        d/=360; d*=2*acos(-1);
        double ans=0;
        {
            double theta=atan2(b,a+r);
            if(d>=theta){
                ans=max(ans,sqrt(sq(a+r)+sq(b))-r);
            }
            else{
                ans=max(ans,(sqrt(sq(a+r)+sq(b))*cos(d-theta))-r);
            }
        }
        {
            double theta=atan2(b,r);
            if(d>=theta){
                ans=max(ans,sqrt(sq(r)+sq(b))-r);
            }
            else{
                ans=max(ans,(sqrt(sq(r)+sq(b))*cos(d-theta))-r);
            }
        }
        cout<<fixed<<setprecision(10)<<ans<<endl;
    }
}
