#include<bits/stdc++.h>
using namespace std;

const int inf=1000000000;

string s[55];
bool v[55][55][55][55];
int dp[55][55][55][55];

vector<pair<int,int>> to[26];

#define in(a,b,c) (((a)<=(b))&&((b)<=(c)))

int dfs(int x1,int y1,int x2,int y2){
    if(x2<x1 || y2<y1)return -inf;
    if(s[x1][y1]=='#' || s[x2][y2]=='#')return -inf;
    if(x1==x2 && y1==y2)return 0;
    if(abs(x1-x2)+abs(y1-y2)==1 && s[x1][y1]-'a'==s[x2][y2]-'A')return 1;
    if(abs(x1-x2)+abs(y1-y2)==1)return 0;
    if(v[x1][y1][x2][y2])return dp[x1][y1][x2][y2];
    v[x1][y1][x2][y2]=1;
    int &v=dp[x1][y1][x2][y2]; v=-inf;
    if(s[x1][y1]>='a' && s[x1][y1]<='z'){
        for(auto &p:to[s[x1][y1]-'a']){
            if(in(x1,p.first,x2) && in(y1,p.second,y2)); else continue;
            if(p==make_pair(x2,y2)){
//                 cout<<"can match to "<<p.first<<" "<<p.second<<endl;
                v=max(v,1+dfs(x1+1,y1,x2-1,y2));
                v=max(v,1+dfs(x1+1,y1,x2,y2-1));
                v=max(v,1+dfs(x1,y1+1,x2-1,y2));
                v=max(v,1+dfs(x1,y1+1,x2,y2-1));
            }
            v=max(v,dfs(x1,y1,p.first,p.second)+dfs(p.first,p.second,x2,y2));
        }
    }
    v=max(v,dfs(x1+1,y1,x2,y2));
    v=max(v,dfs(x1,y1+1,x2,y2));
//     cout<<"dfs "<<x1<<" "<<y1<<" to "<<x2<<" "<<y2<<" : "<<v<<endl;
    return v;
}

int main(){
    int n,m; while(cin>>n>>m){
        if(n|m); else break;
        for(int i=0;i<26;++i)to[i].clear();
        for(int i=0;i<n;++i)cin>>s[i];
        memset(v,0,sizeof(v));
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            if(s[i][j]>='A' && s[i][j]<='Z')to[s[i][j]-'A'].emplace_back(i,j);
        }
        int r=dfs(0,0,n-1,m-1);
        if(r<0)r=-1;
        cout<<r<<'\n';
    }
}
