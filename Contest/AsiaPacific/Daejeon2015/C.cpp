#include <bits/stdc++.h>
using namespace std;

const int maxn = 5100;
struct dinic {
    static const int inf = 1e9;
    struct edge {
        int to, cap, rev;
        edge(int a, int b, int c): to(a), cap(b), rev(c) {}
        edge() {}
    };
    vector<edge> g[maxn];
    int lev[maxn], qu[maxn], ql, qr;
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
                int f = dfs(e.to, t, min(e.cap, flow - res));
                res += f;
                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }
    int operator()(int s, int t) {
        int res = 0;
        for (; bfs(s, t); res += dfs(s, t, inf));
        return res;
    }
};

int in[100][100];
int out[100][100];
int a[100][100];

const int inf = 1e9;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        dinic flow;
        int n, m; scanf("%d%d", &n, &m);
        int all = 0;
        int sz = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &a[i][j]);
                all += a[i][j];
                in[i][j] = sz++;  
                out[i][j] = sz++;
            }
        }
        int source = sz++, sink = sz++;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) flow.add_edge(in[i][j], out[i][j], a[i][j]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) & 1) continue;
                if (i + 1 < n) flow.add_edge(out[i][j], in[i + 1][j], inf);
                if (j + 1 < m) flow.add_edge(out[i][j], in[i][j + 1], inf);
                if (i - 1 >= 0) flow.add_edge(out[i][j], in[i - 1][j], inf);
                if (j - 1 >= 0) flow.add_edge(out[i][j], in[i][j - 1], inf);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 2 == 0) flow.add_edge(source, in[i][j], inf);
                else flow.add_edge(out[i][j], sink, inf);
            }
        }
        printf("%d\n", all - flow(source, sink));
    }
}
