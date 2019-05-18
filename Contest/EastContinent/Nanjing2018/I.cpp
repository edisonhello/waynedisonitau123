#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;

struct dinic {
    struct edge {
        int to, cap, rev;
        edge(int a, int b, int c): to(a), cap(b), rev(c) {}
    };
    vector<edge> g[maxn];
    int lev[maxn], qu[maxn], ql, qr;
    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size() - 0);
        g[b].emplace_back(a, 0, g[a].size() - 1);
    }
    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        ql = qr = 0;
        qu[qr++] = s;
        lev[s] = 0;
        while (ql < qr) {
            int x = qu[ql++];
            for (const edge &e : g[x]) {
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
        for (edge &e : g[x]) {
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                int f = dfs(e.to, t, min(flow - res, e.cap));
                e.cap -= f;
                g[e.to][e.rev].cap += f;
                res += f;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }
    int operator()(int s, int t) {
        int res = 0;
        for (; bfs(s, t); res += dfs(s, t, 1000000000));
        return res;
    }
} flow;

int hr[maxn];
int mst[maxn];

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    int sz = 0;
    int s = sz++, p = sz++, q = sz++, t = sz++;
    for (int i = 0; i < n; ++i) hr[i] = sz++;
    for (int i = 0; i < m; ++i) mst[i] = sz++;
    for (int i = 0; i < n; ++i) flow.add_edge(q, hr[i], 1);
    for (int i = 0; i < n; ++i) flow.add_edge(p, hr[i], 1);
    for (int i = 0; i < n; ++i) {
        int z; scanf("%d", &z);
        while (z--) {
            int x; scanf("%d", &x);
            --x;
            flow.add_edge(hr[i], mst[x], 1);
        }
    }
    flow.add_edge(s, p, n);
    flow.add_edge(s, q, k);
    for (int i = 0; i < m; ++i) flow.add_edge(mst[i], t, 1);
    printf("%d\n", flow(s, t));
}
