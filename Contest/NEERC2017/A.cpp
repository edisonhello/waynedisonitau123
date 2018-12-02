

#include<bits/stdc++.h>
using namespace std;

pair<int,int> cc[200005];

unordered_map<long long,vector<int>> ccs[35];

#define sq(x) (1ll*(x)*(x))
bool inside(int id,int x,int y){
    return sq(cc[id].first-x)+sq(cc[id].second-y)<sq(cc[id].second);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        int c; cin>>c; 
        if(c==1){
            int x,y; cin>>x>>y;
            int lev=0;
            while((1<<lev)<=y)++lev; --lev;
            cc[i]=make_pair(x,y);
            x/=(1<<lev);
            y/=(1<<lev);
            ccs[lev][x*2000000000ll+y].push_back(i);
        }
        else{
            int x,y; cin>>x>>y;
            int mr=(y+1)>>1;
            int lev=0;
            while((1<<lev)<=mr)++lev; --lev; --lev; lev=max(lev,0);
            bool got=0;
            for(;lev<31;++lev){
                int cx=x/(1<<lev);
                int cy=y/(1<<lev);
                for(int xxx=cx-2;xxx<=cx+2;++xxx){
                    for(int yyy=cy-2;yyy<=cy+2;++yyy){
                        long long id=xxx*2000000000ll+yyy;
                        if(ccs[lev].find(id)==ccs[lev].end())continue;
                        vector<int> &v=ccs[lev][id];
                        for(int z=0;z<(int)v.size();++z){
                            if(inside(v[z],x,y)){
                                cout<<v[z]<<'\n';
                                v.erase(v.begin()+z);
                                got=1;
                                break;
                            }
                        }
                        if(got)break;
                    }
                    if(got)break;
                }
                if(got)break;
            }
            if(!got)cout<<-1<<'\n';
        }
    }
}
