#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;

struct dinic {
    static const int inf = 1e9;
    struct edge {
        int to, cap, rev;
        edge(int a, int b, int c): to(a), cap(b), rev(c) {}
    };
    vector<edge> g[maxn];
    int qu[maxn], ql, qr, lev[maxn];
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
};

const int maxe = 1e5 + 5;
int x[maxe], y[maxe];

int main() {
    int m, n; scanf("%d %d", &m, &n);
    int k; scanf("%d", &k);
    dinic flow;
    for (int i = 0; i < k; ++i) scanf("%d %d", &x[i], &y[i]), --x[i], --y[i];
    int s = n + m, t = n + m + 1;
    for (int i = 0; i < m; ++i) flow.add_edge(s, i, 1);
    for (int i = 0; i < k; ++i) {
        flow.add_edge(x[i], y[i] + m, 1);
    }
    for (int i = 0; i < n; ++i) flow.add_edge(i + m, t, 1);
    int f = flow(s, t);
    int ans = f;
    for (int i = 0; i < m; ++i) {
        dinic tflow = flow;
        for (int j = 0; j < tflow.g[s].size(); ++j) {
            if (tflow.g[s][j].to == i) {
                tflow.g[s][j].cap += 2;
            }
        }
        ans = max(ans, f + tflow(s, t));
    }
    printf("%d\n", ans);
}
