#include<bits/stdc++.h>
using namespace std;
#define count sdghokerw

int ans;

bitset<9> vis[9];
// bitset<81> vis;

string mp[9];

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

#define ins(x,y) ((x)>=0 && (x)<9 && (y)>=0 && (y)<9)


unordered_set<unsigned long long> st;

unsigned long long hh(){
    unsigned long long rt=0,base=7902131;
    for(int i=0;i<9;++i)for(int j=0;j<9;++j)rt+=base*int(vis[i][j]),base*=7902131;
    return rt;
}

// int count=0;
void dfs(int nx,int ny,int dep){
    // cout<<"dfs: "<<nx<<" "<<ny<<" "<<deo<<" "<<count<<endl;
    if(mp[nx][ny]=='D'){ ans=max(ans,dep); return; }
    // if(count>=1000000)return;
    // ++count;

    vis[nx][ny]=1;
    // vis[nx*9+ny]=1;
    if(st.find(hh())!=st.end()){
        vis[nx][ny]=0;
        return;
    }
    // st.insert(hh(vis));
    for(int i=0;i<4;++i){
        // if(ins(nx+dx[i],ny+dy[i]) && !vis[(nx+dx[i])*9+ny+dy[i]] && mp[nx+dx[i]][ny+dy[i]]!='X'){
        if(ins(nx+dx[i],ny+dy[i]) && !vis[nx+dx[i]][ny+dy[i]] && mp[nx+dx[i]][ny+dy[i]]!='X'){
            dfs(nx+dx[i],ny+dy[i],dep+1);
        }
    }
    // vis[nx*9+ny]=0;
    vis[nx][ny]=0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts=3; while(ts--){
        // ans=count=0;
        ans=-1;
        for(int i=0;i<9;++i)vis[i].reset();
        // vis.reset();
        for(int i=0;i<9;++i)cin>>mp[i];
        int sx,sy;
        for(int i=0;i<9;++i)for(int j=0;j<9;++j)if(mp[i][j]=='S')sx=i,sy=j;
        dfs(sx,sy,1);
        cout<<ans<<endl;
    }
}
