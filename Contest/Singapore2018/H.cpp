#include<bits/stdc++.h>
using namespace std;


pair<int,int> pos[400005];
set<int> pxy[400005],pyx[400005];
map<pair<int,int>,int> poss;
int sons[400005];
int pa[400005],paway[400005];

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

void dfs(int now,int cf){
    // cerr<<"now: "<<now<<endl;
    for(int i=0;i<4;++i){
        if(i==cf)continue;
        int nx=pos[now].first+dx[i];
        int ny=pos[now].second+dy[i];
        auto it=poss.find(make_pair(nx,ny));
        if(it==poss.end())continue;
        int sid=it->second;
        ++sons[now];
        pa[sid]=now;
        paway[sid]=(i+2)&3;
        dfs(sid,(i+2)&3);
    }
}

bitset<400005> inque;

int main(){
    ios_base::sync_with_stdio(0);
    int n,m,b; cin>>n>>m>>b;
    paway[1]=-1;
    for(int i=1;i<=b;++i){
        cin>>pos[i].first>>pos[i].second;
        poss[pos[i]]=i;
        pxy[pos[i].first].insert(pos[i].second);
        pyx[pos[i].second].insert(pos[i].first);
    }
    dfs(1, -1);
    queue<int> plug;
    auto checkinsert=[&](int i){
        if(sons[i])return;
        if(inque[i])return;
        // cerr<<"check insert of "<<i<<" and paway: "<<paway[i]<<endl;
        if(paway[i]==2){
            auto it=pyx[pos[i].second].upper_bound(pos[i].first);
            if(it==pyx[pos[i].second].end())plug.push(i),inque[i]=1;
        }
        else if(paway[i]==3){
            auto it=pxy[pos[i].first].upper_bound(pos[i].second);
            if(it==pxy[pos[i].first].end())plug.push(i),inque[i]=1;
        }
        else if(paway[i]==0){
            auto it=pyx[pos[i].second].lower_bound(pos[i].first);
            if(it==pyx[pos[i].second].begin())plug.push(i),inque[i]=1;
        }
        else{
            auto it=pxy[pos[i].first].lower_bound(pos[i].second);
            if(it==pxy[pos[i].first].begin())plug.push(i),inque[i]=1;
        }
    };
    for(int i=2;i<=b;++i){
        checkinsert(i);
    }
    stack<pair<char,int>> st;
    while(plug.size()){
        int now=plug.front(); plug.pop();
        // cerr<<"plug now: "<<now<<endl;
        --sons[pa[now]];
        int nx=pos[now].first;
        int ny=pos[now].second;
        pxy[nx].erase(ny);
        pyx[ny].erase(nx);
        if(paway[now]==0){
            st.emplace('v',ny);
        }
        else if(paway[now]==1){
            st.emplace('>',nx);
        }
        else if(paway[now]==2){
            st.emplace('^',ny);
        }
        else if(paway[now]==3){
            st.emplace('<',nx);
        }
        set<int>::iterator it;
        it=pxy[nx].upper_bound(ny);
        if(it!=pxy[nx].end()){
            checkinsert(poss[make_pair(nx,*it)]);
        }
        if(it!=pxy[nx].begin()){
            checkinsert(poss[make_pair(nx,*prev(it))]);
        }
        it=pyx[ny].upper_bound(nx);
        if(it!=pyx[ny].end()){
            checkinsert(poss[make_pair(*it,ny)]);
        }
        if(it!=pyx[ny].begin()){
            checkinsert(poss[make_pair(*prev(it),ny)]);
        }
    }
    if((int)st.size()!=b-1)exit((cout<<"impossible"<<endl,0));
    cout<<"possible"<<endl;
    while(st.size()){
        cout<<st.top().first<<" "<<st.top().second<<'\n';
        st.pop();
    }
}


