#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 300;
const int inf = 1e18;

struct dinic {
    struct edge {
        int to, cap, rev;
        edge(int a, int b, int c): to(a), cap(b), rev(c) {}
    };
    vector<edge> g[maxn];
    int lev[maxn], qu[maxn];
    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }
    bool bfs(int s, int t) {
        int ql = 0, qr = 0;
        memset(lev, -1, sizeof(lev));
        qu[qr++] = s;
        lev[s] = 0;
        while (ql < qr) {
            int x = qu[ql++];
            for (const edge &e : g[x]) {
                if (lev[e.to] == -1 && e.cap > 0) {
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
    vector<int> reach(int s) {
        vector<int> res(maxn);
        res[s] = 1;
        int ql = 0, qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (edge &e : g[x]) {
                if (e.cap > 0) {
                    if (res[e.to] == 1) continue;
                    res[e.to] = 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return res;
    }
    int operator()(int s, int t) {
        int res = 0;
        for (; bfs(s, t); res += dfs(s, t, inf));
        return res;
    }
};

int a[maxn], b[maxn], c[maxn][maxn];

int32_t main() {
#ifdef ONLINE_JUDGE
    freopen("hentium.in", "r", stdin);
    freopen("hentium.out", "w", stdout);
#endif
    int n;
    while (scanf("%lld", &n) != EOF) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) scanf("%lld%lld", &a[i], &b[i]);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%lld", &c[i][j]);
            }
        }
        dinic flow;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                flow.add_edge(i, j, c[i][j]);
                flow.add_edge(j, i, c[i][j]);
            }
        }
        for (int i = 0; i < n; ++i) flow.add_edge(n, i, 2 * b[i]);
        for (int i = 0; i < n; ++i) flow.add_edge(i, n + 1, 2 * a[i]);
        int res = flow(n, n + 1);
        printf("%lld\n", res / 2);
        vector<int> rec = flow.reach(n);
        for (int i = 0; i < n; ++i) {
            if (rec[i]) printf("1 ");
            else printf("2 ");
        }
        puts("");
    }
}
