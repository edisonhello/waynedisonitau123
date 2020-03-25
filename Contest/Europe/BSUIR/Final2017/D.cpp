#include <bits/stdc++.h>
using namespace std;

int djs[2020], sz[20202], fak[2020];
bitset<202> g[202];

int od, ev;
int totfak;
int dp[203][203][2];
int to[203][203][2];
int vis[203][203][2];

int F(int x) {
    return djs[x] == x ? x : djs[x] = F(djs[x]);
}

void U(int x, int y) {
    g[x][y] = g[y][x] = 1;

    x = F(x), y = F(y);
    if (x != y) {
        totfak -= fak[x];
        totfak -= fak[y];
        fak[y] += fak[x];
        fak[y] += sz[x] * sz[y];
        --fak[y];
        totfak += fak[y];

        if (sz[x] & 1) --od; else --ev;
        if (sz[y] & 1) --od; else --ev;
        sz[y] += sz[x];
        if (sz[y] & 1) ++od; else ++ev;

        djs[x] = y;
    } else {
        --totfak;
        --fak[x];
    }
}

int Dfs(int o, int e, int f) {
    // cerr << "Dfs " << o << ' ' << e << ' ' << f << endl;
    if (vis[o][e][f]) return dp[o][e][f];

    if (o + e == 1) return 0;
    if (o + e <= 0) assert(false);

    vis[o][e][f] = 1;

    if (f) {
        int r = Dfs(o, e, 0);
        if (!r) to[o][e][f] = -1, dp[o][e][f] = 1;
    }

    if (o >= 2) {
        int r = Dfs(o - 2, e + 1, f);
        if (!r) to[o][e][f] = 3, dp[o][e][f] = 1;
    }

    if (o >= 1 && e >= 1) {
        int r = Dfs(o, e - 1, f ^ 1);
        if (!r) to[o][e][f] = 2, dp[o][e][f] = 1;
    }

    if (e >= 2) {
        int r = Dfs(o, e - 1, f ^ 1);
        if (!r) to[o][e][f] = 0, dp[o][e][f] = 1;
    }

    return dp[o][e][f];
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) sz[i] = 1;

    od = n;

    while (m--) {
        int u, v; cin >> u >> v;
        g[u][v] = g[v][u] = 1;
        U(u, v);
    }

    if (Dfs(od, ev, totfak & 1) == 0) {
        cout << 2 << endl;
        fflush(stdout);

        int u, v; cin >> u >> v;
        if (u == 0 && v == 0) exit(0);
        U(u, v);
    } else {
        cout << 1 << endl;
    }

    while (true) {
        if (od + ev == 1) break;

        assert(Dfs(od, ev, totfak & 1));
        
        if (to[od][ev][totfak & 1] == -1) {
            for (int i = 1; i <= n; ++i) if ((int)g[i].count() != sz[F(i)] - 1) {
                int conto = -1;
                for (int j = 1; j <= n; ++j) if (j != i && F(i) == F(j)) {
                    if (!g[i][j]) conto = j;
                }

                if (conto != -1) {
                    U(i, conto);
                    cout << i << ' ' << conto << endl;
                    fflush(stdout);

                    if (od + ev == 1) exit(0);

                    int u, v; cin >> u >> v;
                    if (u == 0 && v == 0) exit(0);
                    U(u, v);

                    break;
                }
            }
        } else {
            int _to = to[od][ev][totfak & 1];
            for (int i = 1; i <= n; ++i) if ((sz[F(i)] & 1) == (_to >> 1)) {
                for (int j = 1; j <= n; ++j) if (F(i) != F(j) && (sz[F(j)] & 1) == (_to & 1)) {
                    U(i, j);
                    cout << i << ' ' << j << endl;
                    fflush(stdout);

                    if (od + ev == 1) exit(0);

                    int u, v; cin >> u >> v;
                    if (u == 0 && v == 0) exit(0);
                    U(u, v);

                    goto done1;
                }
            }
            done1:;
        }
    }
}

