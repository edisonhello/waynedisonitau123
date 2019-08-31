#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
const int mod = 1e9 + 7;
const int mult[2] = {131, 71}, modp[2] = {(int)1e9 + 123, (int)1e9 + 87};
vector<int> g[maxn];
int sz[maxn], mz[maxn], pw[2][maxn];
int h[2][maxn], fc[maxn], iv[maxn];

void dfs(int x, int p) {
    sz[x] = 1;
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, x);
            sz[x] += sz[u];
            mz[x] = max(mz[x], sz[u]);
        }
    }
}

int dfs2(int x, int p) {
    int res = 1, ch = 0;
    vector<pair<int, int>> v[2];
    map<pair<int, int>, int> z;
    sz[x] = 1;
    for (int u : g[x]) {
        if (u == p) continue;
        res = 1LL * res * dfs2(u, x) % mod;
        sz[x] += sz[u];
        for (int i = 0; i < 2; ++i) v[i].emplace_back(h[i][u], sz[u]);
        z[make_pair(h[0][u], h[1][u])]++;
        ch++;
    }
    for (auto it : z) res = 1LL * res * fc[it.second] % mod;
    for (int i = 0; i < 2; ++i) {
        sort(v[i].begin(), v[i].end());
        h[i][x] = (int)g[x].size();
        for (auto u : v[i]) h[i][x] = (1LL * h[i][x] * pw[i][u.second] + u.first) % modp[i];
    }
    // printf("h[0][%d] = %d\n", x + 1, h[0][x]);
    // printf("h[1][%d] = %d\n", x + 1, h[1][x]);
    // printf("res = %d\n", res);
    return res;

}

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    fc[0] = iv[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % mod;
        iv[i] = fpow(fc[i], mod - 2);
    }
    for (int i = 0; i < 2; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j < maxn; ++j)
            pw[i][j] = pw[i][j - 1] * 1LL * mult[i] % modp[i];
    }
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, -1);

    vector<int> centroid;
    for (int i = 0; i < n; ++i) {
        int z = max(mz[i], n - sz[i]);
        if (z * 2 <= n) centroid.push_back(i);
    }

    assert(!centroid.empty() && (int)centroid.size() <= 2);
    int ans = dfs2(centroid[0], -1);
    int hv[2] = {h[0][centroid[0]], h[1][centroid[0]]};
    if (centroid.size() >= 2) {
        int z = dfs2(centroid[1], -1);
        if (h[0][centroid[1]] == hv[0] && h[1][centroid[1]] == hv[1]) assert(z == ans), ans = 2LL * ans % mod;
    }
    printf("%d\n", ans);
    return 0;
}
