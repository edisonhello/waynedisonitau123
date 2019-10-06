#include<bits/stdc++.h>
using namespace std;


int main(){
    freopen("kotlin.in","r",stdin);
    freopen("kotlin.out","w",stdout);
    int h,w,n; cin>>h>>w>>n;
    int sh=(h+1)/2,sw=(w+1)/2;
    for(int i=1;i<=sh;++i)for(int j=1;j<=sw;++j){
        if(i*j==n){
            for(int x=0;x<h;++x){
                for(int y=0;y<w;++y){
                    bool sh=0;
                    if(x&1)sh=1;
                    if(y&1)sh=1;
                    if(x/2+1>i)sh=1;
                    if(y/2+1>j)sh=1;
                    if(sh)cout<<"#";
                    else cout<<".";
                }
                cout<<endl;
            }
            exit(0);
        }
    }
    cout<<"Impossible"<<endl;
}
