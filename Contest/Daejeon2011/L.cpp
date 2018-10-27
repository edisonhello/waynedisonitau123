#include<bits/stdc++.h>
using namespace std;

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int main(){
    int t; cin>>t; while(t--){
        string s; cin>>s;
        int x=0,y=0,d=0;
        int mnx=0,mxx=0,mny=0,mxy=0;
        auto up=[&](){
            mnx=min(mnx,x);
            mny=min(mny,y);
            mxx=max(mxx,x);
            mxy=max(mxy,y);
        };
        for(char c:s){
            if(c=='F'){
                x+=dx[d];
                y+=dy[d];
                up();
            }
            else if(c=='L'){
                --d;
                if(d<0)d+=4;
            }
            else if(c=='R'){
                ++d;
                if(d==4)d-=4;
            }
            else{
                x-=dx[d];
                y-=dy[d];
                up();
            }
        }
        cout<<(mxx-mnx)*(mxy-mny)<<endl;
    }
}
