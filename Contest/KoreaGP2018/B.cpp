#include<bits/stdc++.h>
using namespace std;

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int n,m;
string s[55];
vector<int> G[2505],iG[2505],cG[2505],tp,mem[2505];
int bel[2505],cc,star[2505];
bitset<2505> v;

bool inside(int i,int j){
    return i>=0 && i<n && j>=0 && j<m;
}

inline int getid(int i,int j){
    return i*m+j;
}

void walk(int x,int y){
    for(int d=0;d<4;++d){
        int dx=::dx[d],dy=::dy[d];
        int xx=x+dx,yy=y+dy;
        while(inside(xx,yy) && s[xx][yy]!='#')xx+=dx,yy+=dy;
        xx-=dx,yy-=dy;
        if(xx!=x || yy!=y){
            G[getid(x,y)].push_back(getid(xx,yy));
            cout<<x<<" "<<y<<"("<<getid(x,y)<<") can go to "<<xx<<" "<<yy<<"("<<getid(xx,yy)<<")"<<endl;
        }
    }
}

void dfs1(int now){
    cout<<"dfs1: "<<now<<endl;
    v[now]=1;
    for(int i:G[now])if(!v[i])dfs1(i);
    tp.push_back(now);
}

void dfs2(int now,int ccn){
    bel[now]=ccn;
    mem[ccn].push_back(now);
    v[now]=1;
    cout<<"bel["<<now<<"] = "<<ccn<<endl;
    for(int i:iG[now])if(!v[i])dfs2(i,ccn);
}

int dp[2505];
int dfs3(int now){
    if(v[now])return dp[now];
    cout<<"in dfs3 "<<now<<", star = "<<star[now]<<endl;
    for(int i:cG[now]){
        cout<<"in "<<now<<" can go "<<i<<endl;
        dp[now]=max(dp[now],dfs3(i));
    }
    dp[now]+=star[now];
    cout<<"answer of "<<now<<" is "<<dp[now]<<endl;
    return dp[now];
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>s[i];
    }
    int o=-1;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(s[i][j]=='O')o=getid(i,j);
    cout<<"o: "<<o<<endl;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(s[i][j]!='#')walk(i,j);
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)for(int k:G[getid(i,j)])iG[k].push_back(getid(i,j));
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(!v[getid(i,j)])dfs1(getid(i,j));
    reverse(tp.begin(),tp.end());
    v.reset();
    for(int i:tp)if(!v[i])dfs2(i,++cc);
    int totstar=0;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(s[i][j]=='*')++star[bel[getid(i,j)]],++totstar;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)for(int k:G[getid(i,j)])if(bel[k]!=bel[getid(i,j)])cG[bel[getid(i,j)]].push_back(bel[k]);
    v.reset();
    if(dfs3(bel[o])==totstar)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}
