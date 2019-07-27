#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;

struct dinic {
    struct edge {
        int dest, cap, rev, fl;
        edge(int d, int c, int r) : dest(d), cap(c), rev(r), fl(0) {}
    };
    vector<edge> g[maxn];
    int qu[maxn], ql, qr;
    int lev[maxn];

    void init() {
        for (int i = 0; i < maxn; ++i)
            g[i].clear();
    }

    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (edge &e : g[x]) {
                if (lev[e.dest] == -1 && e.cap > 0) {
                    lev[e.dest] = lev[x] + 1;
                    qu[qr++] = e.dest;
                }
            }
        }
        return lev[t] != -1;
    }

    int dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (edge &e : g[x]) {
            if (e.cap > 0 && lev[e.dest] == lev[x] + 1) {
                int f = dfs(e.dest, t, min(e.cap, flow - res));
                res += f;
                e.cap -= f;
                e.fl += f;
                g[e.dest][e.rev].cap += f;
                g[e.dest][e.rev].fl -= f;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int flow = 0;
        for (; bfs(s, t); flow += dfs(s, t, 1e9));
        return flow;
    }
};

int in[maxn], u[maxn], v[maxn], c[maxn];

int main() {
    int t; scanf("%d", &t);
    dinic flow;
    while (t--) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k);
        flow.init();
        memset(in, 0, sizeof(in));
        for (int i = 0; i < m; ++i) {
            int l, r, a, b; scanf("%d%d%d%d", &l, &r, &a, &b);
            flow.add_edge(r + 1, l, b - a);
            u[i] = r + 1, v[i] = l, c[i] = b - a;
            in[l] += a;
            in[r + 1] -= a;
        }
        int ss = 0, tt = n + 2;
        /* for (int i = 1; i <= n + 1; ++i) {
            if (in[i] < 0) flow.add_edge(ss, i, -in[i]);
            else flow.add_edge(i, tt, in[i]);
        } */
        for (int i = 1; i <= n + 1; ++i) {
            if (in[i] > 0) flow.add_edge(ss, i, in[i]);
            else flow.add_edge(i, tt, -in[i]);
        }
        flow.add_edge(1, n + 1, 1e9);
        int f = flow(ss, tt);
        int sum = 0;
        for (int i = 1; i <= n + 1; ++i) {
            if (in[i] > 0) sum += in[i];
        }
        /* flow.init();
        for (int i = 0; i < m; ++i) flow.add_edge(u[i], v[i], c[i]); */
        int sol = flow(n + 1, 1);


        if (sum != f) {
            puts("-1");
        } else {
            printf("%d\n", sol * n);
        }
    }
}
