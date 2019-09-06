#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    static const int maxn = 100 * 100 + 5;
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int qu[maxn], lev[maxn], ql, qr;

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
        int flow = 0;
        for (; bfs(s, t); flow += dfs(s, t, 1e9));
        return flow;
    }
} flow;
const int maxn = 100 + 5; char s[maxn][maxn][10];
int dg[maxn][maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) scanf("%s", s[i][j]);
    }

    int sz = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) dg[i][j] = sz++;
    }

    int source = sz++, sink = sz++;
    int x = 0, y = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j][0] == 'R') flow.add_edge(dg[i][j], sink, 1), x++;
            else flow.add_edge(source, dg[i][j], 1), y++;
            if (s[i][j][0] == 'R') continue;
            if (i > 0 && s[i - 1][j][0] == 'R') flow.add_edge(dg[i][j], dg[i - 1][j], 1);
            if (j > 0 && s[i][j - 1][0] == 'R') flow.add_edge(dg[i][j], dg[i][j - 1], 1);
            if (i + 1 < n && s[i + 1][j][0] == 'R') flow.add_edge(dg[i][j], dg[i + 1][j], 1);
            if (j + 1 < m && s[i][j + 1][0] == 'R') flow.add_edge(dg[i][j], dg[i][j + 1], 1);
        }
    }
    int fl = flow(source, sink);
    if (x == y && fl == x) {
        int a = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) & 1) {
                    if (s[i][j][1] == '^') a += 0;
                    if (s[i][j][1] == '>') a += 1;
                    if (s[i][j][1] == 'v') a += 2;
                    if (s[i][j][1] == '<') a += 3;
                } else {
                    if (s[i][j][1] == '^') b += 0;
                    if (s[i][j][1] == '>') b += 3;
                    if (s[i][j][1] == 'v') b += 2;
                    if (s[i][j][1] == '<') b += 1;
                }
            }
        }
        if (m % 2 == 1 && n % 4 == 2 && abs(a - b) % 4 == 2 || (m % 2 == 0 || n % 4 != 2) && abs(a - b) % 4 == 0) printf("%d\n", fl);
        else printf("%d\n", fl - 1);
    } else {
        printf("%d\n", fl);
    }
    return 0;
}
