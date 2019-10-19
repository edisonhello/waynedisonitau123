#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    static const int maxn = 1e6 + 1000 + 5;
    struct Edge {
        int to, rev;
        long long cap;
        Edge(int a, long long b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int qu[maxn], lev[maxn], ql, qr, n;

    void Init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) g[i].clear();
    }

    void AddEdge(int a, int b, long long c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool Bfs(int s, int t) {
        fill(lev, lev + n, -1);
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (Edge &e : g[x]) {
                if (lev[e.to] == -1 && e.cap > 0) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }

    long long Dfs(int x, int t, long long flow) {
        if (x == t) return flow;
        long long res = 0;
        for (Edge &e : g[x]) {
            if (lev[e.to] == lev[x] + 1 && e.cap > 0) {
                int fl = Dfs(e.to, t, min(flow - res, e.cap));
                e.cap -= fl;
                g[e.to][e.rev].cap += fl;
                res += fl;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }

    long long operator()(int s, int t) {
        long long res = 0;
        for (; Bfs(s, t); res += Dfs(s, t, 1e18));
        return res;
    }
} flow;

const int maxn = 1000 + 5;
long long r[maxn], w[maxn * maxn];
vector<int> g[maxn];

int main() {
    int tc; scanf("%d", &tc);
    while (tc--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) scanf("%lld", &r[i]);
        for (int i = 0; i < n; ++i) g[i].clear();
        long long sum = 0;
        for (int i = 0; i < m; ++i) {
            int a, b; long long t;
            scanf("%d%d%lld", &a, &b, &t);
            w[i] = t;
            sum += t;
            --a, --b;
            g[a].push_back(i);
            g[b].push_back(i);
        }

        auto Check = [&](long long t) {
            int src = n + m, trg = n + m + 1;
            flow.Init(n + m + 2);
            for (int i = 0; i < n; ++i) flow.AddEdge(src, i, t * r[i]);
            for (int i = 0; i < n; ++i) {
                for (int &e : g[i])
                    flow.AddEdge(i, n + e, 1e15);
            }
            for (int i = 0; i < m; ++i)
                flow.AddEdge(i + n, trg, w[i]);
            long long fl = flow(src, trg);
            return fl == sum;
        };

        long long ans = 1e13;
        for (int d = 50; d >= 0; --d) {
            if (ans - (1LL << d) < 0) continue;
            if (Check(ans - (1LL << d)))
                ans -= (1LL << d);
        }
        printf("%lld\n", ans);
    }
}
