#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long

int main(){
    ull a[3],n; cin>>a[0]>>a[1]>>a[2]>>n;
    ull R=(n&1?(n-1)*(n+1)/4:(n - 4 + n / 2 * (n / 2 + 1)));
    sort(a,a+3);
    int sa=0;
    if(a[0]==a[1])++sa;
    if(a[1]==a[2])++sa;
    ull div;
    if(sa==0)div=1;
    if(sa==1)div=2;
    if(sa==2)div=6;
    ull g=__gcd(div,n);
    div/=g, n/=g;
    g=__gcd(div,R);
    div/=g, R/=g;
    cout<<n*R<<endl;
}
