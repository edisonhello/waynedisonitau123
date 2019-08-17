#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Dinic {
    static const int maxn = 3000 + 5;
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int lev[maxn], qu[maxn];

    void AddEdge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool Bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        int ql = 0, qr = 0;
        qu[qr++] = s;

        while (ql < qr) {
            int x = qu[ql++];
            for (Edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }

    int Dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (Edge &e : g[x]) {
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                int f = min(e.cap, flow - res);
                int z = Dfs(e.to, t, f);
                e.cap -= z;
                g[e.to][e.rev].cap += z;
                res += z;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int res = 0;
        for (; Bfs(s, t); res += Dfs(s, t, 1e15));
        return res;
    }
} flow;

const int maxn = 100 + 5;
int to[maxn], cap[maxn], inc[maxn];
int ind[maxn][maxn], mid[maxn][maxn], oud[maxn][maxn], day[maxn];

int32_t main() {
    int n, q, s; scanf("%lld%lld%lld", &n, &q, &s);
    for (int i = 0; i < s; ++i) scanf("%lld", &to[i]), --to[i];
    for (int i = 0; i < q; ++i) scanf("%lld", &cap[i]);

    int sz = 0, sum = 0;
    int source = sz++, sink = sz++;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < q; ++j) {
            ind[i][j] = sz++;
            mid[i][j] = sz++;
            oud[i][j] = sz++;
            flow.AddEdge(ind[i][j], mid[i][j], cap[j]);
            flow.AddEdge(mid[i][j], oud[i][j], cap[j]);
        }
        day[i] = sz++;
    }

    for (int i = 0; i < n; ++i) {
        int d; scanf("%lld", &d);
        for (int j = 0; j < q; ++j) inc[j] = 0;
        for (int j = 0; j < s; ++j) {
            int x; scanf("%lld", &x);
            sum += x;
            inc[to[j]] += x;
        }
        for (int j = 0; j < q; ++j) flow.AddEdge(source, ind[i][j], inc[j]);
        for (int j = 0; j < q; ++j) flow.AddEdge(oud[i][j], day[i], 1e12); 
        flow.AddEdge(day[i], sink, d);

        if (i + 1 < n) {
            for (int j = 0; j < q; ++j) flow.AddEdge(mid[i][j], ind[i + 1][j], 1e12);
        }
    }
    int ans = flow(source, sink);
    if (ans == sum) puts("possible");
    else puts("impossible");
    return 0;
}
