#include<bits/stdc++.h>
using namespace std;

vector<int> G[100005],iG[100005],tp,ans;
bitset<100005> v;
int bel[100005],vis[200005],ins[200005];

void dfs1(int now){
    v[now]=1;
    for(int i:G[now]){
        if(!v[i])dfs1(i);
    }
    tp.push_back(now);
}
void dfs2(int now,int ccn){
    v[now]=1;
    bel[now]=ccn;
    // cout<<"bel["<<now<<"]: "<<ccn<<endl;
    for(int i:iG[now]){
        if(!v[i])dfs2(i,ccn);
    }
}

stack<int> st;
void dfs3(int now,int nc){
    // cout<<"dfs3: "<<now<<" "<<nc<<endl;
    st.push(now);
    ins[now*2+nc]=1;
    vis[now*2+nc]=1;
    for(int i:G[now]){
        if(ans.size())continue;
        if(bel[i]!=bel[now])continue;
        int to=i*2+(3-nc);
        int no=i*2+nc;
        if(ins[no]){
            while(st.top()!=i){
                ans.push_back(st.top());
                st.pop();
            }
            st.pop();
            ans.push_back(i);
            continue;
        }
        else{
            if(vis[to])continue;
            dfs3(i,3-nc);
        }
    }
    if(st.size())st.pop();
    ins[now*2+nc]=0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n,m; cin>>n>>m;
        for(int i=1;i<=n;++i)G[i].clear(),iG[i].clear();
        while(m--){
            int u,v; cin>>u>>v;
            G[u].push_back(v);
            iG[v].push_back(u);
        }

        for(int i=1;i<=n;++i)v[i]=0;
        tp.clear();
        for(int i=1;i<=n;++i)if(!v[i]){
            dfs1(i);
        }
        // reverse(tp.begin(),tp.end());
        for(int i=1;i<=n;++i)v[i]=0;
        int cc=0;
        for(int i=n-1;i>=0;--i){
            if(!v[tp[i]]){
                dfs2(tp[i],++cc);
            }
        }
        ans.clear();
        for(int i=1;i<=n;++i)v[i]=0;
        for(int i=1;i<=n*2+3;++i)vis[i]=0,ins[i]=0;
        for(int i=1;i<=n;++i){
            if(ans.empty() && !v[bel[i]]){
                v[bel[i]]=1;
                while(st.size())st.pop();
                dfs3(i,1);
            }
        }
        if(ans.empty())cout<<-1<<'\n';
        else{
            cout<<1<<'\n';
            cout<<ans.size()<<'\n';
            reverse(ans.begin(),ans.end());
            for(int i:ans)cout<<i<<'\n';
        }
    }

}
