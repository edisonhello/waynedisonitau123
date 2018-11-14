#include<bits/stdc++.h>
#define DEBUG 0
using namespace std;

int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int G[55][55][5];
int pos[55][55][5][12];

int main(){
    int m,x,y,t; cin>>m>>x>>y>>t;
    for(int i=0;i<4;++i)pos[x][y][i][0]=1;
    while(m--){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        if (x1==x2) {
            tie(y1,y2)=make_pair(min(y1,y2),max(y1,y2));
            for(int i=y1;i<y2;++i)G[x1][i][0]=1,G[x1][i+1][2]=1;
        } else {
            tie(x1,x2)=make_pair(min(x1,x2),max(x1,x2));
            for(int i=x1;i<x2;++i)G[i][y1][1]=1,G[i+1][y1][3]=1;
        }
    }
    while(t--){
        if(DEBUG)cout<<"new time"<<endl;
        int dis; char dir; cin>>dis>>dir;
        queue<tuple<int,int,int,int>> q;
        for(int i=0;i<=50;++i){
            for(int j=0;j<=50;++j){
                for(int k=0;k<4;++k){
                    if(pos[i][j][k][0])q.emplace(i,j,k,0);
                }
            }
        }
        while(q.size()){
            int x,y,d,z; tie(x,y,d,z)=q.front(); q.pop();
            if(DEBUG)cout<<"now "<<x<<" "<<y<<" "<<d<<" "<<z<<endl;
            if(z==10)continue;
            vector<int> okd;
            okd.push_back(d);
            if (z) okd.push_back(d==0?3:d-1);
            if (z) okd.push_back(d==3?0:d+1);
            for(int nd:okd){
                if(G[x][y][nd]){
                    if(pos[x+dx[nd]][y+dy[nd]][nd][z+1])continue;
                    if(DEBUG)cout<<"from "<<x<<" "<<y<<" can go to "<<x+dx[nd]<<" "<<y+dy[nd]<<endl;
                    pos[x+dx[nd]][y+dy[nd]][nd][z+1]=1;
                    q.emplace(x+dx[nd],y+dy[nd],nd,z+1);
                }
            }
        }
        for(int i=0;i<=50;++i)for(int j=0;j<=50;++j)for(int k=0;k<4;++k)pos[i][j][k][0]=0;
        int kk=-1;
        if(dir=='N')kk=0;
        else if(dir=='S')kk=2;
        else if(dir=='W')kk=3;
        else kk=1;
        // for(int i=0;i<=50;++i)for(int j=0;j<=50;++j)for(int k=0;k<4;++k)if(k==kk || (G[i][j][kk] && abs(kk-k)!=2))pos[i][j][k][0]=pos[i][j][k][dis];
        for(int i=0;i<=50;++i)for(int j=0;j<=50;++j){
            /* for(int k1=0;k1<4;++k1)for(int k2=0;k2<4;++k2){
                if(abs(k1-k2)==2)continue;
                if(!G[i][j][k2])continue;
            } */
            pos[i][j][(kk+3) % 4][0] = pos[i][j][kk][dis];
            pos[i][j][(kk+1) % 4][0] = pos[i][j][kk][dis];
            pos[i][j][(kk+0) % 4][0] = pos[i][j][kk][dis];

            for (int k = 0; k < 4; ++k) {
                if (abs(k - kk) == 2) continue;
                if (G[i][j][kk]) pos[i][j][kk][0] |= pos[i][j][k][dis];
            }
            /* for(int k=0;k<4;++k){
                if(pos[i][j][k][dis])pos[i][j][k][0]=1;
                if(abs(k-kk)!=2 && pos[i][j][k][dis] && G[i][j][k])pos[i][j][kk][0]=1;
            } */
        }
        for(int i=0;i<=50;++i)for(int j=0;j<=50;++j)for(int k=0;k<4;++k)for(int l=1;l<=10;++l)pos[i][j][k][l]=0;
    }
    vector<pair<int,int>> ans;
    for(int i=0;i<=50;++i)for(int j=0;j<=50;++j)for(int k=0;k<4;++k)if(pos[i][j][k][0])ans.emplace_back(i,j),(DEBUG?cout<<i<<" "<<j<<" "<<k<<endl:cout<<"");
    ans.resize(unique(ans.begin(),ans.end())-ans.begin());
    for(auto &p:ans)cout<<p.first<<" "<<p.second<<'\n';
}
