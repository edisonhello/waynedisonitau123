#include<bits/stdc++.h>
using namespace std;



int main(){
    int t; cin>>t; while(t--){
        double a,b; cin>>a>>b;
        if(a==b){ cout<<1<<endl; continue; }
        int u=ceil(log(b/a)/log(1.1)-1e-12);
        // cout<<u<<endl;
        double now=a;
        for(int i=1;;++i){
            if(now>=b){
                cout<<i<<endl;
                break;
            }
            if(i%14==13 || i%14==0)continue;
            if(i%3==1)now*=1.1;
        }

    }
}
