#include<bits/stdc++.h>
using namespace std;

bitset<10005> v;
vector<int> tp,G[10005],iG[10005],mem[10005];
int bel[10005];
int sccval[10005];


void addedge(int i,int j){
    G[i].push_back(j);
    iG[j].push_back(i);
}
void addedge(int i,int j,int k){
    addedge(i^1,j);
    addedge(i^1,k);
    addedge(j^1,i);
    addedge(j^1,k);
    addedge(k^1,i);
    addedge(k^1,j);
}

void _(char &x){
    if(x=='B')x=0;
    else x=1;
}

void dfs1(int now){
    v[now]=1;
    for(int i:G[now]){
        if(v[i])continue;
        dfs1(i);
    }
    tp.push_back(now);
}
void dfs2(int now,int cc){
    v[now]=1;
    bel[now]=cc;
    mem[cc].push_back(now);
    for(int i:iG[now]){
        if(v[i])continue;
        dfs2(i,cc);
    }
}

int main(){
    ios_base::sync_with_stdio(0) ;cin.tie(0);
    int n,m; cin>>n>>m;
    while(m--){
        int a,s,d;
        char q,w,e;
        cin>>a>>q>>s>>w>>d>>e;
        _(q); _(w); _(e);
        addedge(a*2+q,s*2+w,d*2+e);
        /* G[a*2+(1-q)].push_back(s*2+w);
        G[a*2+(1-q)].push_back(d*2+e);
        G[s*2+(1-w)].push_back(a*2+q);
        G[s*2+(1-w)].push_back(d*2+e);
        G[d*2+(1-e)].push_back(a*2+q);
        G[d*2+(1-e)].push_back(s*2+w); */
    }
    for(int i=2;i<=n*2+1;++i){
        if(v[i])continue;
        dfs1(i);
    }
    v.reset();
    reverse(tp.begin(),tp.end());
    int cc=0;
    for(int i:tp){
        if(v[i])continue;
        ++cc;
        dfs2(i,cc);
    }
    for(int i=1;i<=n;++i){
        if(bel[i*2]==bel[i*2+1]){
            cout<<"-1"<<endl;
            exit(0);
        }
    }
    v.reset();
    memset(sccval,-1,sizeof(sccval));
    for(int i:tp){
        if(v[i])continue;
        if(sccval[bel[i]]!=-1)continue;
        if(sccval[bel[i^1]]!=-1){
            sccval[bel[i]]=sccval[bel[i^1]]^1;
        }
        else{
            sccval[bel[i]]=1;
        }
    }
    for(int i=1;i<=n;++i){
        if(sccval[bel[i*2]])cout<<"R";
        else cout<<"B";
    }
    cout<<endl;
}
