#include<bits/stdc++.h>
using namespace std;

double pi=acos(-1);

char mp[50][30];

void init(){
    for(int i=7;i<=43;++i)for(int j=6;j<=24;++j)mp[i][j]=' ';
    for(int j=6;j<=24;++j)for(int i=7+abs(j-15);i<=43-abs(j-15);i+=2)mp[i][j]='.';
    // mp[7][6]='m';
    // mp[8][6]='a';
    // mp[9][6]='p';
}
void print(){
    for(int j=6;j<=24;++j){ for(int i=7;i<=43;++i)cout<<mp[i][j]; cout<<endl; }
}

bool vis[50][30];
int dis[50][30];
vector<pair<int,int>> work;

vector<pair<int,int>> gnei(const pair<int,int> &now){
    vector<pair<int,int>> rt;
    for(auto d:vector<pair<int,int>>{{-1,-1}, {1,-1}, {-2,0}, {2,0}, {-1,1}, {1,1}}){
        if(mp[now.first+d.first][now.second+d.second]=='.' || mp[now.first+d.first][now.second+d.second]=='x'){
            rt.emplace_back(now.first+d.first,now.second+d.second);
        }
    }
    return rt;
}

void cbfs(int x,int y,int w){
    queue<pair<int,int>> q; q.emplace(x,y);
    vis[x][y]=1; dis[x][y]=1; 
    while(q.size()){
        auto now=q.front(); q.pop();
        work.emplace_back(now);
        if(dis[now.first][now.second]==w)continue;
        for(auto p:gnei(now)){
            if(vis[p.first][p.second])continue;
            vis[p.first][p.second]=1;
            dis[p.first][p.second]=dis[now.first][now.second]+1;
            q.emplace(p.first,p.second);
        }
    }
}
void create(){
    int x,y,w; cin>>x>>y>>w; 
    if(x<-20 || x>20 || y<-10 || y>10){ cout<<-1<<"\n"; return; }
    x+=25; y+=15;
    // cout<<x<<" "<<y<<" "<<mp[x][y]<<endl;
    if(mp[x][y]!='.'){ cout<<-1<<"\n"; return; }

    memset(vis,0,sizeof(vis)); 
    work.clear();
    cbfs(x,y,w);
    
    for(auto &p:work){
        if(p.first<5 || p.first>45 || p.second<5 || p.second>25){ cout<<-1<<"\n"; return; }
        if(mp[p.first][p.second]!='.'){ cout<<-1<<"\n"; return; }
    }

    if(int(work.size())!=1+3*w*(w-1)){ cout<<-1<<"\n"; return; }
    for(auto &p:work)mp[p.first][p.second]='x';
    cout<<work.size()<<"\n";
}
set<pair<int,int>> wst;
void condfs(int x,int y){
    // cout<<"mdfs "<<x<<" "<<y<<endl;
    wst.insert({x,y});
    vis[x][y]=1;
    for(auto d:gnei(make_pair(x,y))){
        if(vis[d.first][d.second])continue;
        if(mp[d.first][d.second]!='x')continue;
        condfs(d.first,d.second);
    }
}
void remove(){
    int x,y; cin>>x>>y;
    if(x<-20 || x>20 || y<-10 || y>10){ cout<<-1<<"\n"; return; }
    x+=25; y+=15;
    if(mp[x][y]!='x'){ cout<<-1<<"\n"; return; }
    
    memset(vis,0,sizeof(vis));
    wst.clear();
    condfs(x,y);

    for(auto &p:wst)mp[p.first][p.second]='.';
    cout<<wst.size()<<"\n";
}
void move(){
    int x,y,dir,len; cin>>x>>y>>dir>>len;
    if(x<-20 || x>20 || y<-10 || y>10){ cout<<-1<<"\n"; return; }
    x+=25; y+=15;
    if(mp[x][y]!='x'){ cout<<-1<<"\n"; return; }
    
    memset(vis,0,sizeof(vis));
    wst.clear();
    condfs(x,y);

    int act=0;
    pair<int,int> dd;
    if(dir==0)dd={-1,-1};
    if(dir==1)dd={ 1,-1};
    if(dir==2)dd={ 2, 0};
    if(dir==3)dd={ 1, 1};
    if(dir==4)dd={-1, 1};
    if(dir==5)dd={-2, 0};
    while(1){
        if(len==0)break;
        vector<pair<int,int>> go;
        for(auto &p:wst){
            go.emplace_back(p.first+dd.first,p.second+dd.second);
        }
        bool stop=0;
        for(auto &p:go)if(wst.find(p)==wst.end() && mp[p.first][p.second]!='.')stop=1;
        if(stop)break;
        for(auto &p:wst)mp[p.first][p.second]='.';
        for(auto &p:go)mp[p.first][p.second]='x';
        ++act;
        wst.clear();
        for(auto &p:go)wst.insert(p);
        --len;
    }
    cout<<act<<"\n";
}
void rotate(){
    int x,y,dir; cin>>x>>y>>dir;
    if(x<-20 || x>20 || y<-10 || y>10){ cout<<-1<<"\n"; return; }
    x+=25; y+=15;
    if(mp[x][y]!='x'){ cout<<-1<<"\n"; return; }
    
    memset(vis,0,sizeof(vis));
    wst.clear();
    condfs(x,y);

    vector<pair<int,int>> go;
    double angle=-pi/3;
    if(!dir)angle=pi/3;
    double snx=sin(angle),csx=cos(angle);
    // cout<<"angle: "<<angle<<endl;
    for(auto &p:wst){
        double dx=p.first-x,dy=p.second-y;
        // cout<<dx<<" "<<dy<<" -> ";
        dy*=sqrt(3);
        // cout<<dx<<" "<<dy<<" -> ";
        tie(dx,dy)=make_pair(dx*csx-dy*snx,dx*snx+dy*csx);
        dy/=sqrt(3);
        // cout<<dx<<" "<<dy<<" -> ";
        dx=round(dx+1e-8), dy=round(dy+1e-8);
        // cout<<dx<<" "<<dy<<endl;
        
        go.emplace_back(x+dx,y+dy);
    }
    bool stop=0;
    // cout<<"wst: "; for(auto p:wst)cout<<p.first<<" "<<p.second<<", "; cout<<endl;
    // cout<<"go : "; for(auto p:go)cout<<p.first<<" "<<p.second<<", "; cout<<endl;
    for(auto &p:go){
        if(p.first<5 || p.first>45 || p.second<5 || p.second>25){ stop=1; break; }
        if(wst.find(p)==wst.end() && mp[p.first][p.second]!='.'){ stop=1; break; }
    }
    if(stop){ cout<<-1<<"\n"; return; }
    for(auto &p:wst)mp[p.first][p.second]='.';
    for(auto &p:go)mp[p.first][p.second]='x';
    cout<<wst.size()<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    // print();
    int q; cin>>q; while(q--){
        string s; cin>>s;
        if(s=="Create")create();
        if(s=="Remove")remove();
        if(s=="Move")move();
        if(s=="Rotate")rotate();
        // print();
    }
    print();
}
