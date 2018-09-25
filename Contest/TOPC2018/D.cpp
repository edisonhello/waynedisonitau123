#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
const int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
vector<int> g[maxn], r[maxn];
int c[maxn], to[maxn], sz[maxn];
int fa[maxn];
bool v[maxn], onc[maxn], toc[maxn], fc[maxn];
string gr[maxn];

namespace djs {
    int fa[maxn], sz[maxn];
    void init(int n) {
        for (int i = 0; i < n; ++i)
            fa[i] = i, sz[i] = 1;
    }
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        fa[x] = y;
        sz[y] += sz[x];
    }
    int size(int x) {
        return sz[find(x)];
    }
}

void add_edge(int x, int y) {
    g[x].push_back(y);
    r[y].push_back(x);
    djs::merge(x, y);
}

void rdfs(int x, int k) {
    to[x] = k;
    sz[x] = 1;
    v[x] = true;
    for (int u : r[x]) {
        if (v[u]) continue;
        rdfs(u, k);
        sz[x] += sz[u];
    }
}

void dfs(int x, int p) {
    if (fc[djs::find(x)]) return;
    // printf("dfs x = %d p = %d\n", x, p);
    fa[x] = p;
    v[x] = true;
    for (int u : g[x]) {
        if (fc[djs::find(x)]) break;
        if (v[u]) {
            if (onc[u]) continue;
            int y = x;
            while (true) {
                // printf("y = %d\n", y);
                onc[y] = true;
                if (y == u) break;
                y = fa[y];
            }
            fc[djs::find(x)] = true;
            // puts("aaa");
            continue;
        }      
        dfs(u, x);
    }
}

void hdfs(int x, int p) {
    sz[x] = 1;
    toc[x] = true;
    for (int u : r[x]) {
        if (u == p) continue;
        hdfs(u, x);
        sz[x] += sz[u];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        int n, m, s; cin >> n >> m >> s;
        for (int i = 0; i < s; ++i) cin >> c[i];
        for (int i = 0; i < n; ++i) cin >> gr[i];
        for (int i = 0; i <= n * m; ++i) g[i].clear(), r[i].clear();
        djs::init(n * m + 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (gr[i][j] >= 'A' && gr[i][j] <= 'Z') continue;
                int dx, dy;
                if (gr[i][j] == 'u') dx = -1, dy = 0;
                if (gr[i][j] == 'd') dx = 1, dy = 0;
                if (gr[i][j] == 'l') dx = 0, dy = -1;
                if (gr[i][j] == 'r') dx = 0, dy = 1;
                if (i + dx < 0 || i + dx >= n || j + dy < 0 || j + dy >= m) add_edge(i * m + j, n * m);
                else add_edge(i * m + j, (i + dx) * m + (j + dy));
            }
        }
        for (int i = 0; i <= n * m; ++i) v[i] = onc[i] = toc[i] = fc[i] = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (gr[i][j] >= 'A' && gr[i][j] <= 'Z') {
                    rdfs(i * m + j, gr[i][j] - 'A');
                }
            }
        }
        rdfs(n * m, 'Z' + 1);
        for (int i = 0; i < n * m; ++i) {
            if (v[i]) continue;
            dfs(i, -1);
        }
        // puts("gee");
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (gr[i][j] >= 'A' && gr[i][j] <= 'Z') ans += c[gr[i][j] - 'A'] * 1ll * sz[i * m + j];
            }
        }
        // puts("gee");
        for (int i = 0; i < n * m; ++i) {
            if (!onc[i]) continue;
            // printf("i = %d\n", i);
            for (int u : r[i]) if (!onc[u]) hdfs(u, i);
            // for (int )
        }
        // puts("gee");
        long long res = ans;
        for (int i = 0; i < n * m; ++i) {
            if (g[i].size() == 0) continue;
            int x = i / m, y = i % m;
            for (int j = 0; j < 4; ++j) {
                int tx = x + dx[j], ty = y + dy[j];
                int u = tx * m + ty;
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                if (toc[u] || onc[u]) continue;
                int val = c[to[u]];
                int tval = c[to[i]];
                if (toc[i] || onc[i]) {
                    if (onc[i]) res = max(res, ans + val * 1ll * djs::size(i));
                    else res = max(res, ans + val * 1ll * sz[i]);
                } else {
                    res = max(res, ans - tval * 1ll * sz[i] + val * 1ll * sz[i]);
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
