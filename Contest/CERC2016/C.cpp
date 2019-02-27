#include<bits/stdc++.h>
using namespace std;

double ans;

void circle(int d){
    if(!d){
        ans+=acos(-1)/2;
        return;
    }
    // cout<<"circle "<<d<<endl;
    ans+=d+0.5+1;
    double x=d;
    double y=sqrt(3)/2-0.5;
    double t=hypot(x,y);
    double tt=sqrt(t*t-0.25);
    double o=acos((t*t+0.25-tt*tt)/(2*0.5*t));
    o+=acos((t*t+d*d-y*y)/(2*t*d));
    o=acos(-1)/2-o;
    ans+=tt+o*0.5;
}
void square(int d){
    if(!d){
        ans+=2;
        return;
    }
    // cout<<"square "<<d<<endl;
    ans+=d+0.5+1+0.5;
    double x=d-0.5;
    double y=1-sqrt(3)/2;
    ans+=hypot(x,y);
}

int main(){
    int n; cin>>n;
    string s; cin>>s; s=" "+s;
    int L=1,R=n;
    while(L<=n && s[L]=='T')++L;
    while(R>=1 && s[R]=='T')--R;
    if(R<L){ // all triangle
        ans+=n;
        ans+=n-1;
        ans+=2;
    }
    else{
        ans+=(R-L)*2;
        if(s[L]=='C')circle(L-1);
        else square(L-1);
        if(s[R]=='C')circle(n-R);
        else square(n-R);
    }
    cout<<fixed<<setprecision(20)<<ans<<endl;
}
