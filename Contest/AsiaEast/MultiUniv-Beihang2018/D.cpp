#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

void ReadInt(int &v) {
    char c;
    while (c = getchar(), !isdigit(c));
    v = c - '0';
    while (c = getchar(), isdigit(c)) v = v * 10 + c - '0';
}

constexpr int kN = 200'000;
vector<int> g[kN];
int cfa[kN], cdep[kN], cdist[kN][20];
int sz[kN], mk[kN], fa[kN][20], dep[kN];
bool vis[kN];

void BuildCentroid(int n) {
    vector<int> nd;

    function<void(int)> DfsSz = [&](int x) {
        vis[x] = true;
        sz[x] = 1;
        mk[x] = 0;
        nd.push_back(x);
        for (int u : g[x]) {
            if (vis[u]) continue;
            DfsSz(u);
            sz[x] += sz[u];
            mk[x] = max(mk[x], sz[u]);
        }
    };
    
    function<void(int, int, int)> DfsDist = [&](int x, int r, int d) {
        cdist[x][r] = d;
        vis[x] = true;
        for (int u : g[x]) {
            if (vis[u]) continue;
            DfsDist(u, r, d + 1);
        }
    };

    function<void(int, int, int)> Dfs = [&](int x, int p, int d) {
        nd.clear();
        DfsSz(x); 
        int m = nd.size(), c = -1;
        for (int u : nd) {
            if (max(mk[u], m - sz[u]) * 2 <= m) c = u;
            vis[u] = false;
        }
        DfsDist(c, d, 0);
        for (int u : nd) vis[u] = false;
        vis[c] = true;
        cfa[c] = p;
        cdep[c] = d;
        for (int u : g[c]) {
            if (vis[u]) continue;
            Dfs(u, c, d + 1);
        }
    };

    Dfs(0, -1, 0);
    for (int i = 0; i < n; ++i) vis[i] = false;
}

void Solve() {
    int n, m;
    ReadInt(n);
    ReadInt(m);
    int s = n;
    for (int i = 0; i < n + n - 1; ++i) {
        g[i].clear();
        for (int j = 0; j < 20; ++j) fa[i][j] = -1;
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        ReadInt(u);
        ReadInt(v);
        u--, v--;
        g[u].push_back(s);
        g[s].push_back(u);
        g[v].push_back(s);
        g[s].push_back(v);
        s++;
    }

    function<void(int, int)> Dfs = [&](int x, int p) {
        fa[x][0] = p;
        dep[x] = ~p ? dep[p] + 1 : 0;
        for (int i = 1; (1 << i) <= dep[x]; ++i) {
            fa[x][i] = fa[fa[x][i - 1]][i - 1];
        }
        for (int u : g[x]) {
            if (u == p) continue;
            Dfs(u, x);
        }
    };

    auto Jump = [&](int u, int k) {
        for (int i = 0; i < 20; ++i) {
            if (k >> i & 1) u = fa[u][i];
        }
        return u;
    };

    auto LCA = [&](int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        v = Jump(v, dep[v] - dep[u]);
        if (u == v) return u;
        for (int i = 19; i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };

    auto Dist = [&](int u, int v) {
        int res = dep[u] + dep[v] - 2 * dep[LCA(u, v)];
        return res;
    };

    auto GetMid = [&](int u, int v) {
        int z = LCA(u, v), d = Dist(u, v) / 2;
        if (dep[v] - dep[z] >= d) return Jump(v, d);
        return Jump(u, d);
    };


    Dfs(0, -1);
    BuildCentroid(s);
    // for (int i = 0; i < s; ++i) cerr << cfa[i] << " "; cerr << endl;
    // for (int i = 0; i < s; ++i) cerr << cdep[i] << " "; cerr << endl;
    // for (int i = 0; i < s; ++i) {
    //     cerr << "i = " << i << endl;
    //     for (int j = 0; j < cdist[i].size(); ++j) cerr << cdist[i][j] << ' ';
    //     cerr << endl;
    // }
    vector<vector<int>> csub(s);
    vector<vector<int>> csub2(s);
    // cout << "here" << endl;
    for (int i = 0; i < n; ++i) {
        int z = -1;
        for (int j = cdep[i], x = i; j >= 0; x = cfa[x], --j) {
            // cout << "i = " << i << " j = " << j << " x = " << x << endl;
            csub[x].push_back(cdist[i][j]);
            if (z != -1) csub2[z].push_back(cdist[i][j]);
            z = x;
        }
    }
    // cout << "here" << endl;
    for (int i = 0; i < s; ++i) {
        sort(csub[i].begin(), csub[i].end());
        sort(csub2[i].begin(), csub2[i].end());
        // cerr << "i = " << i << endl;
        // for (int u : csub[i]) cout << u << " "; cout << endl;
        // for (int u : csub2[i]) cout << u << " "; cout << endl;
    }

    auto GetClose = [&](int u, int w) {
#ifdef DEBUG
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (Dist(i, u) <= w) res++;
        }
        cerr << "GetClose u = " << u << " w = " << w << " res = " << res << endl;
        return res;
#else
        int res = 0;
        for (int i = cdep[u], x = u; i >= 0; --i, x = cfa[x]) {
            res += upper_bound(csub[x].begin(), csub[x].end(), w - cdist[u][i]) - csub[x].begin(); 
            // cerr << "x = " << x << " i = " << i << " qr = " << w - cdist[u][i] << endl;
            // cerr << "add " << upper_bound(csub[x].begin(), csub[x].end(), w - cdist[u][i]) - csub[x].begin() << endl;
            if (i > 0) {
                // cerr << "sub = " << upper_bound(csub2[x].begin(), csub2[x].end(), w - cdist[u][i - 1]) - csub2[x].begin() << endl;
                res -= upper_bound(csub2[x].begin(), csub2[x].end(), w - cdist[u][i - 1]) - csub2[x].begin();
            }
        }
        // cerr << "GetClose u = " << u << " w = " << w << " res = " << res << endl;
        return res;
#endif
    };

    int last = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        ReadInt(u);
        ReadInt(v);
        ReadInt(w);
        u = (u + last) % n;
        v = (v + last) % n;
        w = (w + last) % n;
        // cerr << "u = " << u << " v = " << v << " w = " << w << endl;
        int res = GetClose(u, w + w) + GetClose(v, w + w);
        int dist = Dist(u, v);
        if (w + w >= dist / 2) {
            int z = GetMid(u, v);
            res -= GetClose(z, w + w - dist / 2);
        }
        printf("%d\n", last = res);
    }
}

int main() {
    int t;
    ReadInt(t);
    while (t--) Solve();
}

