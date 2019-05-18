#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        long long n,p,q,i,j; cin>>n>>p>>q>>i>>j;
        long long i1=(q*(q-1)/2*(p-1)+(n-(q+1)*p+q)*(n-(q+1)*p+q-1)/2)*2*i;
        long long i2=((n-p)*(n-p)-(p-1)*q*q-(n-(q+1)*p+q)*(n-(q+1)*p+q))*(i+j);
        long long i3=(n-p)*i;
        long long i4=((p-1)*(n-p-q)+(p-1)*q)*(2*j+1);
        long long i5=p*(p-1)/2*2*j;
        long long i6=p*j;
        long long i7=(n-p)*(i+j);
        cout<<2*(i1+i2+i3+i4+i5+i6+i7)<<endl;
    }
}
