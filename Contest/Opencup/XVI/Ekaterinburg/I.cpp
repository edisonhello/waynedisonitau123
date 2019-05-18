#include <bits/stdc++.h>
using namespace std;

const int maxn = 300 + 5;
int n, k, c;
int cost[maxn][maxn], load[maxn][maxn], sum[maxn];
long long dp[maxn];

struct mincost {
    static const int inf = 1e9;
    struct edge {
        int dest, cap, w, rev;
        edge(int a, int b, int c, int d): dest(a), cap(b), w(c), rev(d) {}
    };
    vector<edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];
    void init() {
        for (int i = 0; i < maxn; ++i) g[i].clear();
    }
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
        while (q.size()) {
            int x = q.front(); q.pop();
            inq[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && d[e.dest] > d[x] + e.w) {
                    d[e.dest] = d[x] + e.w;
                    p[e.dest] = x;
                    ed[e.dest] = i;
                    if (!inq[e.dest]) q.push(e.dest), inq[e.dest] = true;
                }
            }
        }
        if (d[t] == inf) return false;
        int dlt = inf;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.dest][e.rev].cap += dlt;
        }
        f += dlt; c += d[t] * dlt;
        return true;
    }
    pair<int, int> operator()(int s, int t) {
        int f = 0, c = 0;
        while (spfa(s, t, f, c));
        return make_pair(f, c);
    }
};

int solve(int l, int r) {
    for (int i = 0; i < k; ++i) {
        sum[i] = 0;
        for (int j = l; j <= r; ++j)
            sum[i] += load[j][i];
    }

    mincost flow;
    int jobs = 0;
    for (int i = 0; i < k; ++i) {
        if (sum[i] == 0) continue;

        ++jobs;
        flow.add_edge(k + n, i, 1, 0);
        for (int j = 0; j < n; ++j) {
            if (cost[j][i] == -1) continue;

            flow.add_edge(i, j + k, 1, cost[j][i] * sum[i]);
        }
    }
    for (int i = 0; i < n; ++i)
        flow.add_edge(i + k, k + n + 1, 1, 0);

    pair<int, int> p = flow(k + n, k + n + 1);
    if (p.first != jobs)
        return 1e9;
    else
        return p.second;
}

int main() {
    scanf("%d%d%d", &n, &k, &c);
    memset(cost, -1, sizeof(cost));

    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        cost[u][v] = w;
    }

    int q; scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        for (int j = 0; j < k; ++j)
            scanf("%d", &load[i][j]);
    }

    dp[0] = 0;
    for (int i = 1; i <= q; ++i) {
        dp[i] = 1e15;
        for (int j = 0; j < i; ++j)
            dp[i] = min(dp[i], dp[j] + solve(j + 1, i) + c);
    }
    printf("%lld\n", dp[q]);
    return 0;
}
