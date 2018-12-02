

#include<bits/stdc++.h>
using namespace std;

int main(){
    int a[3],w[2]; cin>>a[0]>>a[1]>>a[2]>>w[0]>>w[1];
    sort(a,a+3);
    do{
        sort(w,w+2);
        do{
            bool ok=0;
            if(a[0]+a[2]+a[2]<=w[0] && (a[1]+a[2])*2<=w[1])ok=1;
            if((a[1]+a[2])*2<=w[0] && a[0]+a[1]+a[2]<=w[1])ok=1;
            if(a[0]+a[1]+a[2]<=w[0] && a[0]+a[1]+a[2]+a[1]<=w[1])ok=1;
            if(a[1]+a[2]+a[0]+a[2]<=w[0] && a[1]+a[2]+a[0]<=w[1])ok=1;
            if(a[0]+a[1]+a[0]+a[2]+a[0]<=w[0] && a[1]+a[2]<=w[1])ok=1;
            if(a[0]+a[1]+a[2]<=w[0] && a[0]+a[2]+a[1]+a[0]<=w[1])ok=1;
            if(a[0]+a[2]+a[1]+a[0]<=w[0] && a[2]+a[1]+a[2]<=w[1])ok=1;
            if(ok){
                cout<<"Yes"<<endl;
                exit(0);
            }
        }while(next_permutation(w,w+2));
    }while(next_permutation(a,a+3));
    cout<<"No"<<endl;
}
