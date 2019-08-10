#include <bits/stdc++.h>
using namespace std;
#define int long long 

const int maxn = 400 + 5;
const int inf = 1e14 + 5;

struct mincost {
    struct edge {
        int to, cap, w, rev;
        edge(int a, int b, int c, int d) : to(a), cap(b), w(c), rev(d) {}
    };

    vector<edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];

    void add_edge(int a, int b, int c, int d) {
        g[a].emplace_back(b, c, +d, g[b].size() - 0);
        g[b].emplace_back(a, 0, -d, g[a].size() - 1);
    }

    bool spfa(int s, int t, int &f, int &c) {
        for (int i = 0; i < maxn; ++i) {
            d[i] = inf;
            p[i] = ed[i] = -1;
            inq[i] = false;
        }

        d[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int x = q.front(); q.pop();
            inq[x] = false;
            for (int i = 0; i < (int)g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && d[e.to] > d[x] + e.w) {
                    d[e.to] = d[x] + e.w;
                    p[e.to] = x;
                    ed[e.to] = i;
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if (d[t] == inf) return false;

        int dlt = inf;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.to][e.rev].cap += dlt;
        }
        f += dlt;
        c += d[t] * dlt;
        return true;
    }

    pair<int, int> operator()(int s, int t) {
        int f = 0, c = 0;
        while (spfa(s, t, f, c));
        return make_pair(f, c);
    }
};

int l[maxn], r[maxn], c[maxn], x[maxn], y[maxn];

int32_t main() {
    int n; scanf("%lld", &n);
    for (int i = 0; i < n; ++i) scanf("%lld%lld", &l[i], &r[i]);
    int m; scanf("%lld", &m);
    for (int i = 0; i < m; ++i) scanf("%lld%lld", &x[i], &y[i]);
    int k; scanf("%lld", &k);
    for (int i = 0, j = n; i < k; ++i, ++j) scanf("%lld%lld%lld", &l[j], &r[j], &c[j]);

    mincost flow;
    int s = n + m + k, t = n + m + k + 1;
    for (int i = 0; i < n + k; ++i) flow.add_edge(s, i, 1, c[i]);
    for (int i = 0; i < m; ++i) flow.add_edge(i + n + k, t, 1, 0);
    for (int i = 0; i < n + k; ++i) {
        for (int j = 0; j < m; ++j) {
            int ll = max(l[i], x[j]), rr = min(r[i], y[j]);
            if (ll <= rr) flow.add_edge(i, j + n + k, 1, 0);
        }
    }

    int f, c; tie(f, c) = flow(s, t);
    if (f != m) puts("-1");
    else printf("%lld\n", c);
}
