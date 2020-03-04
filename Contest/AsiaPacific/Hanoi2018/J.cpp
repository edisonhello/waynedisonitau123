#include <bits/stdc++.h>
using namespace std;

const int maxn = 1235;

struct Dinic {
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int lev[maxn], qu[maxn];

    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        int ql = 0, qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (Edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }

    int dfs(int x, int t, int fl) {
        if (x == t) return fl;
        int res = 0;
        for (Edge &e : g[x]) {
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                int f = dfs(e.to, t, min(fl - res, e.cap));
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
        for (; bfs(s, t); res += dfs(s, t, 1e9));
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        if (n == -1) break;
        if (n == m) {
            cout << "YES" << '\n';
            for (int i = 1; i < n; ++i) cout << i << " " << i + 1 << '\n';
            cout << n << " " << 1 << '\n';
        } else if (m == n * (n - 1) / 2) {
            cout << "YES" << '\n';
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    cout << i << " " << j << '\n';
                }
            }
        } else if (n % 2 == 0 && m == n * n / 4) {
            cout << "YES" << '\n';
            for (int i = 1; i <= n / 2; ++i) {
                for (int j = n / 2 + 1; j <= n; ++j) {
                    cout << i << " " << j << '\n';
                }
            }
        } else cout << "NO" << '\n';
    }
}
