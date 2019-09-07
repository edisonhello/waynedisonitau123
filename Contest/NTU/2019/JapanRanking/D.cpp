#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000;

struct Dinic {
    static const int inf = 1e9;
    
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int lev[maxn], qu[maxn], ql, qr;

    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        ql = qr = 0;
        lev[s] = 0;
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

    int dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (Edge &e : g[x]) {
            if (lev[e.to] == lev[x] + 1 && e.cap > 0) {
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
} flow;

int in[maxn], out[maxn];

int main() {
    int h, w, c, m, nw, nc, nm; scanf("%d%d%d%d%d%d%d", &h, &w, &c, &m, &nw, &nc, &nm);
    int sz = 0;
    for (int i = 0; i < h + w + c + m + nw + nc + nm; ++i) {
        in[i] = sz++;
        out[i] = sz++;
        flow.add_edge(in[i], out[i], 1);
    }
    for (int i = 0; i < w; ++i) {
        int p; scanf("%d", &p);
        while (p--) {
            int x; scanf("%d", &x); --x;
            assert(0 <= x && x < h);
            flow.add_edge(out[x], in[i + h], 1);
        }
    }
    for (int i = 0; i < c; ++i) {
        int p; scanf("%d", &p);
        while (p--) {
            int x; scanf("%d", &x); --x;
            assert(0 <= x && x < w);
            flow.add_edge(out[x + h], in[i + h + w], 1);
        }
    }
    for (int i = 0; i < m; ++i) {
        int p; scanf("%d", &p);
        while (p--) {
            int x; scanf("%d", &x); --x;
            assert(0 <= x && x < c);
            flow.add_edge(out[x + h + w], in[i + h + w + c], 1);
        }
    }
    for (int i = 0; i < nw; ++i) {
        for (int j = 0; j < h; ++j) flow.add_edge(out[j], in[i + h + w + c + m], 1);
        for (int j = 0; j < c; ++j) flow.add_edge(out[i + h + w + c + m], in[j + w + h], 1);
    }
    for (int i = 0; i < nc; ++i) {
        for (int j = 0; j < w; ++j) flow.add_edge(out[j + h], in[i + h + w + c + m + nw], 1);
        for (int j = 0; j < m; ++j) flow.add_edge(out[i + h + w + c + m + nw], in[j + w + h + c], 1);
    }
    for (int i = 0; i < nm; ++i) {
        for (int j = 0; j < c; ++j) flow.add_edge(out[j + w + h], in[i + h + w + c + m + nw + nc], 1);
    }
    for (int i = 0; i < nw; ++i) {
        // for (int j = 0; j < nc; ++j) flow.add_edge(aa[i], bb[j], 1);
    }
    for (int i = 0; i < nc; ++i) {
        // for (int j = 0; j < nm; ++j) flow.add_edge(bb[i], cc[j], 1);
    }
    int source = sz++, sink = sz++;
    for (int i = 0; i < h; ++i) flow.add_edge(source, in[i], 1);
    for (int i = 0; i < m; ++i) flow.add_edge(out[i + h + w + c], sink, 1);
    for (int i = 0; i < nm; ++i) flow.add_edge(out[i + h + w + c + m + nc + nw], sink, 1);
    printf("%d\n", flow(source, sink));
    return 0;
}
