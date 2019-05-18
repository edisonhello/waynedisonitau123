#include <bits/stdc++.h>
using namespace std;
const int maxn = 630;

struct dinic {
    static const int inf = 1e9;
    struct edge {
        int to, cap, rev, flow;
        edge(int a, int b, int c): to(a), cap(b), rev(c), flow(0) {}
    };
    vector<edge> g[maxn];
    void init() {
        for (int i = 0; i < maxn; ++i)
            g[i].clear();
    }
    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size() - 0);
        g[b].emplace_back(a, 0, g[a].size() - 1);
    }
    int lev[maxn], qu[maxn], ql, qr;
    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }
    int dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (edge &e : g[x]) if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
            int f = dfs(e.to, t, min(e.cap, flow - res));
            res += f;
            e.cap -= f, e.flow += f;
            g[e.to][e.rev].cap += f, g[e.to][e.rev].flow -= f;
        }
        if (res == 0) lev[x] = -1;
        return res;
    }
    int operator()(int s, int t) {
        int flow = 0;
        for (; bfs(s, t); flow += dfs(s, t, 1000000000));
        return flow;
    }
} flow;

vector<int> wt[103];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        flow.init();
        for(int i=0;i<103;++i)wt[i].clear();
        int m,n; cin>>m>>n;
        vector<int> workerid(m);
        for(int i=0;i<m;++i)workerid[i]=i;
        vector<int> timeid(500);
        for(int i=0;i<500;++i)timeid[i]=i+m;
        vector<int> workid(n);
        for(int i=0;i<n;++i)workid[i]=i+m+500;

        for(int i=0;i<m;++i){
            flow.add_edge(620,workerid[i],123123);
            for(int j=0;j<500;++j){
                flow.add_edge(workerid[i],timeid[j],1);
            }
        }
        int sumoo=0;
        for(int i=0;i<n;++i){
            int s,oo,t; cin>>s>>oo>>t;
            sumoo+=oo;
            for(int j=s;j<t;++j){
                flow.add_edge(timeid[j],workid[i],1);
            }
            flow.add_edge(workid[i],621,oo);
        }

        int f=flow(620,621);
        // cout<<"f: "<<f<<" , sumoo: "<<sumoo<<endl;
        if(f!=sumoo){
            cout<<0<<'\n';
            continue;
        }
        for(int i=0;i<n;++i){
            for(auto &e:flow.g[workid[i]]){
                if(e.to>=timeid[0] && e.to<=timeid.back()){
                    // cout<<"e.to: "<<e.to<<" "<<e.flow<<" "<<e.cap<<endl;
                    if(e.flow<0){
                        wt[workid[i]-500-m].push_back(e.to-m);
                    }
                }
            }
        }
        for(int i=0;i<n;++i)sort(wt[i].begin(),wt[i].end());
        for(int i=0;i<n;++i){
            vector<pair<int,int>> ans;
            for(int j:wt[i]){
                if(ans.empty() || j!=ans.back().second+1){
                    ans.emplace_back(j,j);
                }
                else{
                    ++ans.back().second;
                }
            }
            cout<<ans.size();
            for(auto p:ans)cout<<" "<<p.first<<" "<<p.second+1;
            cout<<'\n';
        }
    }
}
