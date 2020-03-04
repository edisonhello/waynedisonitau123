#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;

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
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
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

int idx[500][500];

int main() {
    int n, k, m; scanf("%d%d%d", &n, &k, &m);
    vector<pair<int, int>> ed;
    for (int i = 0; i < m; ++i) {
        int a, b; scanf("%d%d", &a, &b); --a, --b;
        ed.emplace_back(a, b);
    }
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) idx[i][j] = sz++;
    }
    for (int i = 0; i < (int)ed.size(); ++i) {
        for (int j = 0; j < k; ++j) {
            flow.add_edge(idx[ed[i].first][j], idx[ed[i].second][(j + 1) % k], 1);
        }
    }
    int s = sz++, t = sz++;
    for (int i = 0; i < k; ++i) {
        flow.add_edge(s, idx[i][i], 1);
    }
    for (int i = 0; i < k; ++i) flow.add_edge(idx[n - 1][i], t, 1000000000);
    printf("%d\n", flow(s, t));
    return 0;
}


