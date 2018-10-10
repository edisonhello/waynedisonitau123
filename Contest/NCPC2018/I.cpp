#include <bits/stdc++.h>
using namespace std;

const int maxn = 11233;
struct dinic {
    static const int inf = 1e9;
    struct edge {
        int to, cap, rev;
        edge(int d, int c, int r): to(d), cap(c), rev(r) {}
    };
    vector<edge> g[maxn];
    int qu[maxn], ql, qr;
    int lev[maxn];
    void init() {
        for (int i = 0; i < maxn; ++i)
            g[i].clear();
    }
    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size() - 0);
        g[b].emplace_back(a, 0, g[a].size() - 1);
    }
    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (edge &e : g[x]) if (lev[e.to] == -1 && e.cap > 0) {
                lev[e.to] = lev[x] + 1;
                qu[qr++] = e.to;
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
            e.cap -= f;
            g[e.to][e.rev].cap += f;
        }
        if (res == 0) lev[x] = -1;
        return res;
    }
    int operator()(int s, int t) {
        int flow = 0;
        for (; bfs(s, t); flow += dfs(s, t, inf));
        return flow;
    }
} flow;

int co[1005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t ; while(t--){
        int n,m; cin>>n>>m;
        flow.init();
        int source=0,sink=maxn-1;
        for(int i=1;i<=n;++i){
            cin>>co[i];
            flow.add_edge(i,sink,co[i]);
        }
        int total=0;
        for(int i=1;i<=m;++i){
            int u,v,w; cin>>u>>v>>w;
            total+=w;
            flow.add_edge(source,i+n,w);
            flow.add_edge(i+n,u,flow.inf);
            flow.add_edge(i+n,v,flow.inf);
        }
        cout<<total-flow(source,sink)<<endl;
    }
}
