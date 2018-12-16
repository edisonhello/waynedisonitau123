#include<bits/stdc++.h>
using namespace std;

string s[22];
bitset<22> vis[22];

int dis[22][22];
int cf[22][22];

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int main(){
    int n,m; cin>>n>>m;
    for(int i=0;i<n;++i)cin>>s[i];
    vector<pair<int,int>> at;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(s[i][j]=='1')at.emplace_back(i,j);
        }
    }
    string ans;
    auto go=[&](int d){
        if(d==0)ans+="D";
        else if(d==1)ans+="R";
        else if(d==2)ans+="U";
        else ans+="L";
        for(auto &p:at){
            auto zz=p;
            zz.first+=dx[d];
            zz.second+=dy[d];
            if(zz.first<0 || zz.first>=n || zz.second<0 || zz.second>=m)continue;
            else if(s[zz.first][zz.second]=='0')continue;
            else p=zz;
        }
    };
    while(at.size()>1u){
        for(int i=0;i<22;++i)vis[i].reset();
        memset(dis,0,sizeof(dis));
        memset(cf,0xff,sizeof(cf));
        queue<pair<int,int>> q;
        q.emplace(at[0]); vis[at[0].first][at[0].second]=1;
        while(q.size()){
            auto now=q.front(); q.pop();
            for(int d=0;d<4;++d){
                int nx=now.first+dx[d];
                int ny=now.second+dy[d];
                if(nx<0 || nx>=n || ny<0 || ny>=m)continue;
                if(s[nx][ny]=='0')continue;
                if(vis[nx][ny])continue;
                q.emplace(nx,ny);
                vis[nx][ny]=1;
                dis[nx][ny]=dis[now.first][now.second]+1;
                cf[nx][ny]=(d+2)&3;
            }
        }
        int fari=0;
        for(int i=1;i<int(at.size());++i){
            if(dis[at[i].first][at[i].second]>dis[at[fari].first][at[fari].second]){
                fari=i;
            }
        }
        while(at[0]!=at[fari]){
            // cout<<at[fari].first<<" "<<at[fari].second<<" to "<<at[0].first<<" "<<at[0].second<<endl;
            while(cf[at[fari].first][at[fari].second]!=-1){
                go(cf[at[fari].first][at[fari].second]);
                // cout<<"now fari: "<<at[fari].first<<" "<<at[fari].second<<endl;
            }
            if(at[0]==at[fari])break;
            {
                for(int i=0;i<22;++i)vis[i].reset();
                memset(dis,0,sizeof(dis));
                memset(cf,0xff,sizeof(cf));
                queue<pair<int,int>> q;
                q.emplace(at[0]); vis[at[0].first][at[0].second]=1;
                while(q.size()){
                    auto now=q.front(); q.pop();
                    for(int d=0;d<4;++d){
                        int nx=now.first+dx[d];
                        int ny=now.second+dy[d];
                        if(nx<0 || nx>=n || ny<0 || ny>=m)continue;
                        if(s[nx][ny]=='0')continue;
                        if(vis[nx][ny])continue;
                        q.emplace(nx,ny);
                        vis[nx][ny]=1;
                        dis[nx][ny]=dis[now.first][now.second]+1;
                        cf[nx][ny]=(d+2)&3;
                    }
                }
            }
        }
        sort(at.begin(),at.end());
        at.resize(unique(at.begin(),at.end())-at.begin());
    }
    cout<<ans<<endl;
}
