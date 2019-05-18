#include<bits/stdc++.h>
using namespace std;

string s[4005];
vector<int> G[1000006];
int d[1000006];
bitset<1000006> v;

int ijk(int n,int s,int t){
    memset(d,0x3f,n<<2);
    for(int i=0;i<n;++i)v[i]=0;
    d[s]=0;
    queue<int> q; q.push(s); v[s]=1;
    while(q.size()){
        int now=q.front(); q.pop();
        for(int i:G[now]){
            if(!v[i]){
                q.push(i);
                d[i]=d[now]+1;
                v[i]=1;
            }
        }
    }
    /* priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.emplace(0,s);
    while(pq.size()){
        while(pq.size() && v[pq.top().second])pq.pop();
        if(pq.empty())break;
        int now=pq.top().second;
        for(
    } */
    if(d[t]>n)return -2;
    return d[t];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n,m; cin>>n>>m; cin.ignore();
        for(int i=0;i<(4*n+3);++i)getline(cin,s[i]);
        int S,T;
        for(int j=0;j<m;++j){
            for(int i=0;i<n;++i){
                int id=i*m+j;
                int x,y;
#define addedge(x,y) G[x].push_back(y), G[y].push_back(x)
                if(j&1){
                    x=i*4+4,y=j*6+4;
                    if(s[x-1][y+3]==' ')addedge(id,i*m+(j+1));
                    if(s[x+1][y+3]==' ')addedge(id,(i+1)*m+(j+1));
                }
                else{
                    x=i*4+2,y=j*6+4;
                    if(s[x-1][y+3]==' ')addedge(id,(i-1)*m+(j+1));
                    if(s[x+1][y+3]==' ')addedge(id,i*m+(j+1));
                }
                if(s[x][y]=='S')S=id;
                if(s[x][y]=='T')T=id;
                if(s[x+2][y]==' ')addedge(id,(i+1)*m+j);
            }
        }
        cout<<ijk(n*m,S,T)+1<<'\n';
        for(int i=0;i<n*m;++i)G[i].clear();
    }
}
